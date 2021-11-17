/*
 * anomaly_detection_util.cpp
 *
 * Author: Hail Zanbar 322766353
 * Partner: Hadas Eshel 206775074
 */

#include "anomaly_detection_util.h"
#include <math.h>

//**** Hail Area****

// returns the average of X
float average(float* x, int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += x[i];
    }
    return ((float) sum / (float) size);
}

// returns the variance of X and Y
float var(float* x, int size) {

    // create an array which contains the number squares of the X array
    float newSqrArr[size];
    for (int i = 0; i < size; i++) {
        newSqrArr[i] = (x[i] * x[i]);
    }

    // the expected value of the squares array
    float sqrE = average(newSqrArr, size);

    // the expected value of X array
    float E = average(x, size);

    // the variance according the formula
    float vari = (sqrE - (E * E));
    return vari;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size) {

    // the averages of X and Y
    float Ex = average(x, size);
    float Ey = average(y, size);

    float newX[size];
    float newY[size];
    float multArr[size];

    // create a new array from X and Y, minus the expected val, and insert it to the multiply array (XY).
    for (int i = 0; i < size; i++) {
        newX[i] = (x[i] - Ex);
        newY[i] = (y[i] - Ey);
        multArr[i] = (newX[i] * newY[i]);
    }

    // the covariance according the formula
    float cova = average(multArr, size);
    return cova;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size) {

    // create variables according the formula.
    float covXY = cov(x, y, size);
    double varSqr1 = sqrt(var(x, size));
    double varSqr2 = sqrt(var(y, size));

    return (covXY / (float) (varSqr1 * varSqr2));
}

//**** Hadas Area****
// performs a linear regression and return s the line equation
Line linear_reg(float* x, float* y, int size){
    Point * point[size];
    // fill the arries of point value.
    for (int k = 0; k < size; k++){
        point[k] = new Point(x[k], y[k]);
    }
    // performs a linear regression and return s the line equation
    Line lin_reg = linear_reg(point, size);
    // free the points
    for (int d = 0; d < size; d++) {
        delete(point[d]);
    }
    return lin_reg;
}

Line linear_reg(Point** points, int size){
    float a;
    float b;

    // create arries of float value.
    float x_of_points [size];
    float y_of_points [size];

    // fill the arries of float value.
    for (int i = 0; i < size; i++){
        x_of_points[i] = points[i]->x;
        y_of_points[i] = points[i]->y;
    }

    // use the claction that need by the orders
    a = (cov(x_of_points, y_of_points, size) / var(x_of_points, size));
    b = average(y_of_points, size) - (a * average(x_of_points, size));

    // create the line
    Line line = Line(a, b);
    return line;
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    // create a line
    Line line = linear_reg(points, size);
    // use the other function that now is relevent to use.
    return dev(p,line);
}

// returns the deviation between point p and the line
float dev(Point p,Line l){

    // compute the distance between f(x) and y, and return the absulut value.
    float dist = l.f(p.x) - p.y;
    if (dist < 0) {
        dist = -dist;
    }
    return dist;
}

// calculation the Threshold
float calculationThreshold (float* x, float* y, int size, Line lin_reg) {
    Point * point[size];
    float threshold = 0;
    // fill the arries of point value.
    for (int k = 0; k < size; k++){
        point[k] = new Point(x[k], y[k]);
    }
    for (int p = 0; p < size; p++) {
        float devResult = dev(*point[p], lin_reg);
        if (devResult > threshold) {
            threshold = devResult;
        }
    }
    for (int d = 0; d < size; d++) {
        delete(point[d]);
    }
    return threshold;
}