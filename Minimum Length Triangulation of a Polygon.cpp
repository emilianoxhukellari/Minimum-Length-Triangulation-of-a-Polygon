// Minimum Length Triangulation
#include <iostream>
#include <fstream>
#include "Polygon.h"

vector <Polygon*> polygons; // All Polygons will be stored here

void readData() { // Reading data from text file
    ifstream obj;
    obj.open("data.txt");
    if (obj.fail()) {
        cerr << "Error opening file!" << endl;
    }
    else {
        
        while (true) {
            int number = 0;
            double _x, _y;
            obj >> number;
            if (number < 1)
                break;
            vector <Point> add;
            for (int i = 0; i < number; i++) {
                Point p;
                obj >> _x >> _y;
                p.x = _x;
                p.y = _y;
                add.push_back(p); // Add coordinates to "add" vector
            }
           polygons.push_back(new Polygon(add)); // Add new Polygon with "add" coordinates to the vector
        }
    }
}

int main()
{
    readData();
    cout << "========== Minimum Length Triangulation Dynamic Programming ==========" << endl << endl;

    for (int i = 0; i < polygons.size(); i++) { // Display info for each Polygon
        cout << "Polygon #" << i + 1 << endl;
        cout << "Number of vertices: " << polygons.at(i)->getCoordinates().size() << endl; 
        cout << "Minimum length triangulation is: " << polygons.at(i)->minLength(polygons.at(i)->getCoordinates() // Calling function "minLength()"
            , 0, polygons.at(i)->getCoordinates().size() - 1) << endl << endl;

        cout << "Optimal Triangles: " << endl;

        polygons.at(i)->printTriangles(0, polygons.at(i)->getCoordinates().size() - 1); // Printing coordinates of the optimal triangles that form the Polygon

        cout << endl << endl;
    }
}
