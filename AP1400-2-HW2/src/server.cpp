#include "server.h"

std::vector<std::string> pending_trxs;

std::shared_ptr<Client> Server::add_client(std::string id) {
    bool flag = true;
    for (const auto& iter : clients) {
        if (iter.first->get_id() == id) {
            flag = false;
            break;
        }
    }
    if (flag == false) {
        std::random_device r;
        std::default_random_engine e(r());
        std::uniform_int_distribution u(1000, 9999);
        id += std::to_string(u(e));
    }
    auto cln = std::make_shared<Client> (id, *this);
    clients[cln] = 5;
    return cln;
}

std::shared_ptr<Client> Server::get_client(std::string id) const {
    for (const auto& iter : clients) {
        if (iter.first->get_id() == id) {
            return iter.first;
        }
    }
    return nullptr;
}

double Server::get_wallet(const std::string id) const {
    for (const auto& iter : clients) {
        if (iter.first->get_id() == id) {
            return iter.second;
        }
    }
    return 0;
}

// See try
bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value) {
    std::regex base_regex("(\\w+)-(\\w+)-(\\d+\\.\\d+)");
    std::smatch base_match;
    if (std::regex_match(trx, base_match, base_regex)) {
        sender = base_match[1].str();
        receiver = base_match[2].str();
        value = std::stod(base_match[3].str());
        return true;
    }
    throw std::runtime_error("Parse_trx : the pattern doesn't match.");
    return false;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const {
    std::string sender_id, receiver_id;
    double value;
    if (Server::parse_trx(trx, sender_id, receiver_id, value)) {
        auto sender = get_client(sender_id);
        auto receiver = get_client(receiver_id);
        // Ensure that they are something.
        if (!sender || !receiver) { return false; }
        bool authentic = crypto::verifySignature(sender->get_publickey(), trx, signature);
        if (authentic && value < clients.at(sender)) {
            pending_trxs.emplace_back(trx);
            return true;
        }
    }
    return false;
}

size_t Server::mine() {
    std::string mempool;
    for (auto& s : pending_trxs) {
        mempool += s;
    }
    bool flag =  false;
    size_t nonce;
    while (!flag) {
        if (flag) { break; }
        for (auto& iter : clients) {
            nonce = iter.first->generate_nonce();
            if (crypto::sha256(mempool + std::to_string(nonce)).substr(0, 10).find("000") != std::string::npos) {
                iter.second += 6.25;
                for (auto& trx : pending_trxs) {
                    std::string sender, receiver;
                    double value;
                    if (!parse_trx(trx, sender, receiver, value)) {
                        continue;
                    }
                    clients[get_client(sender)] -=value;
                    clients[get_client(receiver)] +=value;
                }
                std::cout << iter.first->get_id() << std::endl;
                flag = true;
                break;
            }
        }
    }
    return nonce;
}

using MPD = std::map<std::shared_ptr<Client>, double>;
void show_wallets(const Server& server) {
    std::cout << std::string(20, '*') << std::endl;
    for (const auto &client: *((MPD*)&server)) {
        std::cout << client.first->get_id() << " : " << client.second << std::endl;
    }
    std::cout << std::string(20, '*') << std::endl;
}