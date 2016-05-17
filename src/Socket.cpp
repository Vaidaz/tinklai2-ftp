#include "./Socket.h"

Socket::Socket(){
}

Socket::Socket(string host, string port){
  this->host = host;
  this->port = port;
}

void *Socket::get_in_addr(struct sockaddr *sa){
  if (sa->sa_family == AF_INET) {
      return &(((struct sockaddr_in*)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int Socket::connectToServer(){

  const char *host = this->host.c_str();
  const char *port = this->port.c_str();
  int *sockfd = &this->sockfd;

  struct addrinfo hints, *servinfo, *p;
  int rv;
  char s[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ((rv = getaddrinfo(host, port, &hints, &servinfo)) != 0) {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      return 1;
  }

  // loop through all the results and connect to the first we can
  for(p = servinfo; p != NULL; p = p->ai_next) {
      if ((*sockfd = socket(p->ai_family, p->ai_socktype,
              p->ai_protocol)) == -1) {
          perror("client: socket");
          continue;
      }

      if (connect(*sockfd, p->ai_addr, p->ai_addrlen) == -1) {
          close(*sockfd);
          perror("client: connect");
          continue;
      }

      break;
  }

  if (p == NULL) {
      fprintf(stderr, "client: failed to connect\n");
      return 2;
  }

  inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
          s, sizeof s);

  freeaddrinfo(servinfo); // all done with this structure
  return 0;
}

void Socket::sendMessage(string message){
  send(this->sockfd, message.c_str(), message.length(), 0);
}

int Socket::isPackage(){
  struct timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 10000;

  fd_set master;
  int fdmax = sockfd;

  FD_ZERO(&master);
  FD_SET(sockfd, &master);

  if (select(fdmax+1, &master, NULL, NULL, &tv) == -1) {
    perror("select");
    exit(4);
  }

  return FD_ISSET(sockfd, &master);
}

string Socket::receiveMessage(){
  int numbytes;
  char buf[1000];
  if ((numbytes = recv(this->sockfd, buf, sizeof(buf)-1, 0)) == -1) {
    perror("recv");
    exit(1);
  }
  string message(buf);
  return message;
}

void Socket::setHost(string host){
  this->host = host;
}

void Socket::setPort(string port){
  this->port = port;
}

string Socket::getHost(){
  return this->host;
}

string Socket::getPort(){
  return this->port;
}

Socket::~Socket(){
  close(this->sockfd);
}
