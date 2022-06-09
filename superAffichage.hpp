#pragma once
#include "benne.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include <iterator>
#include <algorithm>


class SuperAffichage{
    sf::Text textTimer;
    sf::Text textBucheron;
    sf::Text textOuvrier;
    sf::Font font;
    sf::RectangleShape foret;
    sf::RectangleShape usine;
    sf::CircleShape bucheron;
    sf::CircleShape ouvrier;
    sf::RectangleShape ligne1Carrefour;
    sf::RectangleShape ligne2Carrefour;
    sf::RectangleShape ligne3Carrefour;
    sf::RectangleShape ligne4Carrefour;
    sf::RectangleShape ligne5Carrefour;
    sf::RectangleShape ligne6Carrefour;
    sf::RectangleShape ligne7Carrefour;
    sf::RectangleShape ligne8Carrefour;
    std::vector<sf::RectangleShape> benneRemplissageForet;
    std::vector<sf::RectangleShape> benneTransportForet;
    std::vector<sf::Text> textBenneRemplissageForet;
    std::vector<sf::Text> textBenneTransportForet;
    std::vector<sf::RectangleShape> benneExtractionUsine;
    std::vector<sf::RectangleShape> benneTransportUsine;
    std::vector<sf::Text> textBenneExtractionUsine;
    std::vector<sf::Text> textBenneTransportUsine;
    sf::Text textBoisAScier;
    sf::Text textPlanchAStocker;
    sf::Text textStockPlanche;
    sf::RectangleShape transporteur;
    sf::RectangleShape benneTransporteur;

    int nbrBenneRemplissageForet;
    int nbrBenneTransportForet;
    int nbrBenneExtractionUsine;
    int nbrBenneTransportUsine;
    bool transporteurMove;

protected:
    SuperAffichage();
    static SuperAffichage* instance;
public:
    SuperAffichage(SuperAffichage &other) = delete;
    void operator=(const SuperAffichage &) = delete;
    static SuperAffichage *GetInstance();
    void affichage();
    void updateTimer(int jours, int heures, int minutes);
    void updateBucheron(int etat);
    void updateOuvrier(int etat);
    void updateBenneForet(std::deque<std::unique_ptr<Benne>> &parkingBenneVide, std::deque<std::unique_ptr<Benne>> &parkingBennePleine);
    void updateBenneUsine(std::deque<std::unique_ptr<Benne>> &parkingBenneVide, std::deque<std::unique_ptr<Benne>> &parkingBennePleine);
    void updateUsine(int &boisAScier, int &planchAStocker, int &stockPlanche);
    void moveTransporteurForet();
    void moveTransporteurUsine();
    void switchBenneTransporteurForet();
    void switchBenneTransporteurUsine();
};
