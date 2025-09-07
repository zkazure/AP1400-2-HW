#include "client.h"
#include "server.h"
#include "crypto.h"
#include <climits>
#include <iostream>
#include <random>
#include <string>

Client::Client(std::string id, const Server& server)
: id(id), server(& server)
{
    crypto::generate_key(this->public_key, this->private_key);
}

std::string Client::get_id() {
    return this->id;
}

double Client::get_wallet() const {
    return server->get_wallet(this->id);
}

std::string Client::get_publickey() const
{
    return this->public_key;
}

std::string Client::sign(std::string txt) const
{
    return crypto::signMessage(this->private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value) const
{
    std::string trx = this->id + "-" + receiver + "-" + std::to_string(value);
    return server->add_pending_trx(trx, sign(trx));
}

size_t Client::generate_nonce() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, INT_MAX);
    return dis(gen);
}
