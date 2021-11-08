
#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>

using std::ifstream;
using namespace std;

class TimeSeries{

public:

    char** dataTable[];

	TimeSeries(const char* CSVfileName){

        ifstream indata;
        indata.open(CSVfileName); // opens the file
        if(!indata) { // file couldn't be opened
            cerr << "Error: file could not be opened" << endl;
            exit(1);
        }
        int lines_num = 0;
        string line;
        while (getline(indata, line)) { // keep reading until end-of-file
            lines_num++;
        }
        indata.close();
	}

    int getFeaturesNum() {}
    vector<string> getFeatures() {}
    vector<string> getCol(int j) {}
    int getVal(int i, int j) {}
};



#endif /* TIMESERIES_H_ */
