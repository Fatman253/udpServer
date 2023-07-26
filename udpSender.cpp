#include "udpSender.h"

udpSender::udpSender(char *__ip, int __port, int __socket) {
  addr.sin_addr.s_addr = inet_addr(__ip);
  addr.sin_port = htons(__port);
  addr.sin_family = AF_INET;

  _socket = __socket;
}

void udpSender::send(const void *__buff, size_t __len) {
  sendto(_socket, __buff, __len, 0, (struct sockaddr *)&addr, sizeof(addr));
}

