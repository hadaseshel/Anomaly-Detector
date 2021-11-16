
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    this->cf = new vector<correlatedFeatures>;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    delete(this->cf);
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    int n = ts.getFeaturesNum();
    for (int i = 0; i < n; i++) {
        int c = -1;
        float m = 0.9;
        for (int j = i + 1; j < n; j++) {
            float *colI = ts.getCol(i)->data(), *colJ = ts.getCol(j)->data();
            float p = pearson(colI, colJ, (int) ts.getCol(i)->size());
            if (p > m) {
                m = p;
                c = j;
            }
            if (c != -1) {
                 // associate 𝑓𝑖 and 𝑓𝑗 as correlated features
            }
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {

}
