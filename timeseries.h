
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
    vector<string> *features;

    // constructor
	TimeSeries(const char* CSVfileName);

    // destructor
    ~TimeSeries();

    int getFeaturesNum();
    vector<string>* getFeatures() const;
    vector<float>* getCol(int j);
    float getVal(int i, int j);
};

//static methods
void insertFeatures(const string line, map<string, vector<float>*> *dataTable, vector<string> *features);
void insertValues(const string line, map<string, vector<float>*> *dataTable, vector<string> *features);



#endif /* TIMESERIES_H_ */
