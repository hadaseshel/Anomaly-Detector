/*
 * HybridAnomalyDetector.cpp
 *
 * Author: Hadas Eshel 206775074
 * Partner: Hail Zanbar 322766353
 */
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
    SimpleAnomalyDetector();
	// TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

void HybridAnomalyDetector::addCorrelate(string feature1, int i, string feature2 , int c,float correlate,
                                    float *colI, float *colC, int sizeOfCol){

}

void HybridAnomalyDetector::report(vector<AnomalyReport> *vectorOfReport, correlatedFeatures feature,
                                   Point point,  int line) {
    if (feature.typeOfCorrlation == "line") {
        SimpleAnomalyDetector::report(vectorOfReport, feature, point, line);
    } else {

    }
}