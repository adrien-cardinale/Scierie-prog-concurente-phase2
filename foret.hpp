#pragma once
#include "benne.hpp"
#include <deque>
#include <memory>
#include <thread>

class Foret{
protected:
    std::deque<std::unique_ptr<Benne>> parkingRemplissageBenne;
    std::deque<std::unique_ptr<Benne>> parkingTransportBenne;
public:
    Foret();
    friend class Simulation;
    friend class Transporteur;
    friend class Bucheron;
};