#include "superAffichage.hpp"
#define NBR_MAX_BENNE 3

SuperAffichage::SuperAffichage(){
    font.loadFromFile("front/OpenSans-Light.ttf");
    textTimer.setFont(font);
    textTimer.setPosition(500.f, 0.f);
    //foret
    foret.setSize(sf::Vector2f(300.f, 600.f));
    foret.setPosition(0.f, 100.f);
    foret.setFillColor(sf::Color::Green);
    //Usine
    usine.setSize(sf::Vector2f(300.f, 600.f));
    usine.setPosition(900.f, 100.f);
    usine.setFillColor(sf::Color(193, 193, 193));
    //Carrefour
    ligne1Carrefour.setSize(sf::Vector2f(250.f, 10.f));
    ligne1Carrefour.setPosition(300.f, 350.f);
    ligne2Carrefour.setSize(sf::Vector2f(250.f, 10.f));
    ligne2Carrefour.setPosition(300.f, 450.f);
    ligne3Carrefour.setSize(sf::Vector2f(250.f, 10.f));
    ligne3Carrefour.setPosition(650.f, 350.f);
    ligne4Carrefour.setSize(sf::Vector2f(250.f, 10.f));
    ligne4Carrefour.setPosition(650.f, 450.f);
    ligne5Carrefour.setSize(sf::Vector2f(10.f, 250.f));
    ligne5Carrefour.setPosition(540.f, 100.f);
    ligne6Carrefour.setSize(sf::Vector2f(10.f, 250.f));
    ligne6Carrefour.setPosition(650.f, 100.f);
    ligne7Carrefour.setSize(sf::Vector2f(10.f, 250.f));
    ligne7Carrefour.setPosition(540.f, 450.f);
    ligne8Carrefour.setSize(sf::Vector2f(10.f, 250.f));
    ligne8Carrefour.setPosition(650.f, 450.f);        
    //Bucheron
    bucheron.setRadius(40.f);
    bucheron.setPosition(100.f, 150.f);
    bucheron.setFillColor(sf::Color(153,76,0));
    textBucheron.setPosition(75.f, 120.f);
    textBucheron.setFont(font);
    textBucheron.setFillColor(sf::Color::Black);
    //ouvrier
    ouvrier.setRadius(40.f);
    ouvrier.setPosition(1000.f, 150.f);
    ouvrier.setFillColor(sf::Color::Blue);
    textOuvrier.setPosition(975.f, 120.f);
    textOuvrier.setFont(font);
    textOuvrier.setFillColor(sf::Color::Black);
    //Benne foret
    for(int i = 0; i < NBR_MAX_BENNE; i++){
        benneRemplissageForet.push_back(sf::RectangleShape());
        benneRemplissageForet[i].setSize(sf::Vector2f(100.f, 50.f));
        benneRemplissageForet[i].setPosition(150.f, 300.f + i*60.f);
        benneRemplissageForet[i].setFillColor(sf::Color::Yellow);
        textBenneRemplissageForet.push_back(sf::Text());
        textBenneRemplissageForet[i].setFont(font);
        textBenneRemplissageForet[i].setPosition(benneRemplissageForet[i].getPosition().x + 50.f, benneRemplissageForet[i].getPosition().y + 25.f);
        textBenneRemplissageForet[i].setFillColor(sf::Color::Black);
        textBenneRemplissageForet[i].setCharacterSize(20);
        textBenneRemplissageForet[i].setString("0");
        benneTransportForet.push_back(sf::RectangleShape());
        benneTransportForet[i].setSize(sf::Vector2f(100.f, 50.f));
        benneTransportForet[i].setPosition(150.f, 500.f + i*60.f);
        benneTransportForet[i].setFillColor(sf::Color::Yellow);
        textBenneTransportForet.push_back(sf::Text());
        textBenneTransportForet[i].setFont(font);
        textBenneTransportForet[i].setPosition(benneTransportForet[i].getPosition().x + 50.f, benneTransportForet[i].getPosition().y + 25.f);
        textBenneTransportForet[i].setFillColor(sf::Color::Black);
        textBenneTransportForet[i].setCharacterSize(20);
        textBenneTransportForet[i].setString("0");
    }
    //Benne usine
    for(int i = 0; i < NBR_MAX_BENNE; i++){
        benneExtractionUsine.push_back(sf::RectangleShape());
        benneExtractionUsine[i].setSize(sf::Vector2f(100.f, 50.f));
        benneExtractionUsine[i].setPosition(910.f, 300.f + i*60.f);
        benneExtractionUsine[i].setFillColor(sf::Color::Yellow);
        textBenneExtractionUsine.push_back(sf::Text());
        textBenneExtractionUsine[i].setFont(font);
        textBenneExtractionUsine[i].setPosition(benneExtractionUsine[i].getPosition().x + 50.f, benneExtractionUsine[i].getPosition().y + 25.f);
        textBenneExtractionUsine[i].setFillColor(sf::Color::Black);
        textBenneExtractionUsine[i].setCharacterSize(20);
        textBenneExtractionUsine[i].setString("0");
        benneTransportUsine.push_back(sf::RectangleShape());
        benneTransportUsine[i].setSize(sf::Vector2f(100.f, 50.f));
        benneTransportUsine[i].setPosition(910.f, 500.f + i*60.f);
        benneTransportUsine[i].setFillColor(sf::Color::Yellow);
        textBenneTransportUsine.push_back(sf::Text());
        textBenneTransportUsine[i].setFont(font);
        textBenneTransportUsine[i].setPosition(benneTransportUsine[i].getPosition().x + 50.f, benneTransportUsine[i].getPosition().y + 25.f);
        textBenneTransportUsine[i].setFillColor(sf::Color::Black);
        textBenneTransportUsine[i].setCharacterSize(20);
        textBenneTransportUsine[i].setString("0");
    }
    //affichage usine
    textBoisAScier.setFont(font);
    textBoisAScier.setPosition(1020.f, 400.f);
    textBoisAScier.setFillColor(sf::Color::Black);
    textBoisAScier.setCharacterSize(15);
    textBoisAScier.setString("Bois a scier : 0");
    textPlanchAStocker.setFont(font);
    textPlanchAStocker.setPosition(1020.f, 450.f);
    textPlanchAStocker.setFillColor(sf::Color::Black);
    textPlanchAStocker.setCharacterSize(15);
    textPlanchAStocker.setString("Planches a stocker : 0");
    textStockPlanche.setFont(font);
    textStockPlanche.setPosition(1020.f, 500.f);
    textStockPlanche.setFillColor(sf::Color::Black);
    textStockPlanche.setCharacterSize(15);
    textStockPlanche.setString("Stock de planches : 0");
    //transporteur
    transporteur.setSize(sf::Vector2f(40.f, 40.f));
    transporteur.setPosition(780.f, 360.f);
    transporteur.setFillColor(sf::Color::Red);
    benneTransporteur.setSize(sf::Vector2f(80.f, 40.f));
    benneTransporteur.setPosition(820.f, 360.f);
    benneTransporteur.setFillColor(sf::Color::Yellow);
}

void SuperAffichage::affichage(){
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Projet Programation concurente");
    
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(textTimer);
        window.draw(foret);
        window.draw(ligne1Carrefour);
        window.draw(ligne2Carrefour);
        window.draw(ligne3Carrefour);
        window.draw(ligne4Carrefour);
        window.draw(ligne5Carrefour);
        window.draw(ligne6Carrefour);
        window.draw(ligne7Carrefour);
        window.draw(ligne8Carrefour);
        window.draw(usine);
        window.draw(bucheron);
        window.draw(textBucheron);
        window.draw(ouvrier);
        window.draw(textOuvrier);
        
        for(int i = 0; i < nbrBenneRemplissageForet; i++){
            window.draw(benneRemplissageForet[i]);
            window.draw(textBenneRemplissageForet[i]);
        }
        for(int i = 0; i < nbrBenneTransportForet; i++){
            window.draw(benneTransportForet[i]);
            window.draw(textBenneTransportForet[i]);
        }
        for(int i = 0; i < nbrBenneExtractionUsine; i++){
            window.draw(benneExtractionUsine[i]);
            window.draw(textBenneExtractionUsine[i]);
        }
        for(int i = 0; i < nbrBenneTransportUsine; i++){
            window.draw(benneTransportUsine[i]);
            window.draw(textBenneTransportUsine[i]);
        }
        window.draw(textBoisAScier);
        window.draw(textPlanchAStocker);
        window.draw(textStockPlanche);
        window.draw(transporteur);
        if(transporteurMove){
            window.draw(benneTransporteur);
        }

        window.display();
    }
}

void SuperAffichage::updateTimer(int jours, int heures, int minutes){
    textTimer.setString("jour : " + std::to_string(jours) + "   " + std::to_string(heures) + " : " + std::to_string(minutes));
    textTimer.setCharacterSize(30);
    textTimer.setFillColor(sf::Color::White);
}

void SuperAffichage::updateBucheron(int etat){
    switch (etat)
    {
        case 0:{
            textBucheron.setString("");
            break;
        }
        case 1:{
            textBucheron.setString("Retourne en foret");
            break;
        }
        case 2:{
            textBucheron.setString("Coupe du bois");
            break;
        }
        case 3:{
            textBucheron.setString("Rammene le bois a la benne"); 
            break;
        }
        case 4:{
            textBucheron.setString("Controlle si il y a une benne");
            break;
        }case 5:{
            textBucheron.setString("Controlle si la benne est pleine");
            break;
        }case 6:{
            textBucheron.setString("Deplace la benne dans le parking transport");
            break;
        }
        case 7:{
            textBucheron.setString("Rempli la benne");
            break;
        }
    }
    textBucheron.setCharacterSize(10);
}

void SuperAffichage::updateOuvrier(int etat){
    switch (etat)
    {
        case 0:{
            textOuvrier.setString("Va a la benne");
            break;
        }
        case 1:{
            textOuvrier.setString("Controle si la benne est pleine");
            break;
        }
        case 2:{
            textOuvrier.setString("Deplace la benne dans le parking transport");
            break;
        }
        case 3:{
            textOuvrier.setString("vide un bois de la benne"); 
            break;
        }case 4:{
            textOuvrier.setString("Emmene un bois à l'usine");
            break;
        }case 5:{
            textOuvrier.setString("Prend un bois");
            break;
        }case 6:{
            textOuvrier.setString("Scie un bois");
            break;
        }case 7:{
            textOuvrier.setString("Prend une planche");
            break;
        }case 8:{
            textOuvrier.setString("Emmene une planche au stock");
            break;
        }case 9:{
            textOuvrier.setString("Retourne a l'usine");
            break;
        }case 11:{
            textOuvrier.setString("");
            break;
        }
    }
    textOuvrier.setCharacterSize(10);
}

void SuperAffichage::updateBenneForet(std::deque<std::unique_ptr<Benne>> &parkingRemplissageBenne, std::deque<std::unique_ptr<Benne>> &parkingTransportBenne){
    nbrBenneRemplissageForet = parkingRemplissageBenne.size();
    nbrBenneTransportForet = parkingTransportBenne.size();
    for(int i = 0; i < nbrBenneRemplissageForet; i++){
        textBenneRemplissageForet[i].setString(std::to_string(parkingRemplissageBenne.at(i)->getEtat()));
    }
    for(int i = 0; i < nbrBenneTransportForet; i++){
        textBenneTransportForet[i].setString(std::to_string(parkingTransportBenne.at(i)->getEtat()));
    }
}

void SuperAffichage::updateBenneUsine(std::deque<std::unique_ptr<Benne>> &parkingExtractionBenne, std::deque<std::unique_ptr<Benne>> &parkingTransportBenne){
    nbrBenneExtractionUsine = parkingExtractionBenne.size();
    nbrBenneTransportUsine = parkingTransportBenne.size();
    for(int i = 0; i < nbrBenneExtractionUsine; i++){
        textBenneExtractionUsine[i].setString(std::to_string(parkingExtractionBenne.at(i)->getEtat()));
    }
    for(int i = 0; i < nbrBenneTransportUsine; i++){
        textBenneTransportUsine[i].setString(std::to_string(parkingTransportBenne.at(i)->getEtat()));
    }
}

void SuperAffichage::updateUsine(int &boisAScier,int &planchAStocker,int &stockPlanche){
    textBoisAScier.setString("Bois a scier : " + std::to_string(boisAScier));
    textPlanchAStocker.setString("Planches a stocker : " + std::to_string(planchAStocker));
    textStockPlanche.setString("Stock de planches : " + std::to_string(stockPlanche));
}

void SuperAffichage::moveTransporteurForet(){
    transporteurMove = true;
    transporteur.setPosition(transporteur.getPosition().x - 1, 360);
    benneTransporteur.setPosition(benneTransporteur.getPosition().x - 1, 360);   
}

void SuperAffichage::switchBenneTransporteurForet(){
    transporteurMove = false;
    transporteur.setPosition(transporteur.getPosition().x + 80, 410);
    benneTransporteur.setPosition(benneTransporteur.getPosition().x - 40, 410);
}

void SuperAffichage::moveTransporteurUsine(){
    transporteurMove = true;
    transporteur.setPosition(transporteur.getPosition().x + 1, 410);
    benneTransporteur.setPosition(benneTransporteur.getPosition().x + 1, 410);
}

void SuperAffichage::switchBenneTransporteurUsine(){
    transporteurMove = false;
    transporteur.setPosition(transporteur.getPosition().x - 80, 360);
    benneTransporteur.setPosition(benneTransporteur.getPosition().x + 40, 360);
}

SuperAffichage* SuperAffichage::instance = nullptr;
SuperAffichage *SuperAffichage::GetInstance(){
    if(instance == nullptr){
        instance = new SuperAffichage();
    }
    return instance;
}