/*
 * commands.h
 *
 * Author: Hadas Eshel 206775074
 * Partner: Hail Zanbar 322766353
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

	// you may add additional methods here
};

// you may add here helper classes

// the Standard IO
class StandardIO:public DefaultIO{
public:
    StandardIO(){}
    virtual string read() {
        string input;
        cin >> input;
        return input;
    }
    virtual void write(string text) {
        cout << text;
    }
    virtual void write(float f) {
        cout << f;
    }
    virtual void read(float* f) {
        cin >> *f;
    }
    virtual ~StandardIO(){}
};

// ********************** function of StandardIO **********************
/*
string StandardIO::read() {
    string input;
    cin >> input;
    return input;
}

void StandardIO::write(string text){
    cout << text;
}

void StandardIO::write(float f) {
    cout << f;
}

void StandardIO::read(float *f) {
    cin >> *f;
}
 */


// the Socket IO
class SocketIO:public DefaultIO{
public:
    SocketIO(){}
    virtual string read();
    virtual void write(string text);
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~SocketIO(){}
};


// you may edit this class
class Command{
protected:
    string description; // i added description
	DefaultIO* dio;
public:
	Command(DefaultIO* dio):dio(dio){}
	virtual void execute()=0;
    string getDescription(){return this->description;}
	virtual ~Command(){}
};

// implement here your command classes

// command 1 in the menu "upload a time series CVS file"
class Command1: public Command{
    int* stepsNum;
public:
    Command1(DefaultIO* dio, int* num):Command(dio){
        this->description = "upload a time series csv file";
        this->stepsNum = num;
    }

    void execute() {

        // will count the lines in the test csv file.
        int testCount;

        // 2 times - for the train file and the test file.
        for (int i = 0; i < 2; i++) {

            // zero test counter in order to count only the test lines.
            testCount = 0;
            ofstream file;
            if (i == 0) {

                // create train file
                ofstream file("anomalyTrain.csv");
                dio->write("Please upload your local train CSV file.");
            } else {

                // create train file
                ofstream file("anomalyTest.csv");
                dio->write("Please upload your local test CSV file.");
            }
            string line = dio->read();
            while (line != "done\n") {
                file << line << std::endl;
                line = dio->read();
                testCount++;
            }

            /*
            // convert the string to a char array
            int len = data.length();
            char data_array[len + 1];
            strcpy(data_array, data.c_str());


            // create str stream for getline
            stringstream sstr(data);
            string line;
            getline(sstr, line, '\n');

            // write the data to the file
            while (line.compare("done") != 0) {
                file << line << '\n' << std::endl;
                getline(sstr, line, '\n');
            }
             */
            dio->write("Upload complete.");
            file.close();
        }
        *(this->stepsNum) = testCount - 1;
    }
    ~Command1(){}
};

// command 2 in the menu "algorithm setting"
class Command2: public Command{
    HybridAnomalyDetector detector;
public:
    Command2(DefaultIO* dio, HybridAnomalyDetector *hibridDetector):Command(dio){
        this->description = "algorithm settings";
        this->detector = *hibridDetector;
    }
    void execute(){
        float newThreshold;
        while(true){
            // worte the option
            this->dio->write("The current correlation threshold is ");
            this->dio->write(this->detector.getThresholdOfCorrelationOfSimple());
            this->dio->write("\n");
            this->dio->read(&newThreshold);
            if ((newThreshold < 1)&&(newThreshold > 0)) {
                this->detector.setThresholdOfCorrelationOfSimple(newThreshold);
                break;
            }
            this->dio->write("please choose a value between 0 and 1.\n");
        }
    }
    ~Command2(){}
};

// command 3 in the menu "detect anomalies"
class Command3: public Command{
public:
    HybridAnomalyDetector *detector;
    vector<AnomalyReport> *reportsVector;
public:
    Command3(DefaultIO* dio,HybridAnomalyDetector *det, vector<AnomalyReport> *reports ):Command(dio){
            this->description = "detect anomalies";
            this->detector = det;
            this->reportsVector = reports;
    }
    void execute() {
        TimeSeries timeSerTrain("anomalyTrain.csv");
        this->detector->learnNormal(timeSerTrain);
        TimeSeries timeSerTest("anomalyTest.csv");
        *(this->reportsVector) = this->detector->detect(timeSerTest);
        this->dio->write("anomaly detection complete.");
    }
    ~Command3(){}
};

// command 4 in the menu "display results"
class Command4: public Command{
    vector<AnomalyReport>* reportInVectors;
public:
    Command4(DefaultIO* dio, vector<AnomalyReport> *reportVectors):Command(dio){
        this->description = "display results";
        this->reportInVectors = reportVectors;
    }
    void execute(){
        // unupdate loop
        vector<AnomalyReport>::iterator it;
        for(it = this->reportInVectors->begin(); it != this->reportInVectors->end(); it++){
            this->dio->write(it->timeStep);
            this->dio->write("\t");
            this->dio->write(it->timeStep);
        }
        this->dio->write("Done.");
    }
    ~Command4(){}
};

// command 5 in the menu "upload anomalies and analyze results"
class Command5: public Command{
    vector<AnomalyReport> *reportsVector;
    int* linesNum;
public:
    Command5(DefaultIO* dio, vector<AnomalyReport> *reports, int* num):Command(dio){
        this->description = "upload anomalies and analyze results";
        this->reportsVector = reports;
        this->linesNum = num;
    }

    // enter the data of the reports of the client to a vector.
    vector<pair <long, long>>* getClientsReport() {
        vector<pair<long, long>>* repVec = new vector<pair<long, long>>;
        char delim = ',';
        string line = dio->read();
        while (line != "done\n") {
            string start, end;
            stringstream ss(line);

            // split each line to stat time and end time.
            getline(ss, start, delim);
            getline(ss, end, delim);
            long s = 0, e = 0;

            // convert the times from strings to ints.
            stringstream ss1(start);
            stringstream ss2(end);
            ss1 >> s;
            ss2 >> e;

            pair<long, long> p = make_pair(s, e);
            repVec->push_back(p);
        }
        return repVec;
    }

    vector<pair <long, long>>* getMyReport(vector<AnomalyReport>* reportsVec) {
        vector<pair <long, long>>* myRep = new vector<pair <long, long>>;
        int i = 0;
        vector<AnomalyReport> reports = *(reportsVec);
        int len = reports.size();

        // go over the reports in the vector and union the reports
        // that have the same description and continuity in time.
        while (i < len) {
            long start = (reports.at(i)).timeStep;
            long end = start;
            i++;
            while(i < len && (reports.at(i)).timeStep - 1 == (reports.at(i-1)).timeStep &&
                        (reports.at(i)).description == (reports.at(i-1)).description) {
                end++;
                i++;
            }
            pair<long, long> p = make_pair(start, end);
            myRep->push_back(p);
        }
        return myRep;
    }

    void execute() {
        dio->write("Please upload your local anomalies file.");
        vector<pair <long, long>>* clientRep = getClientsReport();
        vector<pair <long, long>>* myRep = getMyReport(this->reportsVector);
        long P = clientRep->size();
        long anomalyTime = 0;
        for (pair <long, long> time : *(clientRep)) {
            anomalyTime += (time.second - time.first + 1);
        }
        long N = *(this->linesNum) - anomalyTime;
        long TP = 0;
        for (pair <long, long> myTime : *(myRep)) {
            for (pair <long, long> clTime : *(clientRep)) {
                if (clTime.first <= myTime.first && myTime.first <= clTime.second ||
                    clTime.first <= myTime.second && myTime.second <= clTime.second ||
                    myTime.first <= clTime.first && clTime.first <= myTime.second) {
                    TP++;
                }
            }
        }
        long FP = myRep->size() - TP;
        double trueRate = TP / P;
        double falseRate = FP / N;
        std::stringstream stream;
        stream << std::fixed << std::setprecision(3) << trueRate;
        std::string t = stream.str();
        stream << std::fixed << std::setprecision(3) << falseRate;
        std::string f = stream.str();
        dio->write("True Positive Rate: " + t +
                   "\nFalse Positive Rate: " + f);
    }

    ~Command5(){}
};

// command 6 in the menu "exit"
class Command6: public Command{
public:
    Command6(DefaultIO* dio):Command(dio){this->description = "exit";}
    void execute(){
        exit;
    }
    ~Command6(){}
};

#endif /* COMMANDS_H_ */
