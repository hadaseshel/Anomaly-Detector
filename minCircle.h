/*
 * minCircle.h
 *
 * Author: Hail Zanbar 322766353
 * Partner: Hadas Eshel 206775074
 */
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

Circle findMinCircle(Point** points,size_t size);

Circle findMinCircle(float *col1, float *col2,int size);

// you can add here additional methods

double dist(const Point& a, const Point& b);

bool is_inside_circ(const Circle& c, const Point* p);

Point get_center(double bx, double by, double cx, double cy);

Circle create_circle(const Point& a, const Point& b, const Point& c);

Circle create_circle(const Point& a, const Point& b);

bool is_valid_circle(const Circle& c, const vector<Point*>& P);

Circle min_circle_trivial(vector<Point*>& points);

Circle findMinCir_helper(vector<Point*>* P,vector<Point*> R, int size);

#endif /* MINCIRCLE_H_ */
