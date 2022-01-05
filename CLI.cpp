/*
 * CLI.cpp
 *
 * Author: Hadas Eshel 206775074
 * Partner: Hail Zanbar 322766353
 */

#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->commands = new vector<Command*>;
    this->detector = new HybridAnomalyDetector();
    this->reportsVector = new vector<AnomalyReport>;
    this->timeStepsNum = 0;
    this->commands->push_back(new Command1(dio, &(this->timeStepsNum)));
    this->commands->push_back(new Command2(dio, this->detector));
    this->commands->push_back(new Command3(dio, this->detector, this->reportsVector));
    this->commands->push_back(new Command4(dio, this->reportsVector));
    this->commands->push_back(new Command5(dio, this->reportsVector, &(this->timeStepsNum)));
    this->commands->push_back(new Command6(dio));
}

void CLI::start(){
    while (true) {
        this->dio->write("Welcome to the Anomaly Detection Server.\n");
        this->dio->write("Please choose an option:\n");

        int size = this->commands->size();
        vector<Command *>::iterator it = this->commands->begin();
        for (int i = 0; i < size; i++) {
            this->dio->write(i + 1);
            this->dio->write(".");
            this->dio->write((*it)->getDescription() + "\n");
            it++;
        }

        // get choice from user by string
        string choice = this->dio->read();
        stringstream s(choice);
        int option = 0;
        s >> option;
        if(option == 6) {
            break;
        }
        this->commands->at(option - 1)->execute();
    }
}

CLI::~CLI() {
    //delete(this->dio);
    // for each Command in the vector, delete its column vector.
    while(!this->commands->empty()){
        this->commands->pop_back();
    }
    delete(this->commands);
    delete(this->reportsVector);
    delete(this->detector);
}

