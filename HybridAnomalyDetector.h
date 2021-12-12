/*
 * HybridAnomalyDetector.h
 *
 * Author: Hadas Eshel 206775074
 * Partner: Hail Zanbar 322766353
 */
#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
    float corralatonOfSimpleThreshold;
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
    virtual void addCorrelate(string feature1,int i, string feature2 , int c,
                              float correlate, float *colI, float *colC, int sizeOfCol);
    virtual void report(vector<AnomalyReport> *vectorOfReport, correlatedFeatures feature, Point point,  int line);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
