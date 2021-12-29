/*
 * CLI.cpp
 *
 * Author: Hadas Eshel 206775074
 * Partner: Hail Zanbar 322766353
 */

#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->commands = new vector<Command*>;
    this->detector = new HybridAnomalyDetector();
    this->reportsVector = new vector<AnomalyReport>;
    this->commands->push_back(new Command1(dio));
    this->commands->push_back(new Command2(dio, this->detector));
    this->commands->push_back(new Command3(dio));
    this->commands->push_back(new Command4(dio, this->reportsVector));
    this->commands->push_back(new Command5(dio));
    this->commands->push_back(new Command6(dio));
    this->dio = dio;
}

void CLI::start(){
    while(true) {
        this->dio->write("Welcome to the Anomaly Detection Server\n");
        this->dio->write("Please choose an option:\n");

        int size = this->commands->size();
        vector<Command *>::iterator it = this->commands->begin();
        for (int i = 0; i < size; i++) {
            this->dio->write((i + 1));
            this->dio->write(". ");
            this->dio->write((*it)->getDescription());
            it++;
            if (i != 5) {
                this->dio->write("\n");
            }
        }

        // get choice from user
        float choiceInFloat;
        this->dio->read(&choiceInFloat);
        int choice = choiceInFloat;

        // operat the wanted choice
        it = this->commands->begin();
        for (int i = 0; i < size; i++) {
           if (i+1 == choice) {
               (*it)->execute();
           }
           it++;
        }
    }
}

CLI::~CLI() {
    delete(this->dio);
    // for each Command in the vector, delete its column vector.
    while(!this->commands->empty()){
        this->commands->pop_back();
    }
    delete(this->commands);
    delete(this->reportsVector);
    delete(this->detector);
}

