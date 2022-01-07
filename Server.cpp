/*
 * Server.cpp
 *
 * Author: Hail Zanbar 322766353
 * Partner: Hadas Eshel 206775074
 */

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <csignal>
#include<unistd.h>
#include <thread>

Server::Server(int port)throw(const char*) {
    this->port = port;
    this->stopped = false;

    if((this->soc = socket(PF_INET,SOCK_STREAM,0)) == 0){
        throw "get socket failed";
    }

    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = INADDR_ANY;
    myaddr.sin_port = htons(port);

    this->socketAdd = myaddr;
    if (bind(this->soc, (struct sockaddr *) &myaddr, sizeof(myaddr)) < 0) {
        throw "the bind failed";
    }

    if (listen(this->soc, 3) < 0) {
        throw "the listen failed";
    }
}

void sigHandler(int sigNum){
    cout << "sidH" << endl;
}

void Server::start(ClientHandler& ch)throw(const char*){
    this->t = new thread([&ch,this](){
        int new_socket = 0 ;
        int addrlen = sizeof(this->socketAdd);

        int iResult;
        struct timeval tv;
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(this->soc, &rfds);

        tv.tv_sec = (long)2;
        tv.tv_usec = 0;

        //signal(SIGALRM,SIG_DFL);
        while (!stopped) {
            //alarm(1);
            iResult = select(this->soc + 1, &rfds, (fd_set *) 0, (fd_set *) 0, &tv);
            if (iResult) {
                new_socket = accept(this->soc, (struct sockaddr *) &this->socketAdd, (socklen_t * ) & addrlen);
            }
            if (new_socket < 0) {
                throw "the accept failed";
            } else if (new_socket != 0) {
                ch.handle(new_socket);
                close(new_socket);
            }
            //alarm(0);
        }
        close(this->soc);
    });
}

void Server::stop(){
    this->stopped = true;
    t->join(); // do not delete this!
    //cout << "finish stop" << endl;
}

Server::~Server(){}

