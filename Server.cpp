/*
 * Server.cpp
 *
 * Author: Hail Zanbar 322766353
 * Partner: Hadas Eshel 206775074
 */

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>

Server::Server(int port)throw (const char*) {
    this->port = port;
    this->stopped = false;

    if((this->soc = socket(PF_INET,SOCK_STREAM,0)) == 0){
        throw "get socket failed";
    }

    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = port;
    if (bind(this->soc, (struct sockaddr *) &myaddr, sizeof(myaddr)) < 0) {
        throw "the bind failed";
    }

    if (listen(this->soc, 3) < 0) {
        throw "the listen failed";
    }
}

void Server::sigHandler(int sigNum){
    this->stopped = true;
}

void Server::start(ClientHandler& ch)throw(const char*){
    t=new thread([&ch,this]() {
        int new_socket = 0;
        int addrlen = sizeof(myaddr);
        signal(SIGALRM,sigHandler);
        while (true) {
            alarm(1);
            new_socket = accept(this->soc, (struct sockaddr *) &myaddr, (socklen_t * ) & addrlen);
            if (new_socket < 0) {
                throw "the accept failed";
            } else if (new_socket != 0) {
                ch.handle(new_socket);
                close(new_socket);
            }
            alarm(0);
        }
    }
}

void Server::stop(){
	t->join(); // do not delete this!
    close(this->soc);
}

Server::~Server() {
}

