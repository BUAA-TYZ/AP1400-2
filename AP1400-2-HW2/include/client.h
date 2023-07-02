#ifndef CLIENT_H
#define CLIENT_H

#include <climits>
#include <iostream>
#include <string>

#include "crypto.h"
#include "server.h"

class Server;

class Client {
public:
    Client(std::string id, const Server& server);
    std::string get_id() const { return id; }
    std::string get_publickey() const { return public_key; }
    double get_wallet() const;
    std::string sign(std::string txt) const { return crypto::signMessage(private_key, txt); }
    bool transfer_money(std::string receiver, double value) const;
    size_t generate_nonce();
private:
    Server const* const server;
    const std::string id;
    std::string public_key;
    std::string private_key;
};

#endif //CLIENT_H