#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Board.h"
#include <SFML/Audio.hpp>
#include <ctime>
using namespace std;
using namespace sf;

void Game::runMainWindow() {

    RenderWindow windowMain(VideoMode(800, 600), "MATCH-3");

    Texture cursorTexture;
    cursorTexture.loadFromFile("assets/cursor.png");
    Sprite cursor(cursorTexture);
    windowMain.setMouseCursorVisible(false);


    Texture backgroundIMG;
    backgroundIMG.loadFromFile("assets/backgroundIMG.png");
    Sprite spriteBackground(backgroundIMG);

    //-------------------------MUSIKKKK
    Texture musicButton, noMusicButton;
    musicButton.loadFromFile("assets/music.png");
    noMusicButton.loadFromFile("assets/noMusic.png");

    Sprite spriteMusic(musicButton), spriteNoMusic(noMusicButton);
    spriteMusic.setPosition(50, 50);
    spriteMusic.setScale(0.125f, 0.125f);

    spriteNoMusic.setPosition(50, 50);
    spriteNoMusic.setScale(0.125f, 0.125f);

    Music music;
    music.openFromFile("assets/FrozenPines.wav");
    music.setLoop(true); 
    //-------------------------MUSIKKKK

    Texture menu;
    menu.loadFromFile("assets/menuButton.png");
    Sprite spriteMenu(menu);
    spriteMenu.setPosition(395, 255);
    spriteMenu.setScale(0.30f, 0.30f);
    spriteMenu.setOrigin(menu.getSize().x / 2.f, menu.getSize().y / 2.f);

    Texture playButton;
    playButton.loadFromFile("assets/playButto.png");
    Sprite spritePlay(playButton);
    spritePlay.setPosition(395, 370);
    spritePlay.setScale(0.30f, 0.30f);
    spritePlay.setOrigin(playButton.getSize().x / 2.f, playButton.getSize().y);

    Texture credits;
    credits.loadFromFile("assets/credits.png");
    Sprite spriteCredits(credits); 
    spriteCredits.setPosition(395, 440);
    spriteCredits.setScale(0.30f, 0.30f);
    spriteCredits.setOrigin(playButton.getSize().x / 2.f, playButton.getSize().y);

    // Load textures
    Texture texPurple, texBlue, texYellow, texGreen, texRed;
    texPurple.loadFromFile("assets/purpleGem.png");
    texBlue.loadFromFile("assets/blueGem.png");
    texYellow.loadFromFile("assets/gemBombYellow.png");
    texGreen.loadFromFile("assets/greenGem.png");
    texRed.loadFromFile("assets/redGem.png");

    // create sprites
    Sprite purple(texPurple), blue(texBlue), yellow(texYellow), green(texGreen), red(texRed);

    // Starting position of our rotating gems!
    purple.setPosition(200, 170); purple.setScale(.70f, .70f);
    blue.setPosition(290, 170); blue.setScale(.70f, .70f);
    yellow.setPosition(380, 170); yellow.setScale(.80f, .80f);
    green.setPosition(470, 170); green.setScale(.70f, .70f);
    red.setPosition(550, 170); red.setScale(.70f, .70f);

    // Very important to center the ORIGIN so they will rotate on themselves 
    purple.setOrigin(texPurple.getSize().x / 2.f, texPurple.getSize().y / 2.f);
    blue.setOrigin(texBlue.getSize().x / 2.f, texBlue.getSize().y / 2.f);
    yellow.setOrigin(texYellow.getSize().x / 2.f, texYellow.getSize().y / 2.f);
    green.setOrigin(texGreen.getSize().x / 2.f, texGreen.getSize().y / 2.f);
    red.setOrigin(texRed.getSize().x / 2.f, texRed.getSize().y / 2.f);

    Clock clock;
    float rotationSpeed = 100.f; // degrees per second
    bool musicON = false;

    Texture creditsIMG;
    creditsIMG.loadFromFile("assets/creditsBackground.png");
    Sprite spriteCreditBackground(creditsIMG);

    Texture back;
    back.loadFromFile("assets/return.png");
    Sprite spriteReturn(back);
    spriteReturn.setScale(.70f, .70f);
    spriteReturn.setPosition(100.f, 60.f);
    spriteReturn.setOrigin(back.getSize().x / 2.f, back.getSize().y / 2.f);



    // sound for clicking the main buttons

    

    SoundBuffer click;
    Sound clickSound;
    click.loadFromFile("assets/clickButton.wav");
    clickSound.setBuffer(click);

    while (windowMain.isOpen()) {
        Event event;
        while (windowMain.pollEvent(event)) {
            if (event.type == Event::Closed)
                windowMain.close();
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                windowMain.close();

            // MUSIKK
            if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(windowMain);
                Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (musicON && spriteMusic.getGlobalBounds().contains(mousePosF)) {
                    cout << "MUSIKK ;D" << endl;
                    if (music.getStatus() == Music::Playing) {
                        music.stop();
                    }
                    else {
                        music.play();
                    }
                    musicON = false;
                }
                else if (!musicON && spriteNoMusic.getGlobalBounds().contains(mousePosF)) {
                    cout << "NO MUSIKK ;D" << endl;
                   
                    musicON = true;
                    music.play();
                }
            }



            Vector2i mousePos = Mouse::getPosition(windowMain);
            Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            // Hover and Play Button
            if (spritePlay.getGlobalBounds().contains(mousePosF)) {
                
                spritePlay.setScale(0.31f, 0.31f);

                if (event.type == Event::MouseButtonPressed) {
                    clickSound.play();
                    cout << "¡Button PLAY pressed!" << endl;
                    windowMain.close();
                    runLVLwindow();
                   
                }
                else {
                    clickSound.stop();
                }
            }
            else {
                spritePlay.setScale(0.30f, 0.30f);
                
            }

            //Menu test
            if (spriteMenu.getGlobalBounds().contains(mousePosF)) {

                Texture cursor;
                cursor.loadFromFile("assets/cursor.png");
                Sprite spriteCursor(cursor);

                spriteMenu.setScale(0.31f, 0.31f);

                Texture yellowGem;
                yellowGem.loadFromFile("assets/yellowGem.png");
                Sprite spriteYellowGem(yellowGem);
                spriteYellowGem.setPosition(200, 100);

                Texture purpleGem;
                purpleGem.loadFromFile("assets/purpleGem.png");
                Sprite spritePurpleGem(purpleGem);
                spritePurpleGem.setPosition(300, 100);


                //Movement variables
                Vector2f purpleTarget = spritePurpleGem.getPosition();
                Vector2f yellowTarget = spriteYellowGem.getPosition();
                bool purpleMoving = false, yellowMoving = false;
                float velocity = 300.f;
                Sprite* selected = nullptr; // pointer to the selected sprite
                Clock clock;

                if (event.type == Event::MouseButtonPressed) {
                    clickSound.play();
                    RenderWindow windowTest(VideoMode(800,600),"Test");
                    windowTest.setMouseCursorVisible(false);

                    RectangleShape outline(Vector2f(300, 30));
                    outline.setFillColor(Color::Transparent); outline.setOutlineColor(Color::White); outline.setOutlineThickness(2);
                    outline.setPosition(250, 250);
                   

                    RectangleShape fill(Vector2f(0, 30)); fill.setFillColor(Color::Green); fill.setPosition(250, 250);
                    // Progress variables
                    int maxPresses = 15;
                    int presses = 0;
                    float maxWidth = 300.f; // full width of bar
                    Texture tRedGem; tRedGem.loadFromFile("assets/redGem.png");
                    Sprite redGem(tRedGem); redGem.setPosition(300, 300);
                    while (windowTest.isOpen()) {
                         float dt = clock.restart().asSeconds();
                        while (windowTest.pollEvent(event)) {
                            if (event.type == Event::Closed) windowTest.close();
                            if (Keyboard::isKeyPressed(Keyboard::Escape)) windowTest.close();
                            
                            if (event.type == Event::MouseButtonPressed) {
                                Vector2i mousePos = Mouse::getPosition(windowMain);
                                Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                                if (redGem.getGlobalBounds().contains(mousePosF)) {
                                    if (presses < maxPresses) {
                                        presses++;
                                        float progress = (float)presses / maxPresses;
                                        fill.setSize(Vector2f(maxWidth * progress, 30));
                                    }
                                   
                                    if (presses == 3) {
                                        fill.setFillColor(Color::Yellow);
                                    }
                                    if (presses == 6) {
                                        fill.setFillColor(Color::Red);
                                    } if (presses == 9) {
                                        fill.setFillColor(Color::Magenta);
                                    }
                                    if (presses == 15) {
                                        fill.setFillColor(Color::Yellow);
                                      
                                    }
                                    if (presses == maxPresses) {
                                        presses = -15;
                                        maxPresses = 0;
                                        float progress = (float)presses / maxPresses;
                                        fill.setSize(Vector2f(maxWidth * progress, 30));
                                    }
                                }
                               
                            }
                            if (event.type == Event::MouseButtonPressed) {
                                Vector2i mousePos = Mouse::getPosition(windowMain);
                                Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                                if (spriteYellowGem.getGlobalBounds().contains(mousePosF)) {
                                    if (!selected) {
                                        selected = &spritePurpleGem;
                                    }
                                    else {
                                        purpleTarget = selected->getPosition();
                                        if (selected == &spriteYellowGem) {
                                            yellowTarget = spritePurpleGem.getPosition();
                                            purpleMoving = true;
                                        }
                                        yellowMoving = true;
                                        selected = nullptr;
                                    }

                                    cout << "Clicked YELOOOW";
                                }
                                else if(spritePurpleGem.getGlobalBounds().contains(mousePosF)){
                                    if (!selected) {
                                        selected = &spriteYellowGem;
                                    }
                                    else {
                                        yellowTarget = selected->getPosition();
                                        if (selected == &spritePurpleGem) {
                                            purpleTarget = spriteYellowGem.getPosition();
                                            yellowMoving = true;
                                        }
                                        purpleMoving = true;
                                        selected = nullptr;
                                    }
                                }
                            }
                         

                          
                        }
                      

                        //update the movement frame by frame
                        auto moveTowards = [&](Sprite& sprite, Vector2f& target, bool& moving) {
                            if (!moving) return;
                            Vector2f pos = sprite.getPosition();
                            Vector2f dir = target - pos;
                            float dist = sqrt(dir.x * dir.x + dir.y * dir.y);

                            if (dist < 1.f) {
                                sprite.setPosition(target);
                                moving = false;
                            }
                            else {
                                dir /= dist;
                                sprite.move(dir * velocity * dt);
                            }
                            };

                        moveTowards(spritePurpleGem, purpleTarget, purpleMoving);
                        moveTowards(spriteYellowGem, yellowTarget, yellowMoving);

                        windowTest.clear(Color::Blue);
                        windowTest.draw(spriteYellowGem);
                        windowTest.draw(spritePurpleGem);


                        Vector2i mousePosCursor = Mouse::getPosition(windowTest);
                        spriteCursor.setPosition(static_cast<float>(mousePosCursor.x), static_cast<float>(mousePosCursor.y));
                      
                        windowTest.draw(redGem);
                        windowTest.draw(outline); windowTest.draw(fill);
                        windowTest.draw(spriteCursor);
                        windowTest.display();
                       
                    }

                   
                }
                else {
                    clickSound.stop();
                }
            }else{
                spriteMenu.setScale(0.30f, 0.30f);
            }

           

            // CREDITS
            if (spriteCredits.getGlobalBounds().contains(mousePosF)) {
                
                spriteCredits.setScale(0.31f, 0.31f);

                if (event.type == Event::MouseButtonPressed) {
                    clickSound.play();
                    cout << "Button credits pressed!!!!!" << endl;

                    RenderWindow creditsWindow(VideoMode(800, 600), "Credits");
                    creditsWindow.setMouseCursorVisible(false);
                    while (creditsWindow.isOpen()) {
                        Event creditsEvent;
                        while (creditsWindow.pollEvent(creditsEvent)) {
                            if (creditsEvent.type == Event::Closed) {
                                cout << "Credits window closed!";
                                creditsWindow.close();
                                
                            }



                               
                        }
                        //Hover effect
                        Vector2i mousePos = Mouse::getPosition(windowMain);
                        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                        if (spriteReturn.getGlobalBounds().contains(mousePosF)) {
                            spriteReturn.setScale(.80f, .80f);
                            


                            if (creditsEvent.type == Event::MouseButtonPressed) {

                                if (spriteReturn.getGlobalBounds().contains(mousePosF)) {
                                    clickSound.play();
                                    cout << "Credits window closed!";
                                    creditsWindow.close();
                                }
                                else {
                                    clickSound.stop();
                                }
                            }
                        }
                        else {
                            spriteReturn.setScale(.70f, .70f);
                        }

                        
                       

                       
                        creditsWindow.clear();
                        creditsWindow.draw(spriteCreditBackground);
                        creditsWindow.draw(spriteReturn);
                        //Update its position to follow the mouse each frame
                        Vector2i mousePosCursor = Mouse::getPosition(creditsWindow);
                        cursor.setPosition(static_cast<float>(mousePosCursor.x), static_cast<float>(mousePosCursor.y)); cursor.setScale(.60f, .60f);
                        creditsWindow.draw(cursor);
                        creditsWindow.display();
                    }
                }
                else {
                    clickSound.stop();
                }
            }
            else {
                spriteCredits.setScale(0.30f, 0.30f);
            }
        }


        float dt = clock.restart().asSeconds();

        // Rotate each gem on its center
        purple.rotate(rotationSpeed * dt);
        blue.rotate(rotationSpeed * dt);
        yellow.rotate(rotationSpeed * dt);
        green.rotate(rotationSpeed * dt);
        red.rotate(rotationSpeed * dt);



        // Draw the main window
        windowMain.clear();
        windowMain.draw(spriteBackground);
       


        // our rotating gems!!
        windowMain.draw(purple);
        windowMain.draw(blue);
        windowMain.draw(yellow);
        windowMain.draw(green);
        windowMain.draw(red);

        //Buttons
        windowMain.draw(spriteCredits);
        windowMain.draw(spritePlay);
        windowMain.draw(spriteMenu);

        //Music sprite depends on the bool musicON
        if (musicON) {
            windowMain.draw(spriteMusic);
        }
        else {
            windowMain.draw(spriteNoMusic);
        }

        //Update its position to follow the mouse each frame
        Vector2i mousePosCursor = Mouse::getPosition(windowMain);
        cursor.setPosition(static_cast<float>(mousePosCursor.x), static_cast<float>(mousePosCursor.y)); cursor.setScale(.60f, .60f);
        windowMain.draw(cursor);
        windowMain.display();
    }
}
        


void Game::runLVLwindow() {

    Texture txLevel1; txLevel1.loadFromFile("assets/level1.png");
    Sprite level1Button(txLevel1); level1Button.setPosition(70.f, 180.f); level1Button.setScale(.30f, .30f);

    Texture txLevel2; txLevel2.loadFromFile("assets/level2.png");
    Sprite level2Button(txLevel2); level2Button.setPosition(450.f, 350.f); level2Button.setScale(.30f, .30f);

    Texture txLevel3; txLevel3.loadFromFile("assets/level3.png");
    Sprite level3Button(txLevel3); level3Button.setPosition(90.f, 560.f); level3Button.setScale(.30f, .30f);

    Texture txLevel4; txLevel4.loadFromFile("assets/level4.png");
    Sprite level4Button(txLevel4); level4Button.setPosition(450.f, 800.f); level4Button.setScale(.30f, .30f);

    Texture txLevel5; txLevel5.loadFromFile("assets/level5.png");
    Sprite level5Button(txLevel5); level5Button.setPosition(70.f, 1100.f); level5Button.setScale(.30f, .30f);

    //--------------------------------------------------------------------------------------------------------

    RenderWindow levelsWindow(VideoMode(800, 600), "Levels");
    Texture bgTexture; bgTexture.loadFromFile("assets/backgroundLevel.png");
    Sprite bgSprite(bgTexture);

    static SoundBuffer clickBuffer;
    static Sound clickSound;

    clickBuffer.loadFromFile("assets/clickSound.wav");
    clickSound.setBuffer(clickBuffer);
   

    const float scrollSpeed = 10.f;
    View camera(FloatRect(0, 0, 800, 600));
    levelsWindow.setView(camera);

    while (levelsWindow.isOpen()) {
        Event event;
        while (levelsWindow.pollEvent(event)) {
            if (event.type == Event::Closed) levelsWindow.close();


            if (event.type == Event::MouseWheelScrolled) {
                camera.move(0, -event.mouseWheelScroll.delta * scrollSpeed);
            }
           

        }

        //in case the user tries to scroll with the keyboard :)
        if (Keyboard::isKeyPressed(Keyboard::Up)) camera.move(0, -scrollSpeed);
        if (Keyboard::isKeyPressed(Keyboard::Down)) camera.move(0, scrollSpeed);

        float topLimit = 0.f;
        float topBottom = 1600.f - 600.f;
        Vector2f pos = camera.getCenter();
        float halfHeight = camera.getSize().y / 2.f;

        if (pos.y - halfHeight < topLimit)       pos.y = halfHeight;
        if (pos.y + halfHeight > 1600.f)         pos.y = 1600.f - halfHeight;
        camera.setCenter(pos);
        levelsWindow.setView(camera);        


        if (event.type == Event::MouseButtonPressed) {
            Vector2i mousePos = Mouse::getPosition(levelsWindow);
            Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));


            if (level1Button.getGlobalBounds().contains(mousePosF))clickSound.play();runSecondWindow();
            if (level2Button.getGlobalBounds().contains(mousePosF)) runSecondWindow();
            if (level3Button.getGlobalBounds().contains(mousePosF)) runSecondWindow();
            if (level4Button.getGlobalBounds().contains(mousePosF)) runSecondWindow();
            if (level5Button.getGlobalBounds().contains(mousePosF)) runSecondWindow();
        }
      
        levelsWindow.clear();
        levelsWindow.draw(bgSprite);
        levelsWindow.draw(level1Button); levelsWindow.draw(level2Button); levelsWindow.draw(level3Button); levelsWindow.draw(level4Button); levelsWindow.draw(level5Button);
        levelsWindow.display();

    }
}


void Game::runSecondWindow() {

    Texture cursor;
    cursor.loadFromFile("assets/cursor.png");
    Sprite spriteCursor(cursor);
    
    Board board;  

    Texture backgroundIMG;
    backgroundIMG.loadFromFile("assets/backgroundGame3.png");
    Sprite spriteBackImg(backgroundIMG);
    Clock clock;

    RenderWindow gameWindow(VideoMode(1000, 800), "Game");
    gameWindow.setMouseCursorVisible(false);
    board.initBar();
   
    while (gameWindow.isOpen()) {
  
        Event event;
        while (gameWindow.pollEvent(event)) {
            // Close the window
            if (event.type == Event::Closed) {
                gameWindow.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape)) gameWindow.close();
            float deltaTime = clock.restart().asSeconds();
            gameWindow.clear();
            gameWindow.draw(spriteBackImg);
            board.drawBoard(gameWindow);
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            board.drawText(gameWindow, event);
         
           
            board.swapGems(gameWindow, event);
           
           

            Vector2i mousePosCursor = Mouse::getPosition(gameWindow);
            spriteCursor.setPosition(static_cast<float>(mousePosCursor.x), static_cast<float>(mousePosCursor.y));
            gameWindow.draw(spriteCursor);

            bool isThereMatch = board.progress();
            board.barProgress(gameWindow, event, isThereMatch);
           
           


            gameWindow.display();

        }
    }
}

void Game::runThirdWindow(int finalScore) {

    //Cursor load Sprite
    Texture cursor;
    cursor.loadFromFile("assets/cursor.png");
    Sprite spriteCursor(cursor);

    Font font;
    font.loadFromFile("arial.ttf");
    Text text; text.setFont(font); 
    text.setCharacterSize(30); text.setPosition(200.f, 260.f);
    text.setString("Total Points: " + to_string(finalScore));

    Texture background;
    background.loadFromFile("assets/returnBackground.png");
    Sprite spriteBackground(background);


    //BUTTONS
    Texture playTexture;
    playTexture.loadFromFile("assets/playAgain.png");
    Sprite playAgain(playTexture); playAgain.setPosition(300.f, 130.f); playAgain.setScale(.40f, .40f);

    Texture exitTexture;
    exitTexture.loadFromFile("assets/exitAll.png");
    Sprite exitSprite(exitTexture); exitSprite.setPosition(70.f, 125.f); exitSprite.setScale(.40f, .40f);

    Texture homeTexture;
    homeTexture.loadFromFile("assets/backHome.png");
    Sprite homeSprite(homeTexture); homeSprite.setPosition(80.f, 240.f); homeSprite.setScale(.25f, .25f);




    RenderWindow returnWindow(VideoMode(600, 400), "PLAY AGAIN!!");
    returnWindow.setMouseCursorVisible(false);
    while (returnWindow.isOpen()) {
        Event event;
        while (returnWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
               returnWindow.close(); 
               //exit(0); //Closes all the windows
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) returnWindow.close();

            
            if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(returnWindow);
                Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (playAgain.getGlobalBounds().contains(mousePosF)) {
                    returnWindow.close();
                    runSecondWindow();
                    return;
                    
                }

                if (exitSprite.getGlobalBounds().contains(mousePosF)) {
                    cout << "Game Over Thanks For Playing :']"<<endl;
                    exit(0);
                  
                }

                if (homeSprite.getGlobalBounds().contains(mousePosF)) {
                    returnWindow.close();
                    runMainWindow();
                    return;
                }
            }



            returnWindow.clear();
            returnWindow.draw(spriteBackground); 
            returnWindow.draw(text);
            returnWindow.draw(playAgain);
            returnWindow.draw(exitSprite);
            returnWindow.draw(homeSprite);
            Vector2i mousePosCursor = Mouse::getPosition(returnWindow);
            spriteCursor.setPosition(static_cast<float>(mousePosCursor.x), static_cast<float>(mousePosCursor.y));
            returnWindow.draw(spriteCursor);
            returnWindow.display();



        }
    }

}