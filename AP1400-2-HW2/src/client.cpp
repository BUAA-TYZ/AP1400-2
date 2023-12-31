#include "client.h"

Client::Client(std::string id, const Server& server)
: id(id), server(&server){
    crypto::generate_key(public_key, private_key);
}

double Client::get_wallet() const {
    return server->get_wallet(id);
}

bool Client::transfer_money(std::string receiver, double value) const {
    std::string trx = id + '-' + receiver + '-' + std::to_string(value);
    return server->add_pending_trx(trx, sign(trx));
}

size_t Client::generate_nonce() {
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution u(0, INT_MAX);
    return u(e);
}
