#pragma once
#include "benne.hpp"
#include "superAffichage.hpp"
#include "superTimer.hpp"
#include "usine.hpp"
#include <memory>
#include <thread>
#include <deque>
#include <iostream>


class Ouvrier{
    int etat;
public:
    Ouvrier();
    void gestion(Usine &usine);
    void viderBenne(std::deque<std::unique_ptr<Benne>> &parkingBenne,std::deque<std::unique_ptr<Benne>> &parkingTransportBenne, int &boisAScier);
    void scier(int &boisAScier, int &plancheAStocker);
    void stocker(int &plancheAStocker,int &stockPlanche );
};