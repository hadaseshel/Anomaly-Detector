#include "timeseries.h"
#include <vector>
#include <sstream>


using std::ifstream;
using namespace std;

TimeSeries::TimeSeries(const char *CSVfileName) {

    this->dataTable = new map<string, vector<float>*>();
    ifstream indata;
    indata.open(CSVfileName); // opens the file
    if(!indata) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }

    int lines_num = 0;
    string line;
    while (getline(indata, line)) { // keep reading until end-of-file

        // insert the first line as keys to the map, and then the values
        if (lines_num == 0) {
            insertFeatures(line, this->dataTable);
        } else {
            insertValues(line, this->dataTable);
        }
        lines_num++;
    }
    indata.close();
}

int TimeSeries::getFeaturesNum() {
    return (int)(this->dataTable)->size();
}

vector<string>* TimeSeries::getFeatures() {
    vector<string>* features = new vector<string>;
    map<string, vector<float>*>::iterator it;

    // for each feature in the table, push it to the features vector.
    for (it = dataTable->begin(); it != dataTable->end(); it++) {
        features->push_back(it->first);
    }
    return features;
}

vector<float>* TimeSeries::getCol(const string& feature) {
    vector<float>* col = new vector<float>;
    auto it = dataTable->find(feature);
    if (it != dataTable->end()) {
        col = it->second;
    }
    return col;
}

float TimeSeries::getVal(const string &feature, int j) {
    auto it = dataTable->find(feature);
    float val = it->second->at(j);
    return val;
}

// insert the first line of the table (the features) to the map as the keys.
void insertFeatures(const string line, map<string, vector<float>*> *dataTable) {
    stringstream ss (line);
    string item;
    vector<string> features;

    // split the line by comma and insert the strings to vector
    while (getline (ss, item, ',')) {
        features.push_back (item);
    }

    for (string feature : features) {
        dataTable->insert(pair<string, vector<float>*>(feature, new vector<float>));
    }

}

// insert each line of the table as values to the vector of each key (character).
void insertValues(const string line, map<string, vector<float>*> *dataTable) {
    stringstream ss (line);
    string item;
    vector<float> values;

    // split the line by comma and insert the strings to vector
    while (getline (ss, item, ',')) {
        values.push_back (stof(item));
    }

    int index = 0;
    map<string, vector<float>*>::iterator it;

    // for each feature in the table, insert to its values vector the appropriate value.
    for (it = dataTable->begin(); it != dataTable->end(); it++) {
        it->second->push_back(values[index]);
        index++;
    }
}


