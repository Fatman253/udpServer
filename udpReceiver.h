#ifndef UDP_RECEIVER_HEADER
#define UDP_RECEIVER_HEADER

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "iostream"

// const boost::function<void(P)>& _callback

// template <typename P, typename Enabled = void>
// class SubscriptionCallbackHelperT : public SubscriptionCallbackHelper
// typedef boost::function<void(typename Adapter::Parameter)> Callback;

// template <typename M>
// class udpCallback {
//  private:
//   using callback = void (*)(M);

//   callback _callback;

//  public:
//   udpCallback(void(*fp)) {}

//   void call(void *buf) { _callback(reinterpret_cast<M *>(buf)); }
// };

// class udpReceiver {
//  private:
//   sockaddr_in addr;
//   int _socket;

//   using callback = void(*);

//   callback _callback;

//   //   template <typename P>
//   //   P jujur;

//  public:
//   template <class M>
//   udpReceiver(char *ip, int port, int __socket, void (*fp)(M)) {
//     addr.sin_addr.s_addr = inet_addr(ip);
//     addr.sin_port = htons(port);
//     addr.sin_family = AF_INET;

//     _socket = __socket;
//   }
// };

#endif
