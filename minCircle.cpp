/*
 * minCircle.cpp
 *
 * Author: Hail Zanbar 322766353
 * Partner: Hadas Eshel 206775074
 */
#include "minCircle.h"

// C++ program to find the minimum enclosing
// circle for N integer points in a 2-D plane
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <vector>
using namespace std;


double dist(const Point& a, const Point& b)
{
    float x = a.x - b.x;
    float y = a.y - b.y;
    return sqrt(x * x + y * y);
}

bool is_inside_circ(const Circle& c, const Point* p)
{
    return dist(c.center, *p) <= c.radius;
}

Point get_center(double bx, double by,
                        double cx, double cy)
{
    double b = bx * bx + by * by;
    double c = cx * cx + cy * cy;
    double d = bx * cy - by * cx;
    return Point( (cy * b - by * c) / (2 * d),
             (bx * c - cx * b) / (2 * d) );
}

Circle create_circle(const Point& a, const Point& b,
                   const Point& c)
{
    Point center = get_center(b.x - a.x, b.y - a.y,
                                c.x - a.x, c.y - a.y);

    center.x += a.x;
    center.y += a.y;
    return Circle(center , dist(center, a));
}

Circle create_circle(const Point& a, const Point& b) {
    Point c = Point((a.x + b.x) / 2.0 , (a.y + b.y) / 2.0 );
    return Circle(c , dist(a, b) / 2.0 );
}

bool is_valid_circle(const Circle& c,
                     const vector<Point*>& P)
{
    for (const Point* p : P)
        if (!is_inside_circ(c, p))
            return false;
    return true;
}

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


    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            Circle c = create_circle(*(points[i]), *(points[j]));
            if (is_valid_circle(c, points))
                return c;
        }
    }
    return create_circle(*(points[0]), *(points[1]), *(points[2]));
}

Circle findMinCir_helper(vector<Point*>* P,
                    vector<Point*> R, int size)
{
    // Base case
    if (size == 0 || R.size() == 3) {
        return min_circle_trivial(R);
    }

    int indx = rand() % size;
    Point* p = P->at(indx);

    swap(P->at(indx), P->at(size - 1));

    Circle minCir = findMinCir_helper(P, R, size - 1);

    if (is_inside_circ(minCir, p)) {
        return minCir;
    }

    R.push_back(p);

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


