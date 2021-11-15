#include "timeseries.h"
#include <vector>
#include <sstream>


using std::ifstream;
using namespace std;

// constructor
TimeSeries::TimeSeries(const char *CSVfileName) {

    this->dataTable = new map<string, vector<float>*>();
    this->features = new vector<string>();
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
            insertFeatures(line, this->dataTable, this->features);
        } else {
            insertValues(line, this->dataTable, this->features);
        }
        lines_num++;
    }
    indata.close();
}

int TimeSeries::getFeaturesNum() {
    return (int)(this->features)->size();
}

// getter of the features vector.
vector<string>* TimeSeries::getFeatures() const {
    return features;
}

// get the j column.
vector<float>* TimeSeries::getCol(int j) {

    // We get the name of the desired column from the feature vector.
    string feature = this->features->at(j);
    vector<float>* col = new vector<float>;

    // get the desired column from the map.
    auto it = dataTable->find(feature);
    if (it != dataTable->end()) {
        col = it->second;
    }
    return col;
}

float TimeSeries::getVal(int i, int j) {

    // We get the name of the desired column from the feature vector.
    string feature = this->features->at(j);
    auto it = dataTable->find(feature);
    float val = it->second->at(i);
    return val;
}

// destructor
TimeSeries::~TimeSeries() {
    map<string, vector<float>*>::iterator it;

    // for each feature in the table, delete its column vector.
    for (it = dataTable->begin(); it != dataTable->end(); it++) {
        delete (it->second);
    }

    // delete the map and the features vector.
    delete (this->dataTable);
    delete (this->features);
}

// insert the first line of the table (the features) to the map as the keys.
void insertFeatures(const string line, map<string, vector<float>*> *dataTable, vector<string> *features) {
    stringstream ss (line);
    string item;

    // split the line by comma and insert the strings to vector
    while (getline (ss, item, ',')) {
        features->push_back(item);
    }

    for (string feature : *features) {
        dataTable->insert(pair<string, vector<float>*>(feature, new vector<float>));
    }

}

// insert each line of the table as values to the vector of each key (character).
void insertValues(const string line, map<string, vector<float>*> *dataTable, vector<string> *features) {
    stringstream ss (line);
    string item;
    vector<float> values;

    // split the line by comma and insert the strings to vector
    while (getline (ss, item, ',')) {
        values.push_back (stof(item));
    }

    // for each feature in the table, insert to its values vector the appropriate value.
    for (int i = 0; i < features->size(); i++) {
        auto it = dataTable->find(features->at(i));
        it->second->push_back(values[i]);
    }
}


