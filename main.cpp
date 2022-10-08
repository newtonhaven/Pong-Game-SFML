#include <SFML/Graphics.hpp>
#include <sstream>
#include <SFML/Audio.hpp>
using namespace sf;

int main(){

    //creation
    RenderWindow window(VideoMode(800,600), "Pong Game");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    Event event;

    //states
    bool up = false; //vars for key binding
    bool down = false;
    bool wkey = false;
    bool skey = false;
    
    //variables
    int yVelocityPlayer1 = 0;
    int yVelocityPlayer2 = 0;
    int xVelocityBall = -4;
    int yVelocityBall = -4;
    int Player1Score = 0;
    int Player2Score = 0;
    bool winner = false;
    bool multiplayer = false;
    // //resorces
    Font font;
    if (!font.loadFromFile("res/arial.ttf")) return 1;
    
    Text score;
    score.setFont(font);
    score.setCharacterSize(30);
    score.setPosition(250,10);
    score.setString("0 : 0");

    Text credits;
    credits.setFont(font);
    credits.setCharacterSize(15);
    credits.setPosition(400,10);
    credits.setString("Press Numbers For change Skins not numlock numbers\n1-football Ball by gothicfan95\n2-Cannonball by Dansevenstar\n3-Egg Blast by OnTheBus\4-Sky background by PauR\n5-Background Night by Alekei\n6-Starfield background by Sauer2\n7-Multiplayer W&S Player1- Up&Down Player2\nall res from opengameart.org");

    //loading images and checking if files are opened

    Texture textPlayer;
    if (!textPlayer.loadFromFile("res/player.png")) return -1;   
    Texture textBall;
    if (!textBall.loadFromFile("res/ball.png")) return -1;  
    Texture textBacground;
    if (!textBacground.loadFromFile("res/sky.png")) return -1;   
    //sound
    SoundBuffer buffer;
    if (!buffer.loadFromFile("res/hit.wav")) return -1;

    Sound hitSound;
    hitSound.setBuffer(buffer);
    
    // textures
    RectangleShape background;
    background.setSize(Vector2f(800,600));
    background.setPosition(0,0);
    background.setTexture(&textBacground);

    RectangleShape Player1;
    Player1.setSize(Vector2f(5,100));
    Player1.setPosition(50,200);
    Player1.setTexture(&textPlayer);

    RectangleShape Player2;
    Player2.setSize(Vector2f(5,100));
    Player2.setPosition(700,200);
    Player2.setTexture(&textPlayer);
    
    RectangleShape ball;
    ball.setSize(Vector2f(50,50));
    ball.setPosition(400,200);
    ball.setTexture(&textBall);


    //GAMELOOP
    while (window.isOpen() && !Keyboard::isKeyPressed(Keyboard::Escape))
    {
        //events
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();

            //player 1 key press
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up) up = true;
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down) down = true;
            //player 1 key relase
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Up) up = false;
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Down) down = false;
            //player 2 key press
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::W) wkey = true;
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::S) skey = true;
            //relase
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::W) wkey = false;
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::S) skey = false;

            //background and ball texture change
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num1)
            {
                if (!textBall.loadFromFile("res/ball.png")) return -1;
            } 
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num2)
            {
                if (!textBall.loadFromFile("res/canon.png")) return -1;
            }  
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num3)
            {
                if (!textBall.loadFromFile("res/egg.png")) return -1;
            }  
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num4)
            {
                if (!textBacground.loadFromFile("res/sky.png")) return -1;
            } 
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num5)
            {
                if (!textBacground.loadFromFile("res/moon.png")) return -1; 
            }  
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num6)
            {
                if (!textBacground.loadFromFile("res/starfield.png")) return -1; 
            }

            // MULTIPLAYER
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num7) multiplayer = true;
        }
        
        //LOGIC
        if ( wkey == true && skey == false ) yVelocityPlayer1 = -5;
        if ( skey == true && wkey == false ) yVelocityPlayer1 = 5;
        if ( skey == false && wkey == false || wkey == true && skey == true ) yVelocityPlayer1 = 0;

        //move player


        //SCREEN LIMITS & COLLISION
        //screen limit for player1
        if ( Player1.getPosition().y < 0 ) Player1.setPosition(50,0); // TOP
        if ( Player1.getPosition().y > 500 )Player1.setPosition(50,500); //BOTTOM
        //screen limit for player2
        if ( Player2.getPosition().y < 0 )Player2.setPosition(700,0); // TOP
        if ( Player2.getPosition().y > 500 )Player2.setPosition(700,500); // BOTTOM
        //ball limits
        if ( ball.getPosition().x < -50)//left of the screen
        {
            Player2Score++;
            ball.setPosition(300, 200);
        }
        if ( ball.getPosition().x > 750)//right of the screen
        {
            Player1Score++;
            ball.setPosition(300, 200);
        }
        if ( ball.getPosition().y < 0 || ball.getPosition().y >550 ) yVelocityBall = -yVelocityBall; // Top & bottom
        //ball collision for Player1
        if ( ball.getGlobalBounds().intersects(Player1.getGlobalBounds()) == true )
        {
            xVelocityBall = -xVelocityBall;
            hitSound.play();
        }
        //ball collision for Player2
        if ( ball.getGlobalBounds().intersects(Player2.getGlobalBounds()) == true )
        {
            xVelocityBall = -xVelocityBall;
            hitSound.play();
        }

        //player 2 (follows ball)
        if (!multiplayer)
        {
            if ( ball.getPosition().y < Player2.getPosition().y ) yVelocityPlayer2 = -2;
            if ( ball.getPosition().y > Player2.getPosition().y ) yVelocityPlayer2 = 2;
        }

        if(multiplayer)
        {
            if ( up == true && down == false ) yVelocityPlayer2 = -5;
            if ( down == true && up == false ) yVelocityPlayer2 = 5;
            if ( down == false && up == false || up == true && down == true ) yVelocityPlayer2 = 0;
        }

        //movements
        Player1.move(0,yVelocityPlayer1); 
        Player2.move(0, yVelocityPlayer2);    
        ball.move(xVelocityBall,yVelocityBall);

        // rendering
        window.clear();

        window.draw(background);
        window.draw(Player1);
        window.draw(Player2);
        window.draw(ball);

        std::stringstream text;
        text << Player1Score << " : " << Player2Score;
        score.setString(text.str());

        window.draw(score);
        window.draw(credits);

        window.display();
    }
    
    window.close();

    return 0;
}