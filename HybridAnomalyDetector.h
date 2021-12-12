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
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();

    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
