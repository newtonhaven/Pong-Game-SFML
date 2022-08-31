#include <SFML/Graphics.hpp>
using namespace sf;



int main(){

    //creation
    RenderWindow window(VideoMode(800,600), "SFML-Game");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    bool game = true;
    
    Event event;
    //variables
    int mouseX = 0,mouseY = 0;
    //gameloop
    while (game == true)
    {
        //events
        while (window.pollEvent(event))
        {
            //checking event type. if key event
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::A)
            {
                
            }

            if (event.type == Event::KeyReleased)
            {
                /* code */
            }
            if (event.type == Event::MouseMoved)
            {
                mouseX = event.mouseMove.x; //x position
                mouseY = event.mouseMove.y; // y position
            }
            
            if (event.type == Event::Closed)
            {
                game = false;
            }
            
        }
        
        //logic
        

        // rendering
        window.clear();

        window.display();
    }
    
    //clean up
    window.close();

    return 0;
}