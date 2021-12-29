/*
 * timeseries.h
 *
 * Author: Hadas Eshel 206775074
 * Partner: Hail Zanbar 322766353
 */
/*
 * timeseries.h
 *
 * Author: Hail Zanbar 322766353
 * Partner: Hadas Eshel 206775074
 */

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

    int getFeaturesNum() const;
    vector<string>* getFeatures() const;
    vector<float>* getCol(int j) const;
    float getVal(int i, int j) const;
};

//static methods
void insertFeatures(const string line, map<string, vector<float>*> *dataTable, vector<string> *features);
void insertValues(const string line, map<string, vector<float>*> *dataTable, vector<string> *features);



#endif /* TIMESERIES_H_ */
