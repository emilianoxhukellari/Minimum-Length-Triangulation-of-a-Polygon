// Minimum Length Triangulation
#pragma once
#include <vector>
#include <iostream>

using namespace std;

const double M = 2147483647;

struct Point // 2D point
{
    double x, y;
};

double dist(Point p1, Point p2) // This function finds the distance between two points using Pythagorean Theorem
{
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

struct Memo { // Memo will be used for memoization for Dynamic Programming
    double val;
    int vertex;
};

class Polygon {
private:
    vector <Point> coordinates; // A vector with 2D points for the Polygon
    Memo memo[100][100]; // 2D memo that stores results
public:
    Polygon(vector <Point> x) { // Parametrized constructor 
        coordinates = x;
    }
    void addCoordinates(Point p) {
        coordinates.push_back(p);
    }
    vector <Point> getCoordinates() {
        return coordinates;
    }
    double perimeter(vector <Point> points, int i, int j, int k) // This function finds the perimeter of a triangle
    {
        Point p1 = points.at(i);
        Point p2 = points.at(j);
        Point p3 = points.at(k);
        return dist(p1, p3) + dist(p2, p3) + dist(p2, p1);
    }

    double minLength(vector <Point> points, int i, int j) // Recursive function with memoization
    {

        if (j < i + 2) // There should be at least three points to form a polygon
            return 0;

        if (memo[i][j].val != NULL) // If we have already computed the value, there is no need to recompute
            return memo[i][j].val;

        double min = M;
        double x;
        int minVertex = 0;

        for (int k = i + 1; k < j; k++) { // Visiting all vertices

            x = minLength(points, i, k) + minLength(points, k, j) + perimeter(points, i, k, j); // Divide the polygon into a sub-polygon on the left, a triangle, and a sub-polygon on the right

            if (x < min) { // if the x is less than min, update x -> we need the minumul length triangulation
                min = x;
                minVertex = k;
            }
        }

        memo[i][j].val = min; // fill memo; we will need it for memoization
        memo[i][j].vertex = minVertex; // optimal vertices; will be used to print optimal triangles
        return  min; // return the final result
    }

    void printTriangles(int i, int j) { // Printing coordinates of the optimal triangles with minumum perimeters
        if (i + 2 <= j) {
            cout << i << " " << memo[i][j].vertex << " " << j << endl; 
            printTriangles(i, memo[i][j].vertex); // left
            printTriangles(memo[i][j].vertex, j); // right
        }
    }
};
