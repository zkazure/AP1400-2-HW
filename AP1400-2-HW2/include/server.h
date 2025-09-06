#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <map>
#include <memory>
#include "client.h"

class Client;

class Server {
 public:
    Server();
 std::shared_ptr<Client> add_client(std::string id);
 std::shared_ptr<Client> get_client(std::string id) const;
 double get_wallet(std::string id) const;
    
 private:
 std::map<std::shared_ptr<Client>, double> clients;
};

#endif //SERVER_H
