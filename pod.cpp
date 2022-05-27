#include "pod.h"
#include "game.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <math.h>
#include "utils.h"
//cette fonction permet de stocker les coordonnées de la target (le prochain checkpoint par exemple) et la puissance pour y arriver, 
//qui sert notamment  dans la formule de récurrence pour calculer la nouvelle vitesse du pod
Decision::Decision(sf::Vector2f target, float power) 
{
    target_=target;
    power_=power;
};
//cette fonction permet de connaître les coordonnées, l'angle d'inclinaison et la vitesse du pod à un instant t
//utile notamment dans les fonctions updateGraphics et updatePhysics

Pod::Pod(sf::Vector2f pos, float angle, sf::Vector2f vel) 
{
    pos_=pos;
    angle_=angle;
    vel_=vel;
    
};
//Cette fonction permet de définir la target du pod pour le prochain instant dans l'optique d'arriver à terme au prochain checkpoint

Decision Pod::getDecision(GameInfos gameInfos) const
{
    int nextCP = nextCP_;    //indice du prochain checkpoint
    sf::Vector2f target = gameInfos.cpPositions[nextCP];    // coordonnées du prochain checkpoint
    Pod pod = gameInfos.pods[0];
    sf::Vector2f u = pod.vel_;
    sf::Vector2f u2 = target-pod.pos_;
    float angle = acos((u.x*u2.x+u.y*u2.y)/norm(u)*norm(u2)); //on calcule l'angle entre la direction du pod et le prochain checkpoint en utilisant une formule du produit scalaire

    
 
    //on va traîter le cas angle>pi/10 pour que le pod ne tourne pas de manière trop abrupte 
    //et pour rendre l'affichage cohérent avec la physique du jeu 
    //on prend dans ce cas l'angle différence entre l'angle calculé au dessus et pi/10
    //cela nous donne une direction intermédiare
    if (angle <- M_PI/10 ){
        target.x= pod.pos_.x + u2.x*cos(angle-M_PI/10) + u2.y* sin(angle-M_PI/10); //u.x*cos(M_PI/10) + u.y*sin(M_PI/10);
        target.y= pod.pos_.y - u2.x*sin(angle-M_PI/10) + u2.y* cos(angle-M_PI/10); //+ u.y*cos(M_PI/10) - u.x*sin(M_PI/10);
    }
    printf("x = %f, y = %f\n", target.x, target.y);
    printf("tetha = %f\n", pod.angle_);
    
    return Decision(target, 100);
};

