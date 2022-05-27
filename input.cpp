#include "input.h"

Input::Input()
{
    button.up=button.down=false;
}

Input::Button Input::GetButton(void) const{
return button;
}

void InputHandler(Event event,RenderWindow& window){

    if (event.type == Event::Closed){
        window.close();
    }

    if (event.type == Event::KeyPressed){
        switch (event.key.code){
            case keyboard::up:
                button.up=true;
                break;

            case keyboard::down:
                button.down=true;
                break;
            default:
                break;
        }

    }
    if (event.type == Event::KeyReleased){
        switch(event.key.code){
            case keyboard::up:
                button.up=false;
                break;

            case keyboard::down:
                button.down=false;
                break;
            default:
                break;
        }
        
    }

}