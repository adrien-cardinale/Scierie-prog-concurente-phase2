#include "simulation.hpp"

Simulation::Simulation():foret(), usine(), transporteur(std::ref(usine), std::ref(foret)){
    foret.parkingRemplissageBenne.push_back(std::make_unique<Benne>(0));
    usine.parkingExtractionBenne.push_back(std::make_unique<Benne>(2));
    foret.parkingTransportBenne.push_back(std::make_unique<Benne>(2));
}

void Simulation::start(){
    threadTransporteur = std::thread(&Transporteur::transporter, &transporteur);
    threadBucheron = std::thread(&Bucheron::CouperDuBois, &bucheron, std::ref(foret));
    threadOuvrier = std::thread(&Ouvrier::gestion, &ouvrier, std::ref(usine));
}

void Simulation::stop(){
    threadTransporteur.join();
    threadBucheron.join();
    threadOuvrier.join();
}