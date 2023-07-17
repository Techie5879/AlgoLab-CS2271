#include <bits/stdc++.h>
#include <fstream>
#include <time.h>

using namespace std;

struct Point {
    int x, y;
};

double dist(const Point &p1, const Point &p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double trigCost(const Point &i, const Point &j, const Point &k) {
    return dist(i, j) + dist(j, k) + dist(k, i);
}

pair<double, vector<pair<int, int>>> mTCG(Point *points, int *visited, int n) {
    if (n == 3) {
        return {trigCost(points[visited[0]], points[visited[1]], points[visited[2]]),
                {{visited[0], visited[1]}, {visited[1], visited[2]}, {visited[2], visited[0]}}};
    }

    int index;
    int newVisited[n - 1];
    double min = 1e7;
    double cost;
    vector<pair<int, int>> minTrigEdges;

    for (int i = 1; i < n - 1; i++) {
        cost = trigCost(points[visited[i - 1]], points[visited[i]], points[visited[i + 1]]);
        if (cost < min) {
            min = cost;
            index = visited[i];
            minTrigEdges = {{visited[i - 1], visited[i]}, {visited[i], visited[i + 1]}, {visited[i + 1], visited[i - 1]}};
        }
    }

    cost = trigCost(points[visited[n - 1]], points[visited[n - 2]], points[visited[0]]);
    if (cost < min) {
        min = cost;
        index = visited[n - 1];
        minTrigEdges = {{visited[n - 1], visited[n - 2]}, {visited[n - 2], visited[0]}, {visited[0], visited[n - 1]}};
    }

    cost = trigCost(points[visited[0]], points[visited[1]], points[visited[n - 1]]);
    if (cost < min) {
        min = cost;
        index = visited[0];
        minTrigEdges = {{visited[0], visited[1]}, {visited[1], visited[n - 1]}, {visited[n - 1], visited[0]}};
    }

    int m = 0;
    for (int i = 0; i < n; i++) {
        if (visited[i] != index) {
            newVisited[m++] = visited[i];
        }
    }

    auto result = mTCG(points, newVisited, n - 1);
    result.first += cost;
    result.second.insert(result.second.end(), minTrigEdges.begin(), minTrigEdges.end());

    return result;
}

int main() {
    ifstream infile("output.txt");
    ofstream outfile("greedy.txt");
    ofstream outfile_time("greedy_time.txt");
    ofstream outfile_triangulation("greedy_triangulation.txt");

    int N;
    while (infile >> N) {
        Point points[N];
        for (int i = 0; i < N; i++) {
            infile >> points[i].x >> points[i].y;
        }
        int visited[N];
        for (int k = 0; k < N; k++) {
            visited[k] = k;
        }
        clock_t start = clock();
        auto result = mTCG(points, visited, N);
        clock_t end = clock();
        double elapsedTime = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
        cout << elapsedTime << endl;
        outfile << "Number of vertices: " << N << endl;
        outfile << result.first << endl;
        outfile_time << elapsedTime << endl;
        outfile_triangulation << "Number of vertices: " << N << endl;
        for (const auto &edge : result.second) {
            outfile_triangulation << points[edge.first].x << " " << points[edge.first].y << endl;
        }
    }
    infile.close();
    outfile.close();
    outfile_time.close();
    outfile_triangulation.close();
    return 0;
}