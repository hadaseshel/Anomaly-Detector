
#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>

using std::ifstream;
using namespace std;

class TimeSeries{

public:

    map <string, vector<float>*> *dataTable;

	TimeSeries(const char* CSVfileName);

    int getFeaturesNum();
    vector<string>* getFeatures();
    vector<float>* getCol(const string& feature);
    float getVal(const string& feature,int j);
};

void insertFeatures(const string line, map<string, vector<float>*> *dataTable);
void insertValues(const string line, map<string, vector<float>*> *dataTable);



#endif /* TIMESERIES_H_ */
