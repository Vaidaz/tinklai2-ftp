#include "./StdioHelper.h"

int StdioHelper::isInput(){
  struct timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 100000;

  fd_set master;
  int fdmax = STDIN_FILENO;

  FD_ZERO(&master);
  FD_SET(STDIN_FILENO, &master);

  if (select(fdmax+1, &master, NULL, NULL, &tv) == -1) {
    perror("select");
    exit(4);
  }

  return FD_ISSET(STDIN_FILENO, &master);
}
