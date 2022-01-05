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

    if((this->soc = socket(PF_INET,SOCK_STREAM,0)) == 0){
        throw "get socket failed";
    }
}

void Server::start(ClientHandler& ch)throw(const char*){
    // to bind the server
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = port;
    if(bind(this->soc,(struct sockaddr*)&myaddr, sizeof(myaddr))<0){
        throw "the bind failed";
    }

    if(listen(this->soc, 3) < 0){
        throw "the listen failed";
    }

    int new_socket = 0;
    int addrlen = sizeof(myaddr);
    while(true){
        if((new_socket = accept(this->soc , (struct sockaddr *)&myaddr, (socklen_t*)&addrlen))<0){
        throw "the accept failed";
    	}
        ch.handle(new_socket);
    }
}

void Server::stop(){
	t->join(); // do not delete this!

}

Server::~Server() {
}

