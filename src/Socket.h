#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

class Socket {
  private:
    int sockfd;
    int fdmax;
    fd_set master;
    string port;
    string host;
    void *get_in_addr(struct sockaddr *sa);
    int acceptConnection();
    int removeConnection(int);
  public:
    Socket();
    Socket(string, string);
    void setHost(string);
    void setPort(string);
    string getHost();
    string getPort();
    int connectToServer();
    int openServer();
    void sendMessage(string);
    void sendMessage(int, string);
    int isPackage();
    void handleConnections();
    string receiveMessage();
    void disconect();
    ~Socket();
};

#endif
