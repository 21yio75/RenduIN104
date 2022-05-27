#include <SFML/Graphics/Font.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "checkpoint.h"
#include "game.h"


// on écrit tout d'abord la fonction qui crée les checkpoints intermédiares

CheckPoint::CheckPoint(sf::Vector2f center, unsigned int id) : circle_(600,100),fillingText_()
{
    
    setOriginToCenter(circle_);
    circle_.setPosition(center);
    circle_.setFillColor(sf::Color(255,255,255,63));
    circle_.setOutlineColor(sf::Color(0,0,0));
    circle_.setOutlineThickness(-50);

   
    std::string text_printed = std::to_string(id);
    font_.loadFromFile("../repository/Fredoka-Bold.ttf");
    fillingText_.setFont(font_);
    fillingText_.setString(text_printed);
    fillingText_.setCharacterSize(600);
    fillingText_.setFillColor(sf::Color::Black);
    setTextCenterPosition(fillingText_,center);


};

void CheckPoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(circle_, states);
    target.draw(fillingText_);
};

sf::Vector2f CheckPoint::getPosition()
{
    return circle_.getPosition();
}
//cette fonction construit le checkpoint final
FinalCheckPoint::FinalCheckPoint(sf::Vector2f center) : circle_(600,100), fillingTexture_()
{
    setOriginToCenter(circle_);
    circle_.setPosition(center);
    circle_.setFillColor(sf::Color(255,255,255,63));
    circle_.setOutlineColor(sf::Color(0,0,0));
    circle_.setOutlineThickness(-50);
//on récupère l'image du drapeau
    fillingTexture_.loadFromFile("../repository/Images/checkeredFlag.png");
    fillingSprite_ = sf::Sprite(fillingTexture_);
    setOriginToCenter(fillingSprite_);
    fillingSprite_.setPosition(center);
    scaleByRadius(fillingSprite_,550);

};

void FinalCheckPoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(circle_, states);
    target.draw(fillingSprite_, states);
};

sf::Vector2f FinalCheckPoint::getPosition()
{
    return circle_.getPosition();
}
