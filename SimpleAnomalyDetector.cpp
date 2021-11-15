
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    this->cf = new vector<correlatedFeatures>;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    delete(this->cf);
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    int n = ts.getFeaturesNum();
    for (int i = 0; i < n; i++) {
        int c = -1;
        float m = 0;
        for (int j = i + 1; j < n; j++) {
            float * colI = &ts.getCol(i)[0], *colJ = &ts.getCol(j)[0];
            float p = pearson(colI, colJ, ts.getFeaturesNum());
            if (p > m) {
                p = m;
                c = j;
            }
            // need numbers of liens in ts
        }
        if (c != -1) {
            // associate 𝑓𝑖 and 𝑓𝑗 as correlated features
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){

}

