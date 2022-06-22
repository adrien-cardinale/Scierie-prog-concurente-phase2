#include "ouvrier.hpp"

std::mutex m;
std::condition_variable ouvrierPeutServir;
std::condition_variable ouvrierPeutViderBenne;
std::condition_variable ouvrierPeutScier;
std::condition_variable ouvrierPeutStocker;

Ouvrier::Ouvrier():status(66){}

void Ouvrier::gestion(Usine &usine){
    std::thread threadServir(&Ouvrier::servirClient, this, std::ref(usine.clients), std::ref(usine.stockPlanche));
    std::thread threadViderBenne(&Ouvrier::viderBenne, this, std::ref(usine.parkingExtractionBenne),std::ref(usine.parkingTransportBenne), std::ref(usine.boisAScier));
    std::thread threadScier(&Ouvrier::scier, this, std::ref(usine.boisAScier), std::ref(usine.plancheAStocker));
    std::thread threadStocker(&Ouvrier::stocker, this, std::ref(usine.plancheAStocker), std::ref(usine.stockPlanche));
    int etat = 0;
    SuperAffichage::GetInstance()->updateBenneUsine(std::ref(usine.parkingExtractionBenne), std::ref(usine.parkingTransportBenne));
    while(true){
        if(etatViderBenne == EtatThread::RUNNING){
                std::cout << "Ouvrier vider benne running " << std::endl;
            }else{
                std::cout << "Ouvrier vider benne waiting " << std::endl;
            }
        switch(etat){
            case 0:{
                if(SuperTimer::GetInstance()->getHeures() >= 8 && SuperTimer::GetInstance()->getHeures() <= 17){
                    etat = 1;
                }
                break;
            case 1:{
                if(usine.clients.empty() || usine.stockPlanche <= 0){
                    etat = 3;
                }
                else{
                    etat = 2;
                }
                break;
            }
            case 2:{
                ouvrierPeutServir.notify_one();
                if(etatServirClient == EtatThread::WAITING){
                    etat = 0;
                }
            }
            }case 3:{
                if(!usine.parkingExtractionBenne.empty()){ 
                    etat = 4;
                }else{
                    etat = 5;
                }
                break;
            }case 4:{
                ouvrierPeutViderBenne.notify_one();
                if(etatViderBenne == EtatThread::WAITING){
                    etat = 0;
                }
                break;
            }case 5:{
                if(usine.boisAScier >= 0){
                    etat = 6;
                }else{
                    etat = 7;
                }
                break;
            }case 6:{
                ouvrierPeutScier.notify_one();
                if(etatScier == EtatThread::WAITING){
                    etat = 0;
                }
                break;
            }case 7:{
                if(usine.plancheAStocker >= 0){
                    etat = 8;
                }else{
                    etat = 0;
                }
                break;
            }case 8:{
                ouvrierPeutStocker.notify_one();
                if(etatStocker == EtatThread::WAITING){
                    etat = 0;
                }
                break;
            }
        }
         SuperAffichage::GetInstance()->updateUsine(std::ref(usine.boisAScier), std::ref(usine.plancheAStocker), std::ref(usine.stockPlanche));
    }
}

void Ouvrier::viderBenne(std::deque<std::unique_ptr<Benne>> &parkingExtractionBenne,std::deque<std::unique_ptr<Benne>> &parkingTransportBenne, int &boisAScier){
    std::unique_lock<std::mutex> lock(m);
    etatViderBenne = EtatThread::WAITING;
    ouvrierPeutViderBenne.wait(lock);
    etatViderBenne = EtatThread::RUNNING;
    int etat = 0;
    while(true){
        switch(etat){
            case 0:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                etat = 1;
                break;
            }case 1:{
                status = 1;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if(parkingExtractionBenne.front()->getEtat() > 0){
                    etat = 3;
                }else{
                    etat = 2;
                }
                break;
            }case 2:{
                status = 2;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                parkingTransportBenne.push_back(std::move(parkingExtractionBenne.front()));
                parkingExtractionBenne.pop_front();
                benneDisponibleTransporteurUsine.notify_one();

                std::unique_lock<std::mutex> lock(m);
                etatViderBenne = EtatThread::WAITING;
                ouvrierPeutViderBenne.wait(lock);
                etatViderBenne = EtatThread::RUNNING;

                etat = 0;
                break;
            }case 3:{
                status = 3;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                parkingExtractionBenne.front()->viderBenne();
                boisAScier++;
                etat = 4;
                break;
            }case 4:{
                status = 4;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                
                std::unique_lock<std::mutex> lock(m);
                etatViderBenne = EtatThread::WAITING;
                ouvrierPeutViderBenne.wait(lock);
                etatViderBenne = EtatThread::RUNNING;

                etat = 0;
                break;
            }
        }
        SuperAffichage::GetInstance()->updateOuvrier(status);
        SuperAffichage::GetInstance()->updateBenneUsine(std::ref(parkingExtractionBenne), std::ref(parkingTransportBenne)); 
    }
}

void Ouvrier::scier(int &boisAScier, int &plancheAStocker){
    std::unique_lock<std::mutex> lock(m);
    etatScier = EtatThread::WAITING;
    ouvrierPeutScier.wait(lock);
    etatScier = EtatThread::RUNNING;
        std::cout << "Ouvrier scie" << std::endl;

    int etat = 0;
    while(true){
        switch(etat){
            case 0:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                boisAScier--;
                status = 6;
                etat = 1;
                break;
            }case 1:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                plancheAStocker++;

                status = 6;

                std::unique_lock<std::mutex> lock(m);
                etatScier = EtatThread::WAITING;
                ouvrierPeutScier.wait(lock);
                etatScier = EtatThread::RUNNING;

                etat = 0;
                break;
            }
        }
        SuperAffichage::GetInstance()->updateOuvrier(status);
    }
}

void Ouvrier::stocker(int &plancheAStocker,int &stockPlanche ){
    std::unique_lock<std::mutex> lock(m);
    etatStocker = EtatThread::WAITING;
    ouvrierPeutStocker.wait(lock);
    etatStocker = EtatThread::RUNNING;

    int etat = 0;
    while(true){
        switch(etat){
            case 0:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                plancheAStocker--;
                status = 8;
                etat = 1;
                break;
            }case 1:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                stockPlanche++;
                status = 9;
                etat = 2;
                break;
            }case 2:{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                status = 9;

                std::unique_lock<std::mutex> lock(m);
                etatStocker = EtatThread::WAITING;
                ouvrierPeutStocker.wait(lock);
                etatStocker = EtatThread::RUNNING;

                etat = 0;
                break;
            }
        }
        SuperAffichage::GetInstance()->updateOuvrier(status);
    }
}

void Ouvrier::servirClient(std::deque<std::unique_ptr<Client>> &client, int &stockPlanche){
    std::unique_lock<std::mutex> lock(m);
    etatStocker = EtatThread::WAITING;
    ouvrierPeutStocker.wait(lock);
    etatStocker = EtatThread::RUNNING;

    int etat = 0;
    int nbrPlanche;
    while(true){
        switch(etat){
           case 0:{
               nbrPlanche = client.front()->plancheVoulue;
               etat = 1;
               status = 10;
               break;
           }case 1:{
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::unique_lock<std::mutex> lock(m);
                if(stockPlanche < nbrPlanche){
                    etatServirClient = EtatThread::WAITING;
                    ouvrierPeutServir.wait(lock);
                }
                etatServirClient = EtatThread::RUNNING;
                status = 11;
                etat = 2;
                break;
           }
           case 2:{
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                stockPlanche -= nbrPlanche;
                status = 12;

                std::unique_lock<std::mutex> lock(m);
                etatServirClient = EtatThread::WAITING;
                ouvrierPeutServir.wait(lock);
                etatServirClient = EtatThread::RUNNING;
                
                etat = 0;
                break;
           }
        }
    
    }
}