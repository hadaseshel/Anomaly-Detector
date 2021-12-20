/*
 * CLI.cpp
 *
 * Author: Hadas Eshel 206775074
 * Partner: Hail Zanbar 322766353
 */

#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->commands = new vector<Command*>;
    this->commands->push_back(new Command1(dio));
    this->commands->push_back(new Command2(dio));
    this->commands->push_back(new Command3(dio));
    this->commands->push_back(new Command4(dio));
    this->commands->push_back(new Command5(dio));
    this->commands->push_back(new Command6(dio));
    this->dio = dio;
}

void CLI::start(){
}


CLI::~CLI() {
}

