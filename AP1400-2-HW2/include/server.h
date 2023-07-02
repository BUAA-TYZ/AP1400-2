#ifndef SERVER_H
#define SERVER_H

#include <map>
#include <memory>
#include <random>
#include <regex>
#include <string>

#include "client.h"
#include "crypto.h"

extern std::vector<std::string> pending_trxs;

class Client;
class Server {
public:
    Server() = default;
    std::shared_ptr<Client> add_client(std::string id);
    std::shared_ptr<Client> get_client(std::string id) const;
    double get_wallet(const std::string id) const;
    static bool parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value);
    bool add_pending_trx(std::string trx, std::string signature) const;
    size_t mine();
private:
    std::map<std::shared_ptr<Client>, double> clients;
};

extern void show_wallets(const Server& server);
#endif //SERVER_H