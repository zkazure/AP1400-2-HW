#include "server.h"
#include <memory>
#include <random>
#include <string>

class Client;

Server::Server() {};

std::shared_ptr<Client> Server::add_client(std::string id) {
    if (get_client(id)) {
        while (true) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1000, 9999);
            std::string digit_4 = std::to_string(dis(gen));
            if (get_client(id+digit_4)) {
                id += digit_4;
                break;
            }
        }
    }

    auto cli = std::make_shared<Client>(id, *this);
    clients[cli] = 5;
    
    return cli;
}

std::shared_ptr<Client> Server::get_client(std::string id) {
    for (const auto& cli : clients) {
        if (cli.first->get_id() == id)
            return cli.first;
    }
    return nullptr;
}

double Server::get_wallet(std::string id) const
{
    for (auto& cli : clients) {
        if (cli.first->get_id()==id)
            return cli.second;
    }
    return 0;
}
