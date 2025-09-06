#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include "server.h"

class Client
{
 public:
    Client(std::string id, const Server* server);

 private:
    const Server* const server;
    const std::string id;
 std::string public_key;
 std::string private_key;
};

#endif //CLIENT_H
