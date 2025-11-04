#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Board.h"
#include <SFML/Audio.hpp>
#include "TextBox.cpp"
#include <ctime>
using namespace std;
using namespace sf;


Game::Game() {

    levels = {
    //Lvl, moves, targetScore, Amount of gem GOAL, type of the gem ,  Ice blocks, Bomb Gems, unlocked lvl, swap booster
    { 1, 1, 1000, 1, 0, false, false, true, false}, // Purple Gem
    { 2, 1, 2000, 1, 1, false, true, false, false},  // Yellow Gem
    { 3, 1, 3000, 2, 2, true, true, false, false},   // Green Gem
    { 4, 1, 4000, 3, 3, false, true, false, false}, // Blue Gem
    { 5, 1, 5000, 1, 4, false, true, false, true } // Red Gem

    };

}

void Game::drawLoginForm() {
    //Left Right
    TextBox usernameBox(290, 250, 300, 40);
    TextBox passwordBox(290, 310, 300, 40, true);

    Font font;
    font.loadFromFile("arial.ttf");

    Text usernameLabel("Username: ", font, 24);
    usernameLabel.setPosition(160,250);
    Text passwordLabel("Password: ", font, 24);
    passwordLabel.setPosition(160,315);

    Text ErrorText("Error!! You must enter both password and username", font, 22);
    ErrorText.setPosition(200, 370);
    ErrorText.setFillColor(Color::Red);
    bool errorInput = false;
    Clock errorClock;


    Texture tLogin; tLogin.loadFromFile("assets/loginData.png");
    Sprite background(tLogin);

    Texture tLog;tLog.loadFromFile("assets/login.png");
    Sprite loginButton(tLog);
    loginButton.setPosition(440, 460);
    loginButton.setScale(.15f, .15f);
    loginButton.setOrigin(tLog.getSize().x / 2.f, tLog.getSize().y / 2.f);


    RenderWindow loginForm(VideoMode(800, 600), "Login Form");
    while (loginForm.isOpen()) {
        Event e;
        while (loginForm.pollEvent(e)) {
            if (e.type == Event::Closed) exit(0);
            Vector2i mousePos = Mouse::getPosition(loginForm);
            Vector2f mPosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            usernameBox.handleEvent(e, loginForm);
            passwordBox.handleEvent(e, loginForm);


            //Enter
            if (e.type == Event::KeyPressed && e.key.code == Keyboard::Enter) {

                string username = usernameBox.getText();
                string password = passwordBox.getText();

                if (username == "" || password == "") {
                    cout << "HMMM" << endl;
                    errorInput = true;
                    errorClock.restart();
                }
                else {


                    
                    cout << "Username: " << username << "\n";
                    cout << "Password: " << password << "\n";
                    // ⚡ Later we’ll verify user or save to JSON here
                    loginForm.close();
                }

               
                
            }
            //Login button manually
            if (loginButton.getGlobalBounds().contains(mPosF)) {
                loginButton.setScale(.16f, .16f);

                if (e.type == Event::MouseButtonPressed) {
                    cout << "Checking if the acount exists..."<<endl;
                    cout << "Exist -> welcome ifNOT -> ERROR" << endl;

                    string username = usernameBox.getText();
                    string password = passwordBox.getText();

                    if (username == "" || password == "") {
                        cout << "HMMM" << endl;
                        errorInput = true;
                        errorClock.restart();  
                    }
                    else {
                        errorInput = false;
                        cout << "Username: " << username << "\n";
                        cout << "Password: " << password << "\n";
                        // ⚡ Later we’ll verify user or save to JSON here
                        loginForm.close();
                    }

                   
                   
                }

            }
            else {
                loginButton.setScale(.15f, .15f);
            }


        }


        loginForm.clear();
        loginForm.draw(background);
        loginForm.draw(loginButton);
        loginForm.draw(usernameLabel);
        loginForm.draw(passwordLabel);
        usernameBox.draw(loginForm);
        passwordBox.draw(loginForm);
        if (errorInput && errorClock.getElapsedTime().asSeconds() < 2.f) {
        loginForm.draw(ErrorText);
        }
        loginForm.display();
        
    }


}
void Game::drawRegisterForm() {

    TextBox usernameBox(290, 220, 300, 40);
    TextBox passwordBox(290, 280, 300, 40, true);

    Font font;
    font.loadFromFile("arial.ttf");

    Text usernameLabel("Username: ", font, 24);
    usernameLabel.setPosition(160, 220);
    Text passwordLabel("Password: ", font, 24);
    passwordLabel.setPosition(160, 285);

    Text ErrorText("Error!! You must enter both password and username", font, 22);
    ErrorText.setPosition(200, 370);
    ErrorText.setFillColor(Color::Red);
    bool errorInput = false;
    Clock errorClock;

    //------------------------------------------------------------ 
    Texture treg; treg.loadFromFile("assets/registerData.png");
    Sprite background(treg);

    Texture tReg; tReg.loadFromFile("assets/register.png");
    Sprite registerButton(tReg);
    registerButton.setPosition(400, 480);
    registerButton.setScale(.14f, .14f);
    registerButton.setOrigin(tReg.getSize().x / 2.f, tReg.getSize().y);

  

    RenderWindow registerForm(VideoMode(800, 600), "Register Form");
    while (registerForm.isOpen()) {
        Event event;
        while (registerForm.pollEvent(event)) {
            if (event.type == Event::Closed) registerForm.close();

            Vector2i mousePos = Mouse::getPosition(registerForm);
            Vector2f mPosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            usernameBox.handleEvent(event, registerForm);
            passwordBox.handleEvent(event, registerForm);

            if (registerButton.getGlobalBounds().contains(mPosF)) {
                registerButton.setScale(.15f, .15f);

                if (event.type == Event::MouseButtonPressed) {
                    cout << "IF account exist tell them to log in instead...." << endl;
                    cout << "IF NOT create the account!" << endl;

                    string username = usernameBox.getText();
                    string password = passwordBox.getText();


                    if (username == "" || password == "") {
                        errorInput = true;
                        errorClock.restart();
                        cout << "Error!" << endl;
                    }
                    else {
                        cout << "Username: " << username << "\n";
                        cout << "Password: " << password << "\n";

                        // ⚡ Later we’ll verify user or save to JSON here
                        registerForm.close();
                    }

                   
                }

            }
            else {
                registerButton.setScale(.14f, .14f);

            }


            registerForm.clear();
            registerForm.draw(background);
            registerForm.draw(registerButton);
            registerForm.draw(usernameLabel);
            registerForm.draw(passwordLabel);
            usernameBox.draw(registerForm);
            passwordBox.draw(registerForm);
            if (errorInput && errorClock.getElapsedTime().asSeconds() < 2.f) {
                registerForm.draw(ErrorText);
            }
            registerForm.display();
        }

       
    }
}

void Game::userLogin() {

    cout << "Match-3 Login"<<endl;

    Texture tLogin; tLogin.loadFromFile("assets/loginBg.png");
    Sprite background(tLogin);

    Texture tlogin; tlogin.loadFromFile("assets/login.png");
    Sprite loginButton(tlogin);
    loginButton.setPosition(245, 330);
    loginButton.setScale(0.15f, 0.15f);
    loginButton.setOrigin(tlogin.getSize().x / 2.f, tlogin.getSize().y / 2.f);

    Texture treg; treg.loadFromFile("assets/register.png");
    Sprite registerButton(treg);
    registerButton.setPosition(535, 370);
    registerButton.setScale(.14f, .14f);
    registerButton.setOrigin(treg.getSize().x / 2.f, treg.getSize().y);

    Texture t1cat; t1cat.loadFromFile("assets/catFrame1.png");
    Sprite catFrame1(t1cat);
    catFrame1.setPosition(500, 200);
    catFrame1.setScale(.20f, .20f);

    Texture t2cat; t2cat.loadFromFile("assets/catFrame2.png");
    Sprite catFrame2(t2cat);
    catFrame2.setPosition(500, 200);
    catFrame2.setScale(.20f, .20f);

    Sprite* currentCatFrame = &catFrame1;

    RenderWindow loginWindow(VideoMode(800, 600), "Login");

    while (loginWindow.isOpen()) {
        Event event;
        while (loginWindow.pollEvent(event)) {

            if (event.type == Event::Closed) loginWindow.close();
            if (Keyboard::isKeyPressed(Keyboard::Escape)) loginWindow.close();
            Vector2i mousePos = Mouse::getPosition(loginWindow);
            Vector2f mPosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));


            // Hover
            if (loginButton.getGlobalBounds().contains(mPosF)) {
                loginButton.setScale(0.16f, 0.16f);

                if (event.type == Event::MouseButtonPressed) {
                    loginWindow.close();
                    drawLoginForm();
                    cout << "Logiiiiiin" << endl;

                }
            }
            else {
                loginButton.setScale(0.15f, 0.15f); // back to normal size
            }

            if (registerButton.getGlobalBounds().contains(mPosF)) {
                registerButton.setScale(0.15f, 0.15f);
                currentCatFrame = &catFrame2;
                if (event.type == Event::MouseButtonPressed) {
                    loginWindow.close();
                    drawRegisterForm();
                    cout << "Registaaaa"<<endl;
                }
            }
            else {
                registerButton.setScale(0.14f, 0.14f);//normal size
                currentCatFrame = &catFrame1;

            }




            loginWindow.clear();
            loginWindow.draw(background);
            loginWindow.draw(loginButton);
            loginWindow.draw(registerButton);
            loginWindow.draw(*currentCatFrame);
            loginWindow.display();

        }
    }


}

void Game::runGame() {
    cout << "Running game!"<<endl;
    RenderWindow windowMain(VideoMode(800, 600), "MATCH-3");

    Texture cursorTexture;
    cursorTexture.loadFromFile("assets/cursor.png");
    Sprite cursor(cursorTexture);
    windowMain.setMouseCursorVisible(false);


    Texture backgroundIMG;
    backgroundIMG.loadFromFile("assets/backgroundIMG.png");
    Sprite spriteBackground(backgroundIMG);

    //----------------------------------------------------

    Texture t1cat; t1cat.loadFromFile("assets/catFrame1.png");
    Sprite catFrame1(t1cat);
    catFrame1.setPosition(340, 470);
    catFrame1.setScale(.20f, .20f);

    Texture t2cat; t2cat.loadFromFile("assets/catFrame2.png");
    Sprite catFrame2(t2cat);
    catFrame2.setPosition(340, 470);
    catFrame2.setScale(.20f, .20f);

    Sprite* currentCatFrame = &catFrame1;

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
    playButton.loadFromFile("assets/playButton.png");
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
    texPurple.loadFromFile("assets/gemBombPurple.png");
    texBlue.loadFromFile("assets/blueGem.png");
    texYellow.loadFromFile("assets/gemBombYellow.png");
    texGreen.loadFromFile("assets/greenGem.png");
    texRed.loadFromFile("assets/gemBombRed.png");

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
                currentCatFrame = &catFrame2;
                
                if (event.type == Event::MouseButtonPressed) {
                    clickSound.play();
                    windowMain.close();
                    runLevelsWindow();
                   
                }
                else {
                    clickSound.stop();
                }
            }
            else {
                spritePlay.setScale(0.30f, 0.30f);
                currentCatFrame = &catFrame1;
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

        windowMain.draw(*currentCatFrame);

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
        
void Game::runLevelsWindow() {

    Texture txLevel1; txLevel1.loadFromFile("assets/level1Unlocked.png");
    Sprite level1Button(txLevel1); level1Button.setPosition(70.f, 180.f); level1Button.setScale(.30f, .30f);

    Texture txLevel2; txLevel2.loadFromFile("assets/level2Unlocked.png"); 
    Sprite level2Button(txLevel2); level2Button.setPosition(450.f, 350.f); level2Button.setScale(.30f, .30f);

    Texture txLevel3; txLevel3.loadFromFile("assets/level3Unlocked.png");
    Sprite level3Button(txLevel3); level3Button.setPosition(90.f, 560.f); level3Button.setScale(.30f, .30f);

    Texture txLevel4; txLevel4.loadFromFile("assets/level4Unlocked.png");
    Sprite level4Button(txLevel4); level4Button.setPosition(450.f, 800.f); level4Button.setScale(.30f, .30f);

    Texture txLevel5; txLevel5.loadFromFile("assets/level5Unlocked.png");
    Sprite level5Button(txLevel5); level5Button.setPosition(70.f, 1100.f); level5Button.setScale(.30f, .30f);

    //----------------------------------------------------------------------------------------------------------

   

    RenderWindow levelsWindow(VideoMode(800, 600), "Levels");
    Texture bgTexture; bgTexture.loadFromFile("assets/backgroundLevel.png");
    Sprite bgSprite(bgTexture);

    static SoundBuffer clickBuffer;
    static Sound clickSound;

    clickBuffer.loadFromFile("assets/clickSound.wav");
    clickSound.setBuffer(clickBuffer);


    static SoundBuffer errorBuffer;
    static Sound clickErrorSound;

    errorBuffer.loadFromFile("assets/errorSound.wav");
    clickErrorSound.setBuffer(errorBuffer);
   

    const float scrollSpeed = 10.f;
    View camera(FloatRect(0, 0, 800, 600));
    levelsWindow.setView(camera);

    if (!levels[1].isUnlocked) { level2Button.setColor(Color(255, 255, 255, 128));  cout << "Levels 2 is locked again"<<endl;}
    else { level2Button.setColor(Color(255, 255, 255, 255)); cout << "Level 2 in UNLOCKED PLAYY"<<endl; }

    if (!levels[2].isUnlocked) { level3Button.setColor(Color(255, 255, 255, 128)); }
    else { level2Button.setColor(Color(255, 255, 255, 255)); }

    if (!levels[3].isUnlocked) { level4Button.setColor(Color(255, 255, 255, 128)); }
    else { level4Button.setColor(Color(255, 255, 255, 255)); }

    if (!levels[4].isUnlocked) { level5Button.setColor(Color(255, 255, 255, 128)); }
    else { level5Button.setColor(Color(255, 255, 255, 255)); }
 
   

    while (levelsWindow.isOpen()) {
        Event event;
        while (levelsWindow.pollEvent(event)) {
            if (event.type == Event::Closed)
                levelsWindow.close();

            if (event.type == Event::MouseWheelScrolled)
                camera.move(0, -event.mouseWheelScroll.delta * scrollSpeed);

           

            if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(levelsWindow);
                Vector2f mousePosF = levelsWindow.mapPixelToCoords(mousePos);

              

                if (level1Button.getGlobalBounds().contains(mousePosF) && levels[0].isUnlocked) { clickSound.play(); levelsWindow.close(); runSecondWindow(levels[0]); }
                if (level2Button.getGlobalBounds().contains(mousePosF) && levels[1].isUnlocked) { clickSound.play(); levelsWindow.close(); runSecondWindow(levels[1]); }
                if (level3Button.getGlobalBounds().contains(mousePosF) && levels[2].isUnlocked) { clickSound.play(); levelsWindow.close(); runSecondWindow(levels[2]); }
                if (level4Button.getGlobalBounds().contains(mousePosF) && levels[3].isUnlocked) { clickSound.play(); levelsWindow.close(); runSecondWindow(levels[3]); }
                if (level5Button.getGlobalBounds().contains(mousePosF) && levels[4].isUnlocked) { clickSound.play(); levelsWindow.close(); runSecondWindow(levels[4]); }
                
                
                
               
            
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

       


        levelsWindow.clear();
        levelsWindow.draw(bgSprite);
        levelsWindow.draw(level1Button);
        levelsWindow.draw(level2Button);
        levelsWindow.draw(level3Button);
        levelsWindow.draw(level4Button);
        levelsWindow.draw(level5Button);
       
        levelsWindow.display();

    }

}

void Game::runSecondWindow(const LevelConfig& config) {

   
   
    Texture cursor;
    cursor.loadFromFile("assets/cursor.png");
    Sprite spriteCursor(cursor);

    Texture swapB; swapB.loadFromFile("assets/swapBooster.png");
    Sprite swapBooster;
    swapBooster.setTexture(swapB); swapBooster.setPosition(900.f, 300.f);
    swapBooster.setScale(.10f, .10f);
    
    Board board(config);

    Texture backgroundIMG;
    backgroundIMG.loadFromFile("assets/backgroundGame5.png");
    Sprite spriteBackImg(backgroundIMG);
    Clock clock;

    RenderWindow gameWindow(VideoMode(1000, 800), "Game");
    gameWindow.setMouseCursorVisible(false);
    board.initBar();

    // Info of the specific level
    cout << "Level " << config.levelNumber << endl;
    cout << "Moves: " << config.moves << " | Target: " << config.targetScore << " | Type of Gem : " << config.gemTask << endl;
    cout << "Amount of gems to collect: " << config.gemTaskAmount << endl;
   
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
            board.drawText(gameWindow);
            board.swapGems(gameWindow, event);
           
            Vector2i mousePosCursor = Mouse::getPosition(gameWindow);
            spriteCursor.setPosition(static_cast<float>(mousePosCursor.x), static_cast<float>(mousePosCursor.y));
           
            bool isThereMatch = board.progress();
            board.barProgress(gameWindow, event, isThereMatch);

           
            
            if (config.levelNumber == 5) {
             gameWindow.draw(swapBooster);
             if (event.type == Event::MouseButtonPressed) {
                 Vector2f mousePosF = static_cast<Vector2f>(Mouse::getPosition(gameWindow));
                 if (config.swapBooster && swapBooster.getGlobalBounds().contains(mousePosF)) {
                     board.activateBooster();
                 }


                
             }
            }

            
            
            gameWindow.draw(spriteCursor);
            gameWindow.display();

        }

       
    }

    
}

void Game::runThirdWindow(int finalScore, int gemTaskAmount, int levelCompleted) {

    

   

    //Cursor load Sprite
    Texture cursor;
    cursor.loadFromFile("assets/cursor.png");
    Sprite spriteCursor(cursor);

    Font font;
    font.loadFromFile("arial.ttf");
    Text text; text.setFont(font); 
    text.setCharacterSize(30); text.setPosition(370.f, 430.f);
    text.setString("Total Points: " + to_string(finalScore));

    Texture tWon;
    tWon.loadFromFile("assets/gameOverWon.png");
    Sprite backgroundWon(tWon);

    Texture tLost;
    tLost.loadFromFile("assets/gameOverLost.png");
    Sprite backgroundLost(tLost);


    //BUTTONS
    Texture playTexture;
    playTexture.loadFromFile("assets/playAgain.png");
    Sprite playAgain(playTexture); playAgain.setPosition(470.f, 290.f); playAgain.setScale(.40f, .40f);

    Texture exitTexture;
    exitTexture.loadFromFile("assets/exitAll.png");
    Sprite exitSprite(exitTexture); exitSprite.setPosition(170.f, 290.f); exitSprite.setScale(.40f, .40f);

    Texture homeTexture;
    homeTexture.loadFromFile("assets/backHome.png");
    Sprite homeSprite(homeTexture); homeSprite.setPosition(250.f, 410.f); homeSprite.setScale(.25f, .25f);




    RenderWindow returnWindow(VideoMode(800, 600), "PLAY AGAIN!!");
    if (gemTaskAmount == 0) cout << "You won";
    else cout << "you lost";

    if (gemTaskAmount <= 0) {
        cout << "Level " << levelCompleted << " completed!! ";
        updateUnlockedLevels(levelCompleted);
    }

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
                    runLevelsWindow();
                    return;
                        
                }

                if (exitSprite.getGlobalBounds().contains(mousePosF)) {
                    cout << "Game Over Thanks For Playing :']"<<endl;
                    exit(0);
                  
                }

                if (homeSprite.getGlobalBounds().contains(mousePosF)) {
                    returnWindow.close();
                    runGame();
                    return;
                }
            }



            returnWindow.clear();
            if(gemTaskAmount==0)returnWindow.draw(backgroundWon);
            else returnWindow.draw(backgroundLost);
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

void Game::updateUnlockedLevels(int completedLevel) {

    if (completedLevel < 1 || completedLevel >= levels.size()) return;

    levels[completedLevel].isUnlocked = true;
   
    cout << "Level " << completedLevel + 1 << " just got unlocked!!!"<<endl;

    
}

void Game::setLevels(int index, bool complete) {

    levels[index].isUnlocked = complete;

}