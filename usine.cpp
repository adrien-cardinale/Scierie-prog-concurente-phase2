#include "usine.hpp"

Usine::Usine():boisAScier(0), plancheAStocker(0), stockPlanche(0){
    clients.push_back(std::make_unique<Client>(2));
}