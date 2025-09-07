#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <map>
#include <memory>
#include "client.h"
#include <vector>

class Client;
class Server;

void show_wallets(const Server& server);
extern std::vector<std::string> pending_trxs;

class Server {
 public:
    Server();
 std::shared_ptr<Client> add_client(std::string id);
 std::shared_ptr<Client> get_client(std::string id) const;
 double get_wallet(std::string id) const;
 static bool parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value);
 bool add_pending_trx(std::string trx, std::string signature) const;

 private:
    friend void show_wallets(const Server& server);
 std::map<std::shared_ptr<Client>, double> clients;
};

void show_wallets(const Server& server);
#endif //SERVER_H
