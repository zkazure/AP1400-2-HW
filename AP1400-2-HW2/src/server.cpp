#include "server.h"
#include <memory>
#include <random>
#include <stdexcept>
#include <string>

class Client;

Server::Server() {};

std::vector<std::string> pending_trxs;

void show_wallets(const Server& server)
{
	std::cout << std::string(20, '*') << std::endl;
	for(const auto& cli: server.clients )
		std::cout << cli.first->get_id() <<  " : "  << cli.second << std::endl;
	std::cout << std::string(20, '*') << std::endl;
}

std::shared_ptr<Client> Server::add_client(std::string id) {
    for (auto& cli : clients) {
        if (cli.first->get_id()==id) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1000, 9999);
            id += std::to_string(dis(gen));
            break;
        }
    }


    auto cli = std::make_shared<Client>(id, *this);
    clients[cli] = 5;
    
    return cli;
}

std::shared_ptr<Client> Server::get_client(std::string id) const {
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

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value) {
    int idx[2]={0};
    int cnt=0;
    for (int i=0; i<trx.size() && cnt<3; ++i) {
        if (trx[i]=='-') {
            idx[cnt] = i;
            cnt++;
        }
    }

    if (cnt!=2)
        throw std::runtime_error("invalid syntax");
    sender = trx.substr(0, idx[0]);
    receiver = trx.substr(idx[0]+1, idx[1]-idx[0]-1);
    value = std::stod(trx.substr(idx[1]+1));
    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const
{
    std::string sender, receiver;
    double value;
    parse_trx(trx, sender, receiver, value);
    if (!get_client(sender) || !get_client(receiver))
        return false;

    for (auto const cli : clients) {
        if (cli.first->get_id()==sender) {
            if (cli.second<value)
                return false;
        }
    }

    pending_trxs.push_back(trx);
    return true;
}
