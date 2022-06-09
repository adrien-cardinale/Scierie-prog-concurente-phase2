#pragma once
#include "benne.hpp"
#include <thread>
#include <deque>
#include <memory>

class Usine{
protected:
    int boisAScier;
    int plancheAStocker;
    int stockPlanche;
    std::deque<std::unique_ptr<Benne>> parkingExtractionBenne;
    std::deque<std::unique_ptr<Benne>> parkingTransportBenne;
public:
    Usine();
    friend class Simulation;
    friend class Transporteur;
    friend class Ouvrier;
};