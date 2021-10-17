//
// Created by hadseshel on 10/17/21.
//

#include "anomaly_detection_util.h"

//**** Hail Area****
// returns the variance of X and Y
float var(float* x, int size);
// returns the covariance of X and Y
float cov(float* x, float* y, int size);
// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size);


//**** Hadas Area****
// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size);
// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size);
// returns the deviation between point p and the line
float dev(Point p,Line l);