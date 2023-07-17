// A Dynamic Programming based program to find minimum cost of convex
// polygon triangulation
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>


#define MAX 1000000.0
using namespace std;

// Structure of a point in 2D plane
struct Point
{
    int x, y;
};

// Utility function to find minimum of two double values
double min(double x, double y)
{
    return (x <= y)? x : y;
}

// A utility function to find distance between two points in a plane
double dist(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
                (p1.y - p2.y)*(p1.y - p2.y));
}

// A utility function to find cost of a triangle. The cost is considered
// as perimeter (sum of lengths of all edges) of the triangle
double cost(Point points[], int i, int j, int k)
{
    Point p1 = points[i], p2 = points[j], p3 = points[k];
    return dist(p1, p2) + dist(p2, p3) + dist(p3, p1);
}


double mTCDP(Point points[], int n) {
    // Base case, if less than 3 points
    if (n < 3) return 0;
    // dp[i][j] stores cost of triangulation of points from i to j
    // dp[0][n-1] is the final answer, considering n points
    double dp[n][n];

    // dp is filled in diagonal fashion
    for (int gap = 0; gap < n; gap++) {
        for (int i = 0, j = gap; j < n; i++, j++) {
            if (j < i+2) dp[i][j] = 0.0;
            else {
                dp[i][j] = MAX;
                for (int k = i+1; k < j; k++) {
                    double val = dp[i][k] + dp[k][j] + cost(points,i,j,k);
                    if (dp[i][j] > val) dp[i][j] = val;
                }
            }
        }
    }
    return dp[0][n-1];
}

// Driver program to test above functions
int main()
{
    ifstream infile("output.txt");
    ofstream outfile("dp.txt");
    ofstream outfile_time("dp_time.txt");

    int N;
    while (infile >> N)
    {
        Point points[N];
        for (int i = 0; i < N; i++)
        {
            infile >> points[i].x >> points[i].y;
        }
        clock_t start = clock();
        double result = mTCDP(points, N);
        clock_t end = clock();
        double elapsedTime = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
        cout << elapsedTime << endl;

        outfile << "Number of vertices: " << N << endl;
        outfile << result << endl;
        outfile_time << elapsedTime << endl;
    }

    infile.close();
    outfile.close();
    outfile_time.close();
    return 0;
}
