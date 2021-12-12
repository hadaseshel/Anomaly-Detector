/*
 * SimpleAnomalyDetector.h
 *
 * Author: Hadas Eshel 206775074
 * Partner: Hail Zanbar 322766353
 */


#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "minCircle.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
    int indexFeature1, indexFeature2;
	float corrlation;
	Line lin_reg;
	float threshold;
    Circle minCircle;
    string typeOfCorrlation;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
	vector<correlatedFeatures> *cf;
    float correlationThreshold;
public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);

    virtual void addCorrelate(string feature1,int i, string feature2 , int c,
                              float correlate, float *colI, float *colC, int sizeOfCol);
    virtual void report(vector<AnomalyReport> *vectorOfReport, correlatedFeatures feature, Point point,  int line);

	vector<correlatedFeatures> getNormalModel(){
		return *cf;
	}

};



#endif /* SIMPLEANOMALYDETECTOR_H_ */
