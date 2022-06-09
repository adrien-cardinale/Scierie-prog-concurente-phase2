#pragma once
#include "superAffichage.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>

extern std::mutex m;
extern std::condition_variable benneDisponibleBucheron;
extern std::condition_variable benneDisponibleTransporteurForet;
extern std::condition_variable benneDisponibleTransporteurUsine;
extern std::condition_variable benneDisponibleExtraction;

class SuperTimer{
    int tempsEcoule;
    int heures;
    int minutes;
    int jours;
    int bufferHeures;
protected:
    SuperTimer();
    static SuperTimer* instance;
public:
    SuperTimer(SuperTimer &other) = delete;
    void operator=(const SuperTimer &) = delete;
    static SuperTimer *GetInstance();
    void count();
    int getJours();
    int getHeures();
    int getMinutes();
};
