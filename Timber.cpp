// Timber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber", Style::Fullscreen);


    // BACKGROUND -------------------------------
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");

    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    // TREE ------------------------------------
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    // BEE ----------------------------------------
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");

    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    bool beeActive = false;
    float beeSpeed = 0.2f;

    // CLOUDS --------------------------------------
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");

    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;

    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);
    
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);

    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    Clock clock;

    // TIME BAR -------------------------------------
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;


    bool paused = true;

    int score = 0;

    // TEXT ----------------------------------------
    Text messageText;
    Text scoreText;

    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    messageText.setFont(font);
    scoreText.setFont(font);

    messageText.setString("Press Enter to start!");
    scoreText.setString("Score = 0");

    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    // POSITION THE TEXT --------------------------------
    FloatRect textRect = messageText.getLocalBounds();

    messageText.setOrigin(textRect.left +
        textRect.width / 2.0f,
        textRect.top +
        textRect.height / 2.0f);

    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    while (window.isOpen()) {
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;

            score = 0;
            timeRemaining = 6.0f;
        }

        window.clear();

        if (!paused) {
            Time dt = clock.restart();

            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * 
                timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f) {
                paused = true;
                messageText.setString("Out of time!");

                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left +
                    textRect.width / 2.0f,
                    textRect.top +
                    textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }

            // BEE -----------------------------------------
            if (!beeActive) {
                srand((int)time(0));
                beeSpeed = (rand() % 200) + 200;

                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else {
                spriteBee.setPosition(
                    spriteBee.getPosition().x -
                    (beeSpeed * dt.asSeconds()),
                    spriteBee.getPosition().y);

                if (spriteBee.getPosition().x < -100) {
                    beeActive = false;
                }
            }

            // CLOUDS ----------------------------------------
            if (!cloud1Active) {
                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 200);

                srand((int)time(0) * 10);
                float height = (rand() % 150);
                spriteCloud1.setPosition(-200, height);
                cloud1Active = true;
            }
            else {
                spriteCloud1.setPosition(
                    spriteCloud1.getPosition().x +
                    (cloud1Speed * dt.asSeconds()),
                    spriteCloud1.getPosition().y);

                if (spriteCloud1.getPosition().x > 1920) {
                    cloud1Active = false;
                }
            }

            if (!cloud2Active) {
                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);

                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                spriteCloud2.setPosition(-200, height);
                cloud2Active = true;
            }
            else {
                spriteCloud2.setPosition(
                    spriteCloud2.getPosition().x +
                    (cloud2Speed * dt.asSeconds()),
                    spriteCloud2.getPosition().y);

                if (spriteCloud2.getPosition().x > 1920) {
                    cloud2Active = false;
                }
            }

            if (!cloud3Active) {
                srand((int)time(0) * 30);
                cloud3Speed = (rand() % 200);

                srand((int)time(0) * 30);
                float height = (rand() % 450) - 150;
                spriteCloud3.setPosition(-200, height);
                cloud3Active = true;
            }
            else {
                spriteCloud3.setPosition(
                    spriteCloud3.getPosition().x +
                    (cloud1Speed * dt.asSeconds()),
                    spriteCloud3.getPosition().y);

                if (spriteCloud3.getPosition().x > 1920) {
                    cloud3Active = false;
                }
            }

            // UPDATE THE SCORE TEXT
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
        }

        

        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);
        window.draw(spriteBee);

        window.draw(scoreText);
        window.draw(timeBar);

        if (paused) {
            window.draw(messageText);
        }

        window.display();
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
