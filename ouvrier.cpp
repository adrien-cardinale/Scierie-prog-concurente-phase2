#include "ouvrier.hpp"

Ouvrier::Ouvrier():etat(11){}

void Ouvrier::gestion(Usine &usine){
    int etat = 0;
    SuperAffichage::GetInstance()->updateBenneUsine(std::ref(usine.parkingExtractionBenne), std::ref(usine.parkingTransportBenne));
    while(true){
        switch(etat){
            case 0:{
                if(SuperTimer::GetInstance()->getHeures() >= 8 && SuperTimer::GetInstance()->getHeures() <= 17){
                    etat = 1;
                }
                break;
            }case 1:{
                if(!usine.parkingExtractionBenne.empty()){ 
                    etat = 2;
                }else{
                    etat = 3;
                }
                break;
            }case 2:{
                std::thread threadViderBenne(&Ouvrier::viderBenne, this, std::ref(usine.parkingExtractionBenne),std::ref(usine.parkingTransportBenne), std::ref(usine.boisAScier));
                threadViderBenne.join();
                etat = 0;
                break;
            }case 3:{
                if(usine.boisAScier <= 0){
                    etat = 5;
                }else{
                    etat = 4;
                }
                break;
            }case 4:{
                std::thread threadScier(&Ouvrier::scier, this, std::ref(usine.boisAScier), std::ref(usine.plancheAStocker));
                threadScier.join();
                etat = 0;
                break;
            }case 5:{
                if(usine.plancheAStocker <= 0){
                    etat = 0;
                }else{
                    etat = 6;
                }
                break;
            }case 6:{
                std::thread threadStocker(&Ouvrier::stocker, this, std::ref(usine.plancheAStocker), std::ref(usine.stockPlanche));
                threadStocker.join();
                etat = 0;
                break;
            }
        }
         SuperAffichage::GetInstance()->updateUsine(std::ref(usine.boisAScier), std::ref(usine.plancheAStocker), std::ref(usine.stockPlanche));
    }
}

void Ouvrier::viderBenne(std::deque<std::unique_ptr<Benne>> &parkingExtractionBenne,std::deque<std::unique_ptr<Benne>> &parkingTransportBenne, int &boisAScier){
    etat = 0;
    while(etat != 11){
        switch(etat){
            case 0:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                etat = 1;
                break;
            }case 1:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if(parkingExtractionBenne.front()->getEtat() > 0){
                    etat = 3;
                }else{
                    etat = 2;
                }
                break;
            }case 2:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                parkingTransportBenne.push_back(std::move(parkingExtractionBenne.front()));
                parkingExtractionBenne.pop_front();
                benneDisponibleTransporteurUsine.notify_one();
                etat = 11;
                break;
            }case 3:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                parkingExtractionBenne.front()->viderBenne();
                boisAScier++;
                etat = 4;
                break;
            }case 4:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                etat = 11;
                break;
            }
        }
        SuperAffichage::GetInstance()->updateOuvrier(etat);
        SuperAffichage::GetInstance()->updateBenneUsine(std::ref(parkingExtractionBenne), std::ref(parkingTransportBenne)); 
    }
}

void Ouvrier::scier(int &boisAScier, int &plancheAStocker){
    etat = 5;
    while(etat != 11){
        switch(etat){
            case 5:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                boisAScier--;
                etat = 6;
                break;
            }case 6:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                plancheAStocker++;
                etat = 11;
                break;
            }
        }
        SuperAffichage::GetInstance()->updateOuvrier(etat);
    }
}

void Ouvrier::stocker(int &plancheAStocker,int &stockPlanche ){
    etat = 7;
    while(etat != 11){
        switch(etat){
            case 7:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                plancheAStocker--;
                etat = 8;
                break;
            }case 8:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                stockPlanche++;
                etat = 9;
                break;
            }case 9:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                etat = 11;
                break;
            }
        }
        SuperAffichage::GetInstance()->updateOuvrier(etat);
    }
}