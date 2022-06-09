#include "superAffichage.hpp"
#include "superTimer.hpp"
#include "benne.hpp"
#include "bucheron.hpp"
#include "foret.hpp"
#include "ouvrier.hpp"
#include "usine.hpp"
#include "transporteur.hpp"
#include "simulation.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <mutex>
#include <set>
#include <condition_variable>
#include <vector>
#include <memory>

using namespace std;
using namespace std::chrono;




int main(){
    SuperTimer* superTimer = SuperTimer::GetInstance();
    SuperAffichage* superAffichage = SuperAffichage::GetInstance();
    thread threadTimer(&SuperTimer::count, superTimer);
    thread threadAffichage(&SuperAffichage::affichage, superAffichage);

    Simulation simulation;
    simulation.start();
    
   

    threadAffichage.join();
    threadTimer.detach();
    return 0;
}