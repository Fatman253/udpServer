#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <boost/thread/thread.hpp>
#include <thread>
#include <vector>

#include "udpSender.h"

struct Header {
  uint8_t key;
};

class udpServer {
 private:
  struct receiveHelper {
    receiveHelper(void *buff, size_t __len, sockaddr_in &addr, void (*cb)())
        : buffPtr(buff), port(addr.sin_port), callback(cb), len(__len) {}

    typedef void (*voidPtr)();

    void *buffPtr;
    size_t len;
    voidPtr callback;
    int port;
  };

  boost::thread threadReceive;

  std::vector<receiveHelper> selector;

  struct sockaddr_in servaddr;

  int _socket;
  int _port;

 public:
  void receiverInit();

  void receiverLoop();
  udpServer() {}

  udpServer(int port);

  // ~udpServer()

  void connectServer(int port);

  sockaddr_in createIP(char *ip, int port);

  udpSender addSender(char *__ip, int __port);

  void addReceiver(char *__ip, int __port, void *buffPtr, size_t __len,
                   void (*cb)());

  // void addReceiver(char *__ip, int __port, void *buffPtr);

  void sendMessage(const void *__buff, size_t __len);

  void recvMessage(void (*cb)(void *data, sockaddr_in *addr));

  void recvMessage();

  void start() {
    threadReceive = boost::thread(&udpServer::receiverLoop, this);
  }

  void end() { threadReceive.join(); }
  boost::thread receiverStart() {
    return boost::thread(&udpServer::receiverInit, this);
  }
};

#endif
