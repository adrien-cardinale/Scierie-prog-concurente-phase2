#pragma once
#include "foret.hpp"
#include "usine.hpp"
#include "transporteur.hpp"
#include "bucheron.hpp"
#include "ouvrier.hpp"
#include "benne.hpp"
#include <thread>

class Simulation{
    Foret foret;
    Usine usine;
    Transporteur transporteur;
    Bucheron bucheron;
    Ouvrier ouvrier;
    std::thread threadTransporteur;
    std::thread threadBucheron;
    std::thread threadOuvrier;
public:
    Simulation();
    void start();
    void stop();
};