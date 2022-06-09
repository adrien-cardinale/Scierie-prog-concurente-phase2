#include "benne.hpp"

Benne::Benne():etat(0){}

Benne::Benne(int a):etat(a){}

void Benne::remplirBenne(){
    etat++;
}

void Benne::viderBenne(){
    etat--;
}

int Benne::getEtat(){
    return etat;
}
