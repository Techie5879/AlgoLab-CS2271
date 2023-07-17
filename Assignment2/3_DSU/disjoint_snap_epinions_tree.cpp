#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

//taken from dataset website
const u_long num_vertex = 75888; //vertex numbering goes from 0 to 75888
const u_long num_edges = 508837; //umber of lines in dataset, will be inly used to display progress bar

const char file_path[] = "Dataset/SNAP/2_Epinions/soc-Epinions1.txt";

struct node
{
    //no data field as index itself is data
    node *parent;
    u_long rank;
};

struct edge
{
    u_long value1;
    u_long value2;
};

// number of nodes are fixed (4039) so using an array to store nodes

node node_list[num_vertex];


void MAKE_SET(node *x) {
    x->parent = x;
    x->rank = 0;
}

node *FIND_SET(node *x) {
    if (x != x->parent)
        x->parent = FIND_SET(x->parent);

    return x->parent;
}

void LINK(node *x, node *y) {
    if (x->rank > y->rank)
        y->parent = x;
    else
        x->parent = y;

    if (x->rank == y->rank)
        y->rank++;
}

void UNION(edge temp) {
    if (temp.value1 != temp.value2)
        LINK(FIND_SET(&node_list[temp.value1]), FIND_SET(&node_list[temp.value2]));
}

void update_edge(edge &given_edge, ifstream &fin)
{
    if (!fin.eof())
    {
        char line[100];
        fin.getline(line, 100);

        if(line[0] == '#')
        {
            while(line[0] == '#')
                fin.getline(line, 100);
        }

        stringstream str_strm;
        str_strm << line; //convert the string s into stringstream

        char num[10];

        str_strm >> num;
        given_edge.value1 = atoi(num);

        str_strm >> num;
        given_edge.value2 = atoi(num);

        // cout << given_edge.value1 << " " << given_edge.value2 << endl;
    }
}

const int num_iter = 10;

int main()
{
    float avg_time = 0;

    for (int master = 0; master < num_iter; master++)
    {
        float start_time = clock();

        for (int i = 0; i < num_vertex; i++)
            MAKE_SET(&node_list[i]);

        ifstream fin(file_path, ios::in);

        edge temp;
        for (int i = 0; i < num_edges; i++)
        {
            update_edge(temp, fin);
            UNION(temp);

            cout << (float)i / num_edges * 100 << "% done \r";
        }

        fin.close();

        float end_time = clock();

        float time_taken = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
        avg_time += time_taken;
        cout << "Time Taken: " << time_taken << "ms" << endl;
    }

    avg_time /= num_iter;
    cout << "Average Time Taken: " << avg_time << "ms" << endl;
}