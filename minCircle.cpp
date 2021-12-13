#include "minCircle.h"

// C++ program to find the minimum enclosing
// circle for N integer points in a 2-D plane
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <vector>
using namespace std;


// Function to return the euclidean distance
// between two points
double dist(const Point& a, const Point& b)
{
    return sqrt(pow(a.x - b.x, 2)
                + pow(a.y - b.y, 2));
}

// Function to check whether a point lies inside
// or on the boundaries of the circle
bool is_inside_circ(const Circle& c, const Point* p)
{
    return dist(c.center, *p) <= c.radius;
}


// Helper method to get a circle defined by 3 points
Point get_center(double bx, double by,
                        double cx, double cy)
{
    double b = bx * bx + by * by;
    double c = cx * cx + cy * cy;
    double d = bx * cy - by * cx;
    return Point( (cy * b - by * c) / (2 * d),
             (bx * c - cx * b) / (2 * d) );
}

// Function to return a unique circle that
// intersects three points
Circle create_circle(const Point& a, const Point& b,
                   const Point& c)
{
    Point center = get_center(b.x - a.x, b.y - a.y,
                                c.x - a.x, c.y - a.y);

    center.x += a.x;
    center.y += a.y;
    return Circle(center , dist(center, a));
}

// Function to return the smallest circle
// that intersects 2 points
Circle create_circle(const Point& a, const Point& b)
{
    // Set the center to be the midpoint of A and B
    Point c = Point((a.x + b.x) / 2.0 , (a.y + b.y) / 2.0 );

    // Set the radius to be half the distance AB
    return Circle(c , dist(a, b) / 2.0 );
}

// Function to check whether a circle
// encloses the given points
bool is_valid_circle(const Circle& c,
                     const vector<Point*>& P)
{

    // Iterating through all the points
    // to check whether the points
    // lie inside the circle or not
    for (const Point* p : P)
        if (!is_inside_circ(c, p))
            return false;
    return true;
}

// Function to return the minimum enclosing
// circle for N <= 3
Circle min_circle_trivial(vector<Point*>& points)
{
    assert(points.size() <= 3);
    if (points.empty()) {
        return Circle(Point(0, 0), 0);
    }
    else if (points.size() == 1) {
        return Circle(*(points[0]), 0);
    }
    else if (points.size() == 2) {
        return create_circle(*(points[0]), *(points[1]));
    }

    // To check if MEC can be determined
    // by 2 points only
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {

            Circle c = create_circle(*(points[i]), *(points[j]));
            if (is_valid_circle(c, points))
                return c;
        }
    }
    return create_circle(*(points[0]), *(points[1]), *(points[2]));
}

// Returns the MEC using Welzl's algorithm
// Takes a set of input points P and a set R
// points on the circle boundary.
// n represents the number of points in P
// that are not yet processed.
Circle findMinCir_helper(vector<Point*>* P,
                    vector<Point*> R, int size)
{
    // Base case when all points processed or |R| = 3
    if (size == 0 || R.size() == 3) {
        return min_circle_trivial(R);
    }

    // Pick a random point randomly
    int indx = rand() % size;
    Point* p = P->at(indx);

    // Put the picked point at the end of P
    // since it's more efficient than
    // deleting from the middle of the vector
    swap(P[indx], P[size - 1]);

    // Get the MEC circle d from the
    // set of points P - {p}
    Circle minCir = findMinCir_helper(P, R, size - 1);

    // If d contains p, return d
    if (is_inside_circ(minCir, p)) {
        return minCir;
    }

    // Otherwise, must be on the boundary of the MEC
    R.push_back(p);

    // Return the MEC for P - {p} and R U {p}
    return findMinCir_helper(P, R, size - 1);
}

Circle findMinCircle(Point** points,size_t size) {
    vector<Point*>* pointsVec = new vector<Point*>;
    for (int i = 0; i < size; i++) {
        pointsVec->push_back(points[i]);
    }
    random_shuffle(pointsVec->begin(), pointsVec->end());
    Circle circle = findMinCir_helper(pointsVec, {}, pointsVec->size());

    // free allocated memory
    delete(pointsVec);
    return circle;
}

Circle findMinCircle(float *col1, float *col2,int size) {
    Point* points[size];
    for (int i = 0; i < size; i++) {
        Point* p = new Point(col1[i], col2[i]);
        points[i] = p;
    }
    Circle circle = findMinCircle(points, size);

    // free allocated memory
    for (Point* p : points) {
        delete(p);
    }
    return circle;
}


