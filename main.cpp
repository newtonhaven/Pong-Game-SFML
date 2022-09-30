#include <SFML/Graphics.hpp>
using namespace sf;



int main(){

    //creation
    RenderWindow window(VideoMode(800,600), "SFML-Game");
    //window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    bool game = true;
    
    Event event;

    //states
    bool up = false;
    bool down = false;
    //variables
    int yVelocityPad1 = 0;
    int xVelocityBall = -4;
    int yVelocityBall = -4;
    int yVelocityPad2 = 0;
    //resorces

    Font font;
    if (font.loadFromFile("res/arial.tff") == 0 )
        return 1;
    
    Text score;
    score.setFont(font);
    score.setCharacterSize(30);
    score.setColor(Color::Red);
    score.setPosition(250,10);
    score.setString("0 : 0");

    //images
    Texture textPlayer;
    if (!textPlayer.loadFromFile("res/pad.png"))
        return -1;    
    
    Texture textBall;
    if (!textBall.loadFromFile("res/ball.png"))
        return -1;    
    
    Texture textBacground;
    if (!textBacground.loadFromFile("res/background.png"))
        return -1;    
    
    //sound
    //SoundBuffer hit ;
    //Sound hit;
    hit.setBuffer(hit);
    //if (!hit.loadFromFile("res/hit.wav"))
    //    return -1;
        
    RectangleShape background;
    background.setSize(Vector2f(800,600));
    background.setPosition(0,0);
    background.setTexture(&textBacground);

    RectangleShape pad1;
    pad1.setSize(Vector2f(50,100));
    pad1.setPosition(700,200);
    pad1.setTexture(&textPlayer);

    RectangleShape pad2;
    pad2.setSize(Vector2f(50,100));
    pad2.setPosition(50,200);
    pad2.setTexture(&textPlayer);
    
    RectangleShape ball;
    ball.setSize(Vector2f(50,50));
    ball.setPosition(50,200);
    ball.setTexture(&textBall);


    //gameloop
    while (game == true)
    {
        //events
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                game = false;
            //press
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
            {
                up = true;
            }
            
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
            {
                down = true;
            }
            //relase
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Up)
            {
                up = false;
            }
            
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Down)
            {
                down = false;
            }
            

        }
        
        //logic
        if (up == true && down == false )
        {
            yVelocityPad1 = -5;
        }
        
        if (down == true && up == false)
        {
            yVelocityPad1 = 5;
        }

        if (down == false && up == false || up == true && down == true )
        {
            yVelocityPad1 = 0;
        }

        pad1.move(0,yVelocityPad1);
        //pad out of screen check
        if (pad1.getPosition().y < 0)
        {
            pad1.setPosition(50,0);
        }
        
        if (pad1.getPosition().y >500 )
        {
            pad1.setPosition(50,500);
        }
        //collision pad1
        if (ball.getGlobalBounds().intersects(pad1.getGlobalBounds())==true)
        {
            xVelocityBall = - yVelocityBall;
        }
        //collision pad2
        if (ball.getGlobalBounds().intersects(pad2.getGlobalBounds())==true)
        {
            xVelocityBall = - yVelocityBall;
        }

        //pad2
        if (ball.getPosition().y < pad2.getPosition.y)
        {
            yVelocityPad2 = -2;
        }
        
        if (ball.getPosition().y > pad2.getPosition.y)
        {
            yVelocityPad2 = 2;
        }

        pad2.move(0, yVelocityPad2);    

        //ball
        ball.move(xVelocityBall,yVelocityBall);
        if ( ball.getPosition().y < 0 || ball.getPosition().y >550 )
        {
            yVelocityBall = -yVelocityBall;
        }

        // rendering
        window.clear();

        window.draw(background);
        window.draw(pad1);
        window.draw(pad2);
        window.draw(ball);
        window.draw(score);

        window.display();
    }
    
    //clean up
    window.close();

    return 0;
}