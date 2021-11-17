
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
            float *colI = ts.getCol(i)->data(), *colC = ts.getCol(c)->data();
            Line lin_reg = linear_reg(colI, colC, sizeOfCol);
            float threshold = calculationThreshold(colI, colC, sizeOfCol, lin_reg);
            // create the correlated.
            correlatedFeatures corr = {feature1, feature2, i, c, corrlation, lin_reg, (float )1.1*threshold};
            // push the correlated feateus.
            this->cf->push_back(corr);
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> *reports = new vector<AnomalyReport>;
    int n = ts.getFeaturesNum();
    // go throw the correlatedFeatures
    for (vector<correlatedFeatures>::iterator it = this->cf->begin(); it != this->cf->end(); it++) {
        // go throw liens
        for (int r = 0; r < ts.getCol(0)->size(); r++) {
                // go throw colum first
                for (int i = 0; i < n; i++) {
                    if (i == it->indexFeature1) {
                        // go throw colum secend
                        for (int j = i+1; j < n; j++) {
                            if (j == it->indexFeature2) {
                                float devResult = dev(Point(ts.getVal(r,i), ts.getVal(r,j)), it->lin_reg);
                                if (devResult > it->threshold) {
                                    string description = it->feature1 + "-" + it->feature2;
                                    long timeStep = r + 1;
                                    reports->push_back(AnomalyReport(description,timeStep));
                                }
                            }
                        }
                    }
                }
        }
    }
    return *reports;
    delete(reports);
}
