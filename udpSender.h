#ifndef UDP_SENDER_HEADER
#define UDP_SENDER_HEADER

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "iostream"

class udpSender {
 private:
  sockaddr_in addr;
  int _socket;

 public:
  udpSender(char *__ip, int __port, int __socket);

  void send(const void *__buff, size_t __len);

  template <typename T>
  void put(T *__buff) {
    sendto(_socket, __buff, sizeof(*__buff), 0, (struct sockaddr *)&addr,
           sizeof(addr));
  }
};

#endif
