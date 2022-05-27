#include "game.h"
#include "checkpoint.h"
#include "utils.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <cmath>



//cette fonction sert à afficher le checkpoint final, elle utilise les fonctions du programme checkpoint.cpp
Game::Game() : finalCP_({1000, 1000})
{
    if (!backgroundTexture_.loadFromFile(IMAGES_PATH + "/background.png"))
    {
        printf("Texture error\n"); // si jamais on ne récupère rien, on renvoie un message d'erreur
    }
    sf::Sprite sprite;
    backgroundSprite_.setTexture(backgroundTexture_);
    
    setOriginToCenter(backgroundSprite_);
    scaleToMinSize(backgroundSprite_,WIDTH_VIEW,HEIGHT_VIEW);
    backgroundSprite_.setPosition(WIDTH_VIEW/2,HEIGHT_VIEW/2);
 
    FinalCheckPoint Finalcp_({2000,1000});
    
}
//dans cette fonction, on définit le jeu avec les checkpoints en entrée,
//on affiche le jeu avec son background et on définit la liste des checkpoints
Game::Game(std::vector<sf::Vector2f> checkpointsPositions) : finalCP_(checkpointsPositions[0])
{
    if (!backgroundTexture_.loadFromFile(IMAGES_PATH + "/background.png"))
    {
        printf("Texture error\n"); //si jamais on ne récupère rien, on renvoie un message d'erreur
    }
    sf::Sprite sprite;
    backgroundSprite_.setTexture(backgroundTexture_);
    
    setOriginToCenter(backgroundSprite_);
    scaleToMinSize(backgroundSprite_,WIDTH_VIEW,HEIGHT_VIEW);
    backgroundSprite_.setPosition(WIDTH_VIEW/2,HEIGHT_VIEW/2);

    otherCPs_.reserve(checkpointsPositions.size()-1);
    for (unsigned int cpID = 1; cpID<checkpointsPositions.size(); cpID++)
    {
        otherCPs_.emplace_back(checkpointsPositions[cpID], cpID);
    }
    cpPositions_ = checkpointsPositions;

}
//cette fonction permet d'afficher un pod sur notre jeu, elle utilise les fonctions du programme pod.cpp
void Game::addPod()
{
    int nb_pods = 1;
    
    podsSprites_.reserve(nb_pods);
    pods_.reserve(nb_pods);
    podsTextures_.reserve(nb_pods);
    
 
    Pod pod1 = Pod({1000,7000}, 0.f);
    sf::Texture podTexture1;
    sf::Sprite podSprite1;
    

    if (!podTexture1.loadFromFile("/home/ensta/IN104/repository/Images/BSGCylon.png"))
    {
        printf("Texture error\n");
    }


    //on affiche l'image du pod sur notre jeu 
    podsTextures_.emplace_back(podTexture1);
    pods_.emplace_back(pod1);
    podsSprites_.emplace_back(podSprite1);


    podsSprites_[0].setPosition(2000,4000);
    

       
        
   //cette boucle donne la bonne forme aux pods  
    for (int i=0; i<nb_pods; i++){
        
         podsSprites_[i].setTexture(podsTextures_[i]);
         setOriginToCenter(podsSprites_[i]);
         scaleToMaxSize(podsSprites_[i], 800,800);

         pods_[i].nextCP_ = 1;
         pods_[i].lapCount_ = 1;
         
     }


}
// la fonction update physics actualise la nouvelle position du pod
void Game::updatePhysics()
{
    std::vector<Pod> PodsSnapshot = pods_;
   
    for (Pod &pod : pods_)
    {  
        Decision d = pod.getDecision({pods_,cpPositions_});
        float k = 0.85;  // on écrit la formule de récurrence qui permet de calculer la vitesse à l'instant suivant 
        
        pod.vel_ =  k * ( pod.vel_ + d.power_*(d.target_-pod.pos_)/norm(d.target_-pod.pos_));
        
        pod.pos_ = pod.pos_ + pod.vel_;   // on récupère les coordonnées de la nouvelle position du pod
        pod.angle_ = arg(pod.vel_);       // on récupère l'angle du pod à l'aide de sa nouvelle vitesse
        
//on met à présent à jour les données du jeu sur le nombre de tour ou les prochains checkpoints
        if (norm(pod.pos_ - d.target_)<600){ 
            
            if (pod.nextCP_ == 0 && pod.lapCount_< NUMBER_OF_LAPS){
                pod.nextCP_ = 1;
                pod.lapCount_ += 1;
            }
            else if (0 < pod.nextCP_ && pod.nextCP_ < otherCPs_.size()) pod.nextCP_ += 1;
            else pod.nextCP_ = 0; 
        }
    }

    physicsTime += PHYSICS_TIME_STEP; //on incrémente le temps de jeu
}
//la fonction updateGraphics permet d'aligner les graphiques sur l'évolution physique du jeu 

void Game::updateGraphics(sf::Time frameTime)
{
    
    float k = (physicsTime - frameTime)/(frameTime-lastFrameTime); // on définit une variable k qui va comparer temps graphique et temps physique
    
    

    int nb_pods = podsSprites_.size();     //on récupère le nombre de pods présents dans le jeu
    for (int i=0; i<nb_pods; ++i){         //pour tous les pods présentes dans le jeu
        sf::Vector2f pos_sprite = podsSprites_[i].getPosition(); //on récupère les informations de la prochaine direction du pod

        if (k>1)  podsSprites_[i].setPosition( pos_sprite + (pods_[i].pos_ - pos_sprite)/k );//si le temps physique est supérieur au temps graphique, 
        else podsSprites_[i].setPosition(pods_[i].pos_);                                    // on construit l'image suivante par interpolation linéaire
        
        podsSprites_[i].setRotation(pods_[i].angle_*180.f/M_PI); //on récupère l'angle du pod à cet instant qu'on converti en degrés
    }

    lastFrameTime = frameTime;
    
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backgroundSprite_, states);
    target.draw(finalCP_, states);

    for (const auto &cp : otherCPs_)
    {
        target.draw(cp, states);
    }

    for (const auto &podSprite : podsSprites_)
    {
        target.draw(podSprite, states);
    }
}

