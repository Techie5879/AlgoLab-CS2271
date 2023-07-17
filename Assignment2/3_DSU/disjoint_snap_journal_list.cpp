#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

//taken from dataset website
const long long num_vertex = 4847571; //vertex numbering goes from 0 to 4847570
const long long num_edges = 68993773; //umber of lines in dataset, will be inly used to display progress bar

const char file_path[] = "soc-LiveJournal1.txt";

struct node;

struct conn_comp
{
    conn_comp *next;
    conn_comp *prev;
    node *head;
    node *tail;
    long long len;
};

struct node
{
    conn_comp *rep;
    long long data;
    node *next;
};

struct edge
{
    long long value1;
    long long value2;
};

void MAKE_SET(long long x, conn_comp *start) {
    conn_comp *temp = start->next;

    conn_comp *new_conn_comp = new conn_comp;
    new_conn_comp->len = 1;
    new_conn_comp->next = temp;
    start->next = new_conn_comp;
    new_conn_comp->prev = start;

    if (temp != NULL)
        temp->prev = new_conn_comp;

    new_conn_comp->head = new node;
    new_conn_comp->tail = new_conn_comp->head;
    new_conn_comp->head->data = x;
    new_conn_comp->head->rep = new_conn_comp;
    new_conn_comp->head->next = NULL;
}

conn_comp *FIND_SET(long long val, conn_comp *start) {
    conn_comp *conn_comp_iterator = start->next;
    while (conn_comp_iterator != NULL) {
        node *node_iterator = conn_comp_iterator->head;
        while (node_iterator != NULL) {
            if (node_iterator->data == val)
                return node_iterator->rep;
            node_iterator = node_iterator->next;
        }
        conn_comp_iterator = conn_comp_iterator->next;
    }
    return NULL;
}

void LINK(conn_comp *x, conn_comp *y) {
    if (x != y) {
        conn_comp *max, *min;
        if (x->len > y->len) {
            max = x;
            min = y;
        }
        else {
            max = y;
            min = x;
        }
        max->len += min->len;
        node *changin_pt = min->head;
        max->tail->next = min->head;
        max->tail = min->head;
        while (changin_pt != NULL) {
            changin_pt->rep = max;
            changin_pt = changin_pt->next;
        }
        if (min->prev != NULL) min->prev->next = min->next;
        if (min->next != NULL) min->next->prev = min->prev;
        delete min;
    }
}

void UNION(edge temp, conn_comp *start)
{
    if (temp.value1 != temp.value2)
        LINK(FIND_SET(temp.value1,start), FIND_SET(temp.value2,start));
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

const int num_iter = 1;

int main()
{
    float avg_time = 0;

    for (int master = 0; master < num_iter; master++)
    {
        float start_time = clock();

        conn_comp *start = new conn_comp;
        start->head = NULL;
        start->tail = NULL;
        start->len = 0;
        start->next = NULL;
        start->prev = NULL;

        for (int i = 0; i < num_vertex; i++)
            MAKE_SET(i, start);

        ifstream fin(file_path, ios::in);

        edge temp;
        for (int i = 0; i < num_edges; i++)
        {
            update_edge(temp, fin);
            UNION(temp,start);

            cout << (float)i / (num_edges - 1) * 100 << "% done \r";
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