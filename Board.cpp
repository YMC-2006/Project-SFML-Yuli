#include <iostream>
#include <ctime>   // para time()
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "board.h"
#include "Gem.h"
using namespace std;
using namespace sf;


int randType;
Board::Board(const LevelConfig& config) {

    totalMoves = config.moves;
    targetScore = config.targetScore;
    gemTask = config.gemTask;
    gemType = config.typeGem;
    this->levelNumber = config.levelNumber;
    this->hasIceBlocks = config.hasIceBlocks;
    this->enableBombGems = config.enableBombGems;

    textures[0].loadFromFile("assets/purpleGem.png");
    textures[1].loadFromFile("assets/yellowGem.png");
    textures[2].loadFromFile("assets/greenGem.png");
    textures[3].loadFromFile("assets/blueGem.png");
    textures[4].loadFromFile("assets/redGem.png");
    fillMatrix();

}

Board::Board() { //Constructor vacido

	
}


void Board::fillMatrix() {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
		
            randType = noInitialMatch(i,j); //Obtains the correct texture, not 3 equals in the same row
		
			matrix[i][j].initGem(randType, textures[randType]);
			matrix[i][j].getSprite().setPosition(250 + 70.f * i,200 + 70.f * j);
			matrix[i][j].getSprite().setOrigin(
				matrix[i][j].getSprite().getTexture()->getSize().x / 2.f,
				matrix[i][j].getSprite().getTexture()->getSize().y / 2.f
			); //now the center of the gem is the origin and not a corner
		}		
	}
}

void Board::drawBoard(RenderWindow &window) {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

            if (matrix[i][j].getType() == -1) {
                continue;
            }
			
			
			if (matrix[i][j].isSelected()) {
               
				matrix[i][j].getSprite().setColor(Color(200, 200, 255)); // it darkess the color of the gem
				matrix[i][j].getSprite().setScale(.80f, .80f);
				
			}
			else {
               
				matrix[i][j].getSprite().setScale(.70f, .70f);
				matrix[i][j].getSprite().setColor(Color::White);
			}

            window.draw(matrix[i][j].getSprite());
		}
	}
}


void Board::swapGems(RenderWindow& window, Event& event) {

    Game game;
  
    static SoundBuffer clickBuffer;
    static Sound clickSound;
   
    
    clickBuffer.loadFromFile("assets/clickButton.wav");
    clickSound.setBuffer(clickBuffer);
    clickSound.setVolume(100.f);

    static SoundBuffer errorBuffer;
    static Sound errorSound;
    errorBuffer.loadFromFile("assets/errorSound.wav");
    errorSound.setBuffer(errorBuffer);


    Font font;
    font.loadFromFile("arial.ttf");
    Text noMatchText("No match FOUND !!!", font, 30); noMatchText.setFillColor(Color::Red);
    noMatchText.setPosition(350.f, 750.f);
    

    if (event.type == Event::MouseButtonPressed) {
        Vector2i mousePos = Mouse::getPosition(window);
        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        thereIsProgress = false; // I had to put it here again as false bc, if there a match, the variable stays on true, even if we are then just randomly clicking on another gem
        setProgress(thereIsProgress); // and it works here and not if the user clicks on the gem because it sets false, if the user clicks on the gem but what if the user click on any other part of the screen

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (matrix[i][j].getSprite().getGlobalBounds().contains(mousePosF)) {
                  

                    clickSound.play();
                    Gem* clickedGem = &matrix[i][j];
                  
                    // There's still no selected gem, so we select the one the user just clicked on
                    if (selectedGem == nullptr) {
                       
                        clickedGem->setSelected(true);
                        selectedGem = clickedGem;

                        // For the swap we save the cordinates
                        x1 = i;
                        y1 = j;
                        cout << "First [" << i << "][" << j << "]" << endl;
                       
                    }
                    else {
                       
                        // this is the case 2, where the user clicks the same gem so we de-select it
                        if (selectedGem == clickedGem) {
                            selectedGem->setSelected(false);
                            selectedGem = nullptr;
                        }
                        else {
                            // in this case 3 where the user clicks a different gem
                            // we save the cordinates of the new gem clicked
                            int x2 = i, y2 = j;
                            int ady = abs(x1 - x2) + abs(y1 - y2);

                            if (ady == 1) {

                                cout << "Swap [" << x1 << "][" << y1 << "] <-> [" << x2 << "][" << y2 << "]" << endl;

                                // Save the positions of the first and second gem clicked
                                Vector2f pos1 = matrix[x1][y1].getSprite().getPosition();
                                Vector2f pos2 = matrix[x2][y2].getSprite().getPosition();
                               
                              


                                animateSwap(matrix[x1][y1], matrix[x2][y2], pos1, pos2, window);  // we swap them with movement
                                swap(matrix[x1][y1], matrix[x2][y2]);  // swap them on the matrix


                                if (checkMatchAt(x1, y1) || checkMatchAt(x2, y2)) { // If there is a match we add points and delete the match, then call the gravity func
                                    
                                    if (checkMatchAt(x1, y1) && checkMatchAt(x2, y2)) {
                                        cout << "\n\nDouble match [" << x1 << "][" << y1 << "]\n";
                                        cout << "Double match [" << x2 << "][" << y2 << "]\n";
                                        int gemType1 = matrix[x1][y1].getType();
                                        int gemType2 = matrix[x2][y2].getType();
                                        cout << "Gem Type: " << gemType1 << endl;
                                        cout << "Gem Type: " << gemType2 << endl;
                                    }
                                    else if (checkMatchAt(x1, y1)) {
                                        cout << "Match on x1,y1  [" << x1 << "][" << y1 << "]\n";
                                        int gemType = matrix[x1][y1].getType();
                                        cout << "Gem Type: " << gemType << endl;
                                    }
                                    
                                    else if(checkMatchAt(x2, y2)) {
                                        cout << "Match on x2,y2  [" << x2 << "][" << y2 << "]\n";
                                        int gemType = matrix[x2][y2].getType();
                                        cout << "Gem Type: " << gemType << endl;
                                    }
                                    
                                    cout << "A match was found :D" << endl;
                                    int gemsMatched = countPoints();
                                    pointsCounter += gemsMatched * 10;
                                    totalMoves -= 1;
                                    thereIsProgress = true;
                                    setProgress(thereIsProgress);
                                    
                                    if (gemsMatched > 3) {
                                        cout << "Match 4+ gems";
                                    }
                                  
                                    floatingTexts(window, gemsMatched);

                                    // Bucle de cascada
                                    while (deleteMatch()) {
                                        pullGravity();
                                        //animateGravity(window);
                                    }


                                    if (totalMoves <= 0) {
                                        window.close();
                                        game.runThirdWindow(pointsCounter);
                                    }



                                }
                                else { // If there is not match the gems go back to their original position
                                    errorSound.play();
                                    animateSwap(matrix[x1][y1], matrix[x2][y2], pos1, pos2, window);
                                    swap(matrix[x1][y1], matrix[x2][y2]); // Back to normal 
                                   
                                    cout << "No match :v" << endl;
                                    //window.draw(noMatchText);
                                   
                                }
                            }
                           
                            // Reset selección
                            selectedGem->setSelected(false);
                            clickedGem->setSelected(false);
                            selectedGem = nullptr;
                        }
                       
                    }

                    return; 
                }
                
            }
        }
    }
}



int Board::noInitialMatch(int i, int j) {
	
	int randType;

	do {
		randType = rand() % 5;  // rand num between 0 and 4
	} while (
		// horizontal check to the left (two equals in a row)
		(j >= 2 && matrix[i][j - 1].getType() == randType && matrix[i][j - 2].getType() == randType) ||
		// vertical check up (two equals in a row)
		(i >= 2 && matrix[i - 1][j].getType() == randType && matrix[i - 2][j].getType() == randType)
		);

	return randType;
}

bool Board::checkMatchAt(int x, int y) {
    
    int gemType = matrix[x][y].getType();
    if (gemType == -1) return false;

    int horizontalCounter = 1, verticalCounter = 1;

    // Horizontal Left
    for (int j = y - 1; j >= 0 && matrix[x][j].getType() == gemType; j--) horizontalCounter++;
    // Horizontal Right
    for (int j = y + 1; j < size && matrix[x][j].getType() == gemType; j++) horizontalCounter++;
    if (horizontalCounter >= 3) return true;

    // Vertical Top
    for (int i = x - 1; i >= 0 && matrix[i][y].getType() == gemType; i--) verticalCounter++;
    // Vertical Bottom
    for (int i = x + 1; i < size && matrix[i][y].getType() == gemType; i++) verticalCounter++;
    if (verticalCounter >= 3) return true;

    return false;
}

bool Board::progress() {
    return thereIsProgress;
}
void Board::setProgress(bool p) {
    thereIsProgress = p;
}

int Board::countPoints() {
    int totalGems = 0;
    bool marked[8][8] = { false };

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int currentType = matrix[i][j].getType();
            if (currentType == -1) continue;

            // ---- Horizontal ----
            if (j < size - 2 && matrix[i][j + 1].getType() == currentType &&
                matrix[i][j + 2].getType() == currentType)
            {
                int k = j;
                while (k < size && matrix[i][k].getType() == currentType) {
                    if (!marked[i][k]) {        //  dont count again
                        marked[i][k] = true;
                        totalGems++;
                    }
                    k++;
                }
            }

            // ---- Vertical ----
            if (i < size - 2 && matrix[i + 1][j].getType() == currentType &&
                matrix[i + 2][j].getType() == currentType)
            {
                int k = i;
                while (k < size && matrix[k][j].getType() == currentType) {
                    if (!marked[k][j]) {        //  dont count again
                        marked[k][j] = true;
                        totalGems++;
                    }
                    k++;
                }
            }
        }
    }

    return totalGems; // exact number of unique gems
    cout << "Total gems found in line: "<<totalGems<<endl;
   
}


bool Board::deleteMatch()    {
    bool found = false;
    vector<pair<int, int>> toDelete;

    // Horizontal
    for (int i = 0; i < size; i++) {
        int j = 0;
        while (j < size) {
            int currentGem = matrix[i][j].getType();
            if (currentGem == -1) { j++; continue; }

            int start = j;
            while (j + 1 < size && matrix[i][j + 1].getType() == currentGem) j++;
            int len = j - start + 1;

            if (len >= 3) {
                found = true;
                for (int k = start; k <= j; k++) {
                    toDelete.push_back({ i,k });
                }
           
            }
            j++;
        }
    }

    // Vertical
    for (int j = 0; j < size; j++) {
        int i = 0;
        while (i < size) {
            int currentGem = matrix[i][j].getType();
            if (currentGem == -1) { i++; continue; }

            int start = i;
            while (i + 1 < size && matrix[i + 1][j].getType() == currentGem) i++;
            int len = i - start + 1;

            if (len >= 3) {
                found = true;
                for (int k = start; k <= i; k++)
                    toDelete.push_back({ k,j });
            }
            i++;
        }
    }

    // Delete
    for (auto& p : toDelete)
        matrix[p.first][p.second].setType(-1);

    return found;
}

void Board::pullGravity() {

    const float offsetX = 250.f;   // same values as in fillMatrix
    const float offsetY = 200.f;
    const float tileSize = 70.f;
        
    // Loop through each column
    for (int col = 0; col < size; col++) {

        int emptySpot = size - 1; // start from the bottom

        // --- Download existing gems ---
        for (int row = size - 1; row >= 0; row--) {
            if (matrix[col][row].getType() != -1) {
                // If we find a valid gem and there's space below it
                if (row != emptySpot) {
                    // We use swap to move the gem and avoid duplicates
                    swap(matrix[col][emptySpot], matrix[col][row]);

                    // We update the visual position
                    matrix[col][emptySpot].getSprite().setPosition(
                        offsetX + tileSize * col,
                        offsetY + tileSize * emptySpot
                    );

                    // We leave the top position marked as empty
                    matrix[col][row].setType(-1);
                }
                emptySpot--;
            }
        }

        // --- Generate new gems in the upper slots ---
        for (int row = emptySpot; row >= 0; row--) {
            int newType = rand() % 5; // number of gem types

            // Set the new type (only the value and transparency change)
            matrix[col][row].setType(newType);

            // Assign the correct texture
            matrix[col][row].getSprite().setTexture(textures[newType]);

            // Screen position
            matrix[col][row].getSprite().setPosition(
                offsetX + tileSize * col,
                offsetY + tileSize * row
            );
        }
    }
}

/*void Board::deleteGem(RenderWindow& window, Event& event) {

    if (event.type == Event::MouseButtonPressed) {
        Vector2i mousePos = Mouse::getPosition(window);
        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (matrix[i][j].getSprite().getGlobalBounds().contains(mousePosF)) {
                    matrix[i][j].getSprite().setPosition(-1213.f,-4324.f);
                    cout << "Deleted gem ["<<i<<"]["<<j<<"]"<<endl;

                }
            }
        }

    }

}*/

int Board::getPoints() {
    return pointsCounter;
}

int Board::getMoves() {
    return totalMoves;
}

void Board::setPoints(int p) {
    pointsCounter = p;
}

void Board::setMoves(int m) {
    totalMoves = m;
}

int Board::getGemTask() {
    return gemTask;
}

void Board::setTask(int gems) {
    gemTask = gems;
}

void Board::initBar() {
    maxPresses = totalMoves;
    presses = 0;
    maxWidth = 300.f;

    // Outline
    outline.setSize(Vector2f(300, 30)); outline.setFillColor(Color::Transparent);
    outline.setOutlineColor(Color::White); outline.setOutlineThickness(2);
    outline.setPosition(100, 550); outline.rotate(-90);

    // Fill
    fill.setSize(Vector2f(0, 30)); fill.setFillColor(Color::Green); fill.setPosition(100, 550);
    fill.rotate(-90);
   
}

void Board::barProgress(RenderWindow& window, Event& event, bool thereIsMatch) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2i mousePos = Mouse::getPosition(window);
        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        if (thereIsMatch) {
            if (presses < maxPresses) {
                presses++;
                float progress = static_cast<float>(presses) / maxPresses;
                fill.setSize(Vector2f(maxWidth * progress, 30));
            }

            // Color changes
            if (presses == 3) fill.setFillColor(Color::Red);
            if (presses == 6) fill.setFillColor(Color::Yellow);
            if (presses == 9) fill.setFillColor(Color::Green);
            if (presses == 15) fill.setFillColor(Color::Cyan);
        }
    }

    // Dibujamos siempre (independientemente de si hay click o no)
    
    window.draw(outline);
    window.draw(fill);
}

void Board::drawText(RenderWindow& window) {


    Font font;
    font.loadFromFile("arial.ttf");
    Text points(to_string(getPoints()), font, 40); points.setPosition(570, 20);
    Text moves(to_string(getMoves()), font, 40); moves.setPosition(880, 20);
    Text task(to_string(getGemTask()), font, 40); task.setPosition(250, 20);

    Texture textureGem; textureGem.loadFromFile("assets/gemBombRed.png");
    Sprite taskGem(textureGem); taskGem.setScale(.60f, .60f); taskGem.setPosition(200, 80);

    window.draw(points);
    window.draw(moves);
    window.draw(task);
    window.draw(taskGem);

}

void Board::startShake(RenderWindow& window, Gem& g1, Gem& g2, Vector2f pos1, Vector2f pos2) {

    //Shake animation
    static float offSet = 5.f;
    static int cycles = 3;
    static Time delay = milliseconds(30); // If this generates any erros move it back as atributes with const not static

    for (int c = 0; c < cycles; c++) {
        g1.getSprite().setPosition(pos1.x + offSet, pos1.y);
        g2.getSprite().setPosition(pos2.x - offSet, pos2.y);
        window.draw(g1.getSprite()); 
        window.display();
        sleep(delay); 

        g1.getSprite().setPosition(pos1.x - offSet, pos1.y);
        g2.getSprite().setPosition(pos2.x + offSet, pos2.y);

        window.draw(g2.getSprite());
        window.display();
        sleep(delay);
    }

    g1.getSprite().setPosition(pos1);
    g2.getSprite().setPosition(pos2);
}

void Board::animateSwap(Gem& g1, Gem& g2, Vector2f targetPos1, Vector2f targetPos2, RenderWindow& window) {

    Texture backgroundIMG;
    backgroundIMG.loadFromFile("assets/backgroundGame4.png");
    Sprite spriteBackImg(backgroundIMG);

    const float duration = .4f;
    float elapsed = 0.f;
    Clock clock;

    Vector2f start1 = g1.getSprite().getPosition();
    Vector2f start2 = g2.getSprite().getPosition();
    Event event;
    while (elapsed < duration) {
        float dt = clock.restart().asSeconds();
        elapsed += dt;
        float t = min(elapsed / duration, 1.f);

        float smoothT = t * t * (3 - 2 * t);

        // move the sprites progresibly
        g1.getSprite().setPosition(start1 + (targetPos2 - start1) * smoothT);
        g2.getSprite().setPosition(start2 + (targetPos1 - start2) * smoothT);

        // draw the frame by frame as they move
        window.clear();
        window.draw(spriteBackImg);
        drawText(window);
        bool isThereMatch = progress();
        barProgress(window, event, isThereMatch);
        drawBoard(window);  // <-- draw the board
        window.display();
    }

    // set the final positions
    g1.getSprite().setPosition(targetPos2);
    g2.getSprite().setPosition(targetPos1);
}

void Board::animateGravity(RenderWindow& window) {
    const float duration = 0.2f; // duración total de la animación
    Clock clock;
    float elapsed = 0.f;

    // Guardamos las posiciones iniciales y finales de cada gema
    vector<Vector2f> startPositions(size * size);
    vector<Vector2f> endPositions(size * size);

    const float offsetX = 250.f;
    const float offsetY = 200.f;
    const float tileSize = 70.f;

    for (int col = 0; col < size; col++) {
        for (int row = 0; row < size; row++) {
            startPositions[col * size + row] = matrix[col][row].getSprite().getPosition();
            endPositions[col * size + row] = Vector2f(
                offsetX + tileSize * col,
                offsetY + tileSize * row
            );
        }
    }

    // Bucle de animación
    while (elapsed < duration) {
        float dt = clock.restart().asSeconds();
        elapsed += dt;
        float t = min(elapsed / duration, 1.f);

        // interpolación suave (ease-out)
        float smoothT = t * t * (3 - 2 * t);

        for (int col = 0; col < size; col++) {
            for (int row = 0; row < size; row++) {
                Vector2f pos = startPositions[col * size + row] +
                    (endPositions[col * size + row] - startPositions[col * size + row]) * smoothT;
                matrix[col][row].getSprite().setPosition(pos);
            }
        }

        // Dibujar toda la escena (no solo las gemas)
        window.clear();
        drawBoard(window); // <--- función que dibuja TODO: fondo, texto, barra, etc.
        window.display();
    }

    // Asegurarse que todas las gemas acaben exactamente en su destino
    for (int col = 0; col < size; col++) {
        for (int row = 0; row < size; row++) {
            matrix[col][row].getSprite().setPosition(endPositions[col * size + row]);
        }
    }
}


void Board::generateBombGem(Gem& g, int typeGem, Vector2f pos, Texture& tex) {
    Sprite sprite;
    bool isBomb = true;
    if (typeGem == 0) {
        //Generate a purple bomb gem
        
        g.getSprite().setPosition(pos);
    }
}


void Board::floatingTexts(RenderWindow& window, int matchedGems) {
    Texture backgroundIMG;
    backgroundIMG.loadFromFile("assets/backgroundGame4.png");
    Sprite spriteBackImg(backgroundIMG);

    if (matchedGems <= 3) return; // Only enter if worth it lol

    // Animation Variables :D
    const float duration = 0.6f;
    float elapsed = 0.f;
    Clock clock;

    Texture textAmazing;
    textAmazing.loadFromFile("assets/amazing.png");
    Sprite amazing(textAmazing);
    amazing.setScale(0.5f, 0.5f);
    amazing.setPosition(250.f, 150.f);

    Texture textGreat;
    textGreat.loadFromFile("assets/great.png");
    Sprite great(textGreat);
    great.setScale(0.5f, 0.5f);
    great.setPosition(250.f, 150.f);

    // ⚙️ Starting and finish position
    Vector2f startPos(250.f, 150.f);
    Vector2f endPos(250.f, 50.f); // goes up a little bit

    // ✨ Animation Lopp
    while (elapsed < duration) {
        float dt = clock.restart().asSeconds();
        elapsed += dt;
        float t = min(elapsed / duration, 1.f);
        float smoothT = t * t * (3 - 2 * t);

        // Movement from bottom to top
        Vector2f pos = startPos + (endPos - startPos) * smoothT;

        // FADE
        int alpha = static_cast<int>(255 * (1.f - t));
        if (alpha < 0) alpha = 0;

        if (matchedGems >= 5) {
            amazing.setPosition(pos);
            amazing.setColor(Color(255, 255, 255, alpha));
        }
        else {
            great.setPosition(pos);
            great.setColor(Color(255, 255, 255, alpha));
        }

         
        Event event;
        window.clear();

        window.draw(spriteBackImg);
        drawText(window);
        bool isThereMatch = progress();
        barProgress(window, event, isThereMatch);
        drawBoard(window);  // <-- draw the board

        if (matchedGems >= 5) window.draw(amazing);
        else window.draw(great);

        window.display();
    }
}
