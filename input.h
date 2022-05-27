#ifndef INPUT_H
#define INPUT_H
#include <SFML/Graphics.hpp>


class Input
{
    struct Button { bool up,down};

    public: 
    Input();

    ButtonGetButton(void) const;
    void InputHandler(Event event,RenderWindow& window);

    private:
    Button button;
}