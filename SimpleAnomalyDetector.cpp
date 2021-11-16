
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    this->cf = new vector<correlatedFeatures>;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    delete(this->cf);
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    string *features = ts.getFeatures()->data();
    int n = ts.getFeaturesNum();
    int sizeOfCol = (int)ts.getCol(0)->size();
    for (int i = 0; i < n; i++) {
        int c = -1;
        float m = 0.9;
        for (int j = i + 1; j < n; j++) {
            float *colI = ts.getCol(i)->data(), *colJ = ts.getCol(j)->data();
            float p = pearson(colI, colJ, sizeOfCol);
            if (p < 0) {
                p = -p;
            }
            if (p > m) {
                m = p;
                c = j;
            }
        }
        if (c != -1) {
            // associate 𝑓𝑖 and 𝑓𝑗 as correlated features
            string feature1 = features[i], feature2 = features[c];
            float corrlation = m;
            // ***********************************************************
            float *colI = ts.getCol(i)->data(), *colC = ts.getCol(c)->data();
            Point * point[sizeOfCol];
            // fill the arries of point value.
            for (int k = 0; k < sizeOfCol; k++){
                point[k] = new Point(colI[k], colC[k]);
            }
            // ***********************************************************
            Line lin_reg = linear_reg(point, sizeOfCol);
            float threshold = 0;
            // ***********************************************************
            for (int p = 0; p < sizeOfCol; p++) {
                float devResult = dev(*point[p], lin_reg);
                if (devResult > threshold) {
                    threshold = devResult;
                }
            }
            // ***********************************************************
            for (int d = 0; d < sizeOfCol; d++) {
                delete(point[d]);
            }
            correlatedFeatures corr = {feature1, feature2, corrlation, lin_reg, threshold};
            this->cf->push_back(corr);
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {

}
