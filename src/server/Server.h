#ifndef SERVER_H
#define SERVER_H

class Server{
private:
  /**
   * The port on which the server,
   * listens for incoming tcp requests.
  */
  int p;
public:
  Server(int port):p(port){}
};
#endif
