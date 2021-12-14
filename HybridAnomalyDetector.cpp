/*
 * HybridAnomalyDetector.cpp
 *
 * Author: Hadas Eshel 206775074
 * Partner: Hail Zanbar 322766353
 */
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
    this->corralatonOfSimpleThreshold = this->correlationThreshold;
    this->correlationThreshold = 0.5;
}

HybridAnomalyDetector::~HybridAnomalyDetector() {}

void HybridAnomalyDetector::addCorrelate(string feature1, int i, string feature2 , int c,float correlate,
                                    float *colI, float *colC, int sizeOfCol){
    if(correlate >= this->corralatonOfSimpleThreshold) {
        SimpleAnomalyDetector::addCorrelate(feature1, i,feature2 ,c, correlate, colI, colC, sizeOfCol);
    }else{
        Line line = Line();
        Circle circle = findMinCircle(colI, colC, sizeOfCol);
        // create the correlated.
        correlatedFeatures corr = {feature1, feature2, i, c, correlate, line,
                                   0, circle ,"circle"};
        // push the correlated feateus.
        this->cf->push_back(corr);
    }
}

void HybridAnomalyDetector::report(vector<AnomalyReport> *vectorOfReport, correlatedFeatures feature,
                                   Point point,  int line) {
    if (feature.typeOfCorrlation == "line") {
        SimpleAnomalyDetector::report(vectorOfReport, feature, point, line);
    } else {
        // distance from center of circale
        float y = point.y-feature.minCircle.center.y;
        float x = point.x-feature.minCircle.center.x;
        float disResult = sqrt((y*y) + (x*x));
        if (disResult > (feature.minCircle.radius*1.1)) {
            string description = feature.feature1 + "-" + feature.feature2;
            long timeStep = line + 1;
            vectorOfReport->push_back(AnomalyReport(description,timeStep));
        }
    }
}
