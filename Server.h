/*
 * Server.h
 *
 * Author: Hail Zanbar 322766353
 * Partner: Hadas Eshel 206775074
 */

#ifndef SERVER_H_
#define SERVER_H_


#include <thread>
#include <sys/socket.h>
#include "commands.h"
#include "CLI.h"

using namespace std;

// the Socket IO
class SocketIO:public DefaultIO{
    int socket;
public:
    SocketIO(int socket){ this->socket = socket;}
    virtual string read(){
        string text = "";
        char textInChar[1020] = {0};
        int bufferSize = sizeof(textInChar);
        int readBytes = recv(this->socket, textInChar, bufferSize,0);
        text = text + textInChar;
        while(readBytes == bufferSize){
            readBytes = recv(this->socket, textInChar, bufferSize,0);
            if(readBytes > 0) {
                text = text + textInChar;
            }
        }
        return text;
    }
    virtual void write(string text){
        const char* textInChar = text.c_str();
        send(this->socket, textInChar , strlen(textInChar) , 0 );
    }
    virtual void write(float f){
        float x = f;
        send(this->socket, &x, sizeof x, 0);
    }
    virtual void read(float* f){
        recv(this->socket, f, sizeof(*f), 0);
    }
    virtual ~SocketIO(){}
};

// edit your ClientHandler interface here:
class ClientHandler{
public:
    virtual void handle(int clientID)=0;
};


// you can add helper classes here and implement on the cpp file
// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
public:
    virtual void handle(int clientID){
        SocketIO io(clientID);
        CLI cli(&io);
        cli.start();
    }
};

// implement on Server.cpp
class Server {
	thread* t; // the thread to run the start() method in
    int port;
    int soc;
    volatile bool stopped;
	// you may add data members

public:
	Server(int port) throw (const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
    void sigHandler(int sigNum);
};

#endif /* SERVER_H_ */
