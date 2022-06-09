#include "transporteur.hpp"
#include <iostream>

Transporteur::Transporteur(Usine &usine, Foret &foret): parkingExtractionUsine(usine.parkingExtractionBenne),
    parkingTransportUsine(usine.parkingTransportBenne), parkingRemplissageForet(foret.parkingRemplissageBenne), parkingTransportForet(foret.parkingTransportBenne){};

void Transporteur::transporter(){
    int etat = 0;
    while(true){
        switch(etat){
            case 0:{
                if(SuperTimer::GetInstance()->getHeures() >= 8 && SuperTimer::GetInstance()->getHeures() <= 17){
                    etat = 1;
                }
                break;
            }case 1:{
                std::unique_lock<std::mutex> lock(m);
                if(parkingTransportUsine.empty()){
                    benneDisponibleTransporteurUsine.wait(lock);
                }
                etat = 2;
                break;
            }case 2:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                benne = std::move(parkingTransportUsine.front());
                parkingTransportUsine.pop_front();
                etat = 3;
                break;
            }case 3:{
                for(int i = 0; i < 480; i++){
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    SuperAffichage::GetInstance()->moveTransporteurForet();
                }
                SuperAffichage::GetInstance()->switchBenneTransporteurForet();
                etat = 4;
                break;
            }case 4:{
                parkingRemplissageForet.push_back(std::move(benne));
                benneDisponibleBucheron.notify_one();
                
                etat = 5;
                break;
            }case 5:{
                
                std::unique_lock<std::mutex> lock(m);
                if(parkingTransportForet.empty()){
                    benneDisponibleTransporteurForet.wait(lock);
                }
                etat = 6;
                break;
            }case 6:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                benne = std::move(parkingTransportForet.front());
                parkingTransportForet.pop_front();
                etat = 7;
                break;
            }case 7:{
                for(int i = 0; i < 480; i++){
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    SuperAffichage::GetInstance()->moveTransporteurUsine();
                }
                SuperAffichage::GetInstance()->switchBenneTransporteurUsine();
                etat = 8;
                break;
            }case 8:{
                parkingExtractionUsine.push_back(std::move(benne));
                benneDisponibleExtraction.notify_one();
                etat = 0;
                break;
            }
        }
        SuperAffichage::GetInstance()->updateBenneForet(std::ref(parkingRemplissageForet), std::ref(parkingTransportForet));
        SuperAffichage::GetInstance()->updateBenneUsine(std::ref(parkingExtractionUsine), std::ref(parkingTransportUsine));
    }
}