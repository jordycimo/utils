#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

static void relay(int sock) {
  char buf[4096];

  fd_set fds;

  for(;;) {
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    FD_SET(sock, &fds);

    if (select(sock + 1, &fds, NULL, NULL, NULL) < 0) {
      break;
    }

    if (FD_ISSET(STDIN_FILENO, &fds)) {
      ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));

      if (n <= 0) {
        break;
      }

      write(sock, buf, (size_t)n);
    }

    if (FD_ISSET(sock, &fds)) {
      ssize_t n = read(sock, buf, sizeof(buf));

      if (n <= 0) {
        break;
      }

      write(STDOUT_FILENO, buf, (size_t)n);
    }
  }
}


