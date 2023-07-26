#include "udpServer.h"

udpServer::udpServer(int port) { connectServer(port); }

void udpServer::connectServer(int port) {
  _port = port;

  struct sockaddr_in servaddr;

  bzero(&servaddr, sizeof(servaddr));
  _socket = socket(AF_INET, SOCK_DGRAM, 0);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(_port);
  servaddr.sin_family = AF_INET;

  bind(_socket, (struct sockaddr *)&servaddr, sizeof(servaddr));
}

sockaddr_in udpServer::createIP(char *ip, int port) {
  sockaddr_in addr;
  addr.sin_addr.s_addr = inet_addr(ip);
  addr.sin_port = htons(port);
  addr.sin_family = AF_INET;
  return addr;
}

void udpServer::sendMessage(const void *__buff, size_t __len) {
  struct sockaddr_in cliaddr;

  cliaddr.sin_addr.s_addr = inet_addr("192.168.0.4");
  cliaddr.sin_port = htons(2002);
  cliaddr.sin_family = AF_INET;

  sendto(_socket, __buff, __len, 0, (struct sockaddr *)&cliaddr,
         sizeof(cliaddr));
}

void udpServer::recvMessage(void (*cb)(void *data, sockaddr_in *addr)) {
  uint8_t _buffer[1024] = {0};
  struct sockaddr_in cliaddr;
  uint32_t len = sizeof(cliaddr);
  recvfrom(_socket, _buffer, 1024, 0, (struct sockaddr *)&cliaddr, &len);
  cb(_buffer, &cliaddr);
}

void udpServer::recvMessage() {
  uint8_t _buffer[1024] = {0};
  struct sockaddr_in addr;
  uint32_t len = sizeof(addr);
  recvfrom(_socket, _buffer, 1024, 0, (struct sockaddr *)&addr, &len);

  for (auto &hehe : selector) {
    if (addr.sin_port == hehe.port) {
      memcpy(hehe.buffPtr, _buffer, hehe.len);
      hehe.callback();
      break;
    }
  }
}

udpSender udpServer::addSender(char *__ip, int __port) {
  return udpSender(__ip, __port, _socket);
}

void udpServer::receiverLoop() {
  int count = 0;
  while (1) {
    recvMessage();
  }
}

void udpServer::receiverInit() {
  boost::thread receiverThread(&udpServer::receiverLoop, this);

  receiverThread.join();
}

void udpServer::addReceiver(char *__ip, int __port, void *buffPtr, size_t __len,
                            void (*cb)()) {
  struct sockaddr_in addr;

  addr.sin_addr.s_addr = inet_addr(__ip);
  addr.sin_port = htons(__port);
  addr.sin_family = AF_INET;

  selector.push_back(receiveHelper(buffPtr, __len, addr, cb));
}