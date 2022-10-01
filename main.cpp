#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
//#include <SFML/Audio.hpp>
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
    int yVelocityPlayer1 = 0;
    int xVelocityBall = -4;
    int yVelocityBall = -4;
    int yVelocityPlayer2 = 0;
    int Player1Score = 0;
    int Player2Score = 0;

    // //resorces
    // Font font;
    // if (font.loadFromFile("res/arial.tff") == 0 )
    //     return 1;
    
    // Text score;
    // score.setFont(font);
    // score.setCharacterSize(30);
    // //score.setColor(Color::Red);
    // score.setPosition(250,10);
    // score.setString("0 : 0");

    //images
    Texture textPlayer;
    if (!textPlayer.loadFromFile("res/pad.png"))
    {
        return -1;   
    }
     
    Texture textBall;
    if (!textBall.loadFromFile("res/ball.png"))
    {
        return -1;   
    }    
    
    Texture textBacground;
    if (!textBacground.loadFromFile("res/background.png"))
    {
        return -1;   
    }    
    
    // //sound
    // SoundBuffer buffer;
    // if (!buffer.loadFromFile("res/hit.wav"))
    //     return -1;
    // Sound hit;
    // hit.setBuffer(buffer);

    RectangleShape background;
    background.setSize(Vector2f(800,600));
    background.setPosition(0,0);
    background.setTexture(&textBacground);

    RectangleShape Player1;
    Player1.setSize(Vector2f(50,100));
    Player1.setPosition(700,200);
    Player1.setTexture(&textPlayer);

    RectangleShape Player2;
    Player2.setSize(Vector2f(50,100));
    Player2.setPosition(700,200);
    Player2.setTexture(&textPlayer);
    
    RectangleShape ball;
    ball.setSize(Vector2f(50,50));
    ball.setPosition(400,200);
    ball.setTexture(&textBall);


    //gameloop
    while (game == true)
    {
        //events
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                game = false;
            }
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
            yVelocityPlayer1 = -5;
        }
        
        if (down == true && up == false)
        {
            yVelocityPlayer1 = 5;
        }

        if (down == false && up == false || up == true && down == true )
        {
            yVelocityPlayer1 = 0;
        }

        Player1.move(0,yVelocityPlayer1);

        //pad out of screen check
        if (Player1.getPosition().y < 0)
        {
            Player1.setPosition(50,0);
        }
        
        if (Player1.getPosition().y >500 )
        {
            Player1.setPosition(50,500);
        }
        
        if (ball.getPosition().x < -50)
        {
            //Player2Score++;
            ball.setPosition(300, 200);
        }
        
        if (ball.getPosition().x < 550)
        {
            //Player1Score++;
            ball.setPosition(300,200);
        }
        

        //collision Player1
        if (ball.getGlobalBounds().intersects(Player1.getGlobalBounds())==true)
        {
            xVelocityBall = - yVelocityBall;
        }
        //collision Player2
        if (ball.getGlobalBounds().intersects(Player2.getGlobalBounds())==true)
        {
            xVelocityBall = - yVelocityBall;
        }

        //Player2
        if (ball.getPosition().y < Player2.getPosition().y)
        {
            yVelocityPlayer2 = -2;
        }
        
        if (ball.getPosition().y > Player2.getPosition().y)
        {
            yVelocityPlayer2 = 2;
        }

        Player2.move(0, yVelocityPlayer2);    

        //ball
        ball.move(xVelocityBall,yVelocityBall);
        if ( ball.getPosition().y < 0 || ball.getPosition().y >550 )
        {
            yVelocityBall = -yVelocityBall;
        }

        // rendering
        window.clear();

        window.draw(background);
        window.draw(Player1);
        window.draw(Player2);
        window.draw(ball);

        // std::stringstream text;
        // text << Player1Score << " : " << Player2Score;
        // score.setString(text.str());
        // window.draw(score);

        window.display();
    }
    

    window.close();

    return 0;
}