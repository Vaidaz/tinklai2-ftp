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

  this->fdmax = this->sockfd;
  FD_SET(this->sockfd, &this->master);

  return 0;
}

int Socket::openServer(){
  const char *port = this->port.c_str();

  int status, yes = 1;
  struct addrinfo hints, *servinfo;
  int *sockfd = &this->sockfd;

  memset(&hints, 0, sizeof(hints));   // užtikrinam, kad struktūra yra švari
  hints.ai_family = AF_UNSPEC;        // IPv4 arba IPv6, (AF_INET, AF_INET6, AF_UNSPEC)
  hints.ai_socktype = SOCK_STREAM;    // stream socket o ne dgram
  hints.ai_flags = AI_PASSIVE;        // nurodo mano IP

  // getaddrinfo();
  if ((status = getaddrinfo(NULL, port, &hints, &servinfo))) {    // pirmu argumentu siunèiamas DNS arba IP
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    return -1;
  }

  // socket();
  if((*sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1){
    printf("Could not create socket");
  }

  // perpanaudojam adresą, jei jis jau panaudotas
  if(-1 == setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))){
    return -1;
  }

  // bind();
  if(bind(*sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1){
    perror("bind");
    close( *sockfd );
    return -1;
  }

  // listen();
  if(listen(*sockfd, 10) == -1){
    printf("listen failed\n");
    close( *sockfd );
    return -1;
  }

  freeaddrinfo(servinfo);

  this->fdmax = this->sockfd;
  FD_SET(this->sockfd, &this->master);

  return 0;
}

void Socket::sendMessage(string message){
  sendMessage(this->sockfd, message);
}

void Socket::sendMessage(int sockfd, string message){
  send(sockfd, message.c_str(), message.length(), 0);
}


int Socket::isPackage(){
  struct timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 10000;

  fd_set read = this->master;

  int fdmax = this->fdmax;

  FD_ZERO(&read);
  FD_SET(sockfd, &read);

  if (select(fdmax+1, &read, NULL, NULL, &tv) == -1) {
    perror("select");
    exit(4);
  }

  return FD_ISSET(sockfd, &read);
}

string Socket::receiveMessage(){
  int numbytes;
  char buf[1000];
  memset(&buf, 0, sizeof(buf));
  if ((numbytes = recv(this->sockfd, buf, sizeof(buf)-1, 0)) == -1) {
    perror("recv");
    exit(1);
  }
  string message(buf);
  return message;
}

void Socket::handleConnections(){
  fd_set read_set = this->master;
  int i;

  if (select(this->fdmax+1, &read_set, NULL, NULL, NULL) == -1) {
    perror("select");
    exit(4);
  }

  // pereinam per egzistuojančius prisijungimus ir tikrinam
  for(i = 0; i <= this->fdmax; i++) {
    if (FD_ISSET(i, &read_set)) { // nauji duomenys
      if (i == this->sockfd) {
        acceptConnection();
      } else {
        removeConnection(i);
      }
    }
  }
}

int Socket::acceptConnection(){
  socklen_t addrlen;
  struct sockaddr_storage remoteaddr; // kliento adresas
  int newfd;
  char remoteIP[INET6_ADDRSTRLEN];

  addrlen = sizeof remoteaddr;
  newfd = accept(this->sockfd, (struct sockaddr *)&remoteaddr, &addrlen);

  if (newfd == -1) {
    perror("accept");
  } else {
    FD_SET(newfd, &this->master); // įdedam į pagrindinį sąrašą
    if (newfd > this->fdmax) {    // saugom didžiausią deskriptorių
      this->fdmax = newfd;
    }
    printf("selectserver: new connection from %s on "
      "socket %d\n",
      inet_ntop(remoteaddr.ss_family,
        get_in_addr((struct sockaddr*)&remoteaddr),
        remoteIP, INET6_ADDRSTRLEN),
      newfd);
  }

  cout << "Kazkas jungiasi" << endl;
  // sendMessage(newfd, "Sveikas :)\n");

  return newfd;
}

int Socket::removeConnection(int sockfd){
  char buf[100] = {0};
  int nbytes;

  if ((nbytes = recv(sockfd, buf, sizeof buf, 0)) <= 0) {
    if (nbytes == 0) {
      // uždarytas prisijungimas
      printf("selectserver: socket %d hung up\n", sockfd);
    } else {
      // klaida
      perror("recv");
    }
    close(sockfd);
    FD_CLR(sockfd, &this->master); // paralinam į pagrindinio sąrašo
  }
  return sockfd;
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

void Socket::disconect(){
  if(this->sockfd){
    close(this->sockfd);
  }
}

Socket::~Socket(){
  close(this->sockfd);
}
