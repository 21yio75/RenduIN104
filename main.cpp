#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "checkpoint.h"
#include "game.h"
#include <vector>
#include <string>


int main()
{
    sf::ContextSettings settings;
    
    settings.antialiasingLevel = 32;
    
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!", sf::Style::Default, settings);
    window.setView(sf::View(sf::Rect(0.f,0.f,16000.f,9000.f)));
    
    //frame per second
    float fps = 60;
    
    //temps minimal entre deux frame
    sf::Time refreshTime = sf::microseconds(1e6/fps);

    //horloge depuis le début du jeu
    sf::Clock globalClock;
    //horloge réinitialisée à chaque frame
    sf::Clock refreshClock;

    //temps de la physique du jeu
    sf::Time physicsTime = sf::Time::Zero;

    //Vous pouvez aussi initialiser myGame avec une liste de checkpoints prédéfinie
    Game myGame = Game({sf::Vector2f(3000,2000),sf::Vector2f(8000,1000),sf::Vector2f(14000,4000),sf::Vector2f(8000,6000)});
    myGame.addPod();
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        //si on a dépassé le refreshTime depuis la dernière frame
        if (refreshClock.getElapsedTime() >= refreshTime)
        {
            //réinitialise l'horloge qui mesure le temps entre les frames
            refreshClock.restart();

            //récupère le temps écoulé depuis le début du jeu
            sf::Time frameTime = globalClock.getElapsedTime();
            
            //si on a dépassé le temps de la physique
            if (frameTime > physicsTime)
            {
                //met à jour les sprite au temps de la physique
                myGame.updateGraphics(physicsTime);
                
                //fait avancer la physique d'un pas de temps
                myGame.updatePhysics();
                
                physicsTime += PHYSICS_TIME_STEP;

                //reprend le temps écoulé depuis le début pour rester précis
                frameTime = globalClock.getElapsedTime();
            }
            
            //met à jour les sprites au temps actuel
            myGame.updateGraphics(frameTime);
            window.draw(myGame);
            
            window.display();
        }
    }

    return 0;
}
