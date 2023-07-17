#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <vector>

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
    return (x <= y) ? x : y;
}

// A utility function to find distance between two points in a plane
double dist(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

// A utility function to find cost of a triangle. The cost is considered
// as perimeter (sum of lengths of all edges) of the triangle
double cost(Point points[], int i, int j, int k)
{
    Point p1 = points[i], p2 = points[j], p3 = points[k];
    return dist(p1, p2) + dist(p2, p3) + dist(p3, p1);
}

void printTriangulation(int i, int j, int** kvals, Point points[], ofstream& outfile)
{
    if (j <= i + 1)
        return;
    int k = kvals[i][j];
    
    outfile << points[i].x << " " << points[i].y << endl << points[k].x << " " << points[k].y << endl << points[j].x << " " << points[j].y << "\n";
    printTriangulation(i, k, kvals, points, outfile);
    printTriangulation(k, j, kvals, points, outfile);
}

double mTCDP(Point points[], int n, ofstream& outfile)
{
    if (n < 3)
        return 0;

    double dp[n][n];
    int** kvals = new int*[n];
    for (int i = 0; i < n; ++i)
        kvals[i] = new int[n];

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (j < i + 2)
                dp[i][j] = 0.0;
            else
            {
                dp[i][j] = MAX;
                for (int k = i + 1; k < j; k++)
                {
                    double val = dp[i][k] + dp[k][j] + cost(points, i, j, k);
                    if (dp[i][j] > val)
                    {
                        dp[i][j] = val;
                        kvals[i][j] = k;
                    }
                }
            }
        }
    }
    outfile << "Number of vertices: " << n << endl;
    printTriangulation(0, n - 1, kvals, points, outfile);

    for (int i = 0; i < n; ++i)
        delete[] kvals[i];
    delete[] kvals;

    return dp[0][n-1];
}

// Driver program to test above functions
int main()
{
    ifstream infile("output.txt");
    ofstream outfile("dp.txt");
    ofstream outfile_time("dp_time.txt");
    ofstream outfile_triangles("triangles.txt");


    int N;
    while (infile >> N)
    {
        Point points[N];
        for (int i = 0; i < N; i++)
        {
            infile >> points[i].x >> points[i].y;
        }
        clock_t start = clock();
        double result = mTCDP(points, N, outfile_triangles);
        clock_t end = clock();
        double elapsedTime = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
        // cout << elapsedTime << endl;

        outfile << "Number of vertices: " << N << endl;
        outfile << result << endl;
        outfile_time << elapsedTime << endl;
    }
    outfile_triangles.close();
    infile.close();
    outfile.close();
    outfile_time.close();
    return 0;
}