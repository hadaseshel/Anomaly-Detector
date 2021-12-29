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
    virtual string read();
    virtual void write(string text);
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~StandardIO(){}
};

// ********************** function of StandardIO **********************
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

// command 1 in the menu "uplode a time series CVS file"
class Command1: public Command{
public:
    Command1(DefaultIO* dio):Command(dio){}
    void execute();
    ~Command1(){}
};

// command 2 in the menu "algorithm setting"
class Command2: public Command{
public:
    Command2(DefaultIO* dio):Command(dio){this->description = "algorithm settings";}
    void execute();
    ~Command2(){}
};

// command 3 in the menu "detect anomalies"
class Command3: public Command{
public:
    Command3(DefaultIO* dio):Command(dio){}
    void execute();
    ~Command3(){}
};

// command 4 in the menu "display results"
class Command4: public Command{
public:
    Command4(DefaultIO* dio):Command(dio){this->description = "display results";}
    void execute();
    ~Command4(){}
};

// command 5 in the menu "upload anomalies and analyze results"
class Command5: public Command{
public:
    Command5(DefaultIO* dio):Command(dio){}
    void execute();
    ~Command5(){}
};

// command 6 in the menu "exit"
class Command6: public Command{
public:
    Command6(DefaultIO* dio):Command(dio){this->description = "exit";}
    void execute();
    ~Command6(){}
};

// function of exit
void Command6::execute() {
    exit;
}

#endif /* COMMANDS_H_ */
