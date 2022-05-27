#include "utils.h"
#include <cmath>

void setOriginToCenter(sf::Sprite &object)
{
    auto rect = object.getGlobalBounds();
    object.setOrigin(rect.width/2., rect.height/2.);
}

void setOriginToCenter(sf::Shape &object)
{
    auto rect = object.getGlobalBounds();
    object.setOrigin(rect.width/2., rect.height/2.);
}

void scaleToMinSize(sf::Sprite &sp, double size_x, double size_y)
{
    double scalingFactor = std::max(size_x/sp.getTextureRect().width, size_y/sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void scaleToMaxSize(sf::Sprite &sp, double size_x, double size_y)
{
    double scalingFactor = std::min(size_x/sp.getTextureRect().width, size_y/sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void scaleByRadius(sf::Sprite &sp, int radius)
{
    double scalingFactor = 2*radius/std::sqrt(sp.getTextureRect().width*sp.getTextureRect().width + sp.getTextureRect().height*sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void setTextCenterPosition(sf::Text &txt, sf::Vector2f center)
{
    sf::Vector2f offset;
    offset.x = txt.getPosition().x - txt.getGlobalBounds().left - txt.getGlobalBounds().width/2.;
    offset.y = txt.getPosition().y - txt.getGlobalBounds().top - txt.getGlobalBounds().height/2.;

    txt.setPosition(center + offset);
}
//on définit deux fonctions mathématiques qui nous permettent de renouveler 
//la physique du jeu en fonction des mouvements du pod


float norm(sf::Vector2f u){
    float v;
    v=sqrt(pow(u.x,2)+pow(u.y,2));
    if (v==0){                    //cas norme=0 car on va diviser par la norme
        v=1;                      // dans la fonction update physics
    }
    return v;
}

float arg(sf::Vector2f u){
    float tetha;
    if (u.x==0){                //cas argument égal à 0: on fixe l'angle à pi/2
                                //car s'il n'avance plus en x alors il tourne perpendiculairement à sa trajectoire
        tetha=M_PI/2;
    }
    if (u.x>0){                 //disjonction de cas suivant le signe de x
        tetha=atan(u.y/u.x);    //analogie avec l'argument d'un nombre dans un plan complexe
    }
    else{
        tetha=atan(u.y/u.x) + M_PI;
    }
    return tetha;
}