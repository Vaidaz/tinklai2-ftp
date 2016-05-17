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
    string port;
    string host;
    void *get_in_addr(struct sockaddr *sa);
  public:
    Socket();
    Socket(string, string);
    void setHost(string);
    void setPort(string);
    string getHost();
    string getPort();
    int connectToServer();
    void sendMessage(string);
    int isPackage();
    string receiveMessage();
    ~Socket();
};

#endif
