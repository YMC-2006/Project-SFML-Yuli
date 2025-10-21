#include <iostream>
#include <ctime>   // para time()
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "board.h"
#include "Gem.h"
#include "IceGem.h"
#include "NormalGem.h"
#include "BombGem.h"
using namespace std;
using namespace sf;


int randType;
Board::Board(const LevelConfig& config) {

   
    totalMoves = config.moves;
    targetScore = config.targetScore;
    gemTask = config.gemTask;
    gemTaskAmount = config.gemTaskAmount;

    
    this->levelNumber = config.levelNumber;
    this->hasIceBlocks = config.hasIceBlocks;
    this->enableBombGems = config.enableBombGems;

    fillMatrix();
   
}

void Board::generateIceGems() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[0][0] = new IceGem();
           
            
        }
    }

}

void Board::drawScene(RenderWindow& window, Event& event) {


    Texture backgroundIMG;
    if (!backgroundIMG.loadFromFile("assets/backgroundGame5.png")) {
        throw runtime_error("ERROR! couldnt load the bg image");
    }
    Sprite spriteBackImg(backgroundIMG);

    Texture cursor;
    cursor.loadFromFile("assets/cursor.png");
    Sprite spriteCursor(cursor);
    Vector2i mousePosCursor = Mouse::getPosition(window);
    spriteCursor.setPosition(static_cast<float>(mousePosCursor.x), static_cast<float>(mousePosCursor.y));
   

    window.draw(spriteBackImg);
    drawText(window);
    bool isThereMatch = progress();
    barProgress(window, event, isThereMatch);
    drawBoard(window);  // <-- draw the board
    window.draw(spriteCursor);

}

void Board::fillMatrix() {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
            
            
            randType = noInitialMatch(i,j); //Obtains the correct texture, not 3 equals in the same row
            if (i==0 && j==0 && enableBombGems) {
                matrix[i][j] = new BombGem(randType);
            }
            else if (i == 4 && j == 4 && hasIceBlocks) {
                matrix[i][j] = new IceGem(randType);
            }
            else {
                matrix[i][j] = new Gem();
                matrix[i][j]->initGem(randType);
            }
           
			matrix[i][j]->getSprite().setPosition(250 + 70.f * i, 200 + 70.f * j);
			matrix[i][j]->getSprite().setOrigin(
				matrix[i][j]->getSprite().getTexture()->getSize().x / 2.f,
				matrix[i][j]->getSprite().getTexture()->getSize().y / 2.f
			); //now the center of the gem is the origin and not a corner
		}		
	}
}

void Board::drawBoard(RenderWindow &window) {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

            if (matrix[i][j]->getType() == -1) {
                continue;
            }
			
			if (matrix[i][j]->isSelected()) {
               
				matrix[i][j]->getSprite().setColor(Color(200, 200, 255)); // it darkess the color of the gem
				matrix[i][j]->getSprite().setScale(.80f, .80f);
				
			}
			else {
               
				matrix[i][j]->getSprite().setScale(.70f, .70f);
				matrix[i][j]->getSprite().setColor(Color::White);
			}

            window.draw(matrix[i][j]->getSprite());
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
                if (matrix[i][j]->getSprite().getGlobalBounds().contains(mousePosF)) {
                  

                    clickSound.play();
                    Gem* clickedGem = matrix[i][j];
                  
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
                                Vector2f pos1 = matrix[x1][y1]->getSprite().getPosition();
                                Vector2f pos2 = matrix[x2][y2]->getSprite().getPosition();
                               
                              


                                animateSwap(*matrix[x1][y1], *matrix[x2][y2], pos1, pos2, window);  // we swap them with movement
                                swap(matrix[x1][y1], matrix[x2][y2]);  // swap them on the matrix

                                bool m1 = checkMatchAt(x1, y1);
                                bool m2 = checkMatchAt(x2, y2);
                                int centerX = 0, centerY = 0;

                                if (checkMatchAt(x1, y1) || checkMatchAt(x2, y2)) { // If there is a match we add points and delete the match, then call the gravity func
                                    

                                    if (m1 && m2) {
                                        cout << "\n\nDouble match [" << x1 << "][" << y1 << "]\n";
                                        cout << "Double match [" << x2 << "][" << y2 << "]\n";
                                       
                        
                                        updateGemTaskProgress();
                                       
                                        
                                    }
                                    else if (m1) {
                                        cout << "Match on x1,y1  [" << x1 << "][" << y1 << "]\n";
                                       
                                        updateGemTaskProgress();
                                        centerX = x1;
                                        centerY = y1;

                                    }
                                    
                                    else if(m2) {
                                        cout << "Match on x2,y2  [" << x2 << "][" << y2 << "]\n";
                                       
                                        updateGemTaskProgress();
                                        centerX = x2;
                                        centerY = y2;
                                    }
                                    
                                    int totalMatched = 0;
                                    cout << "A match was found :D" << endl;

                                    int gemsMatched = countPoints(); // returns total with values per type
                                    totalMatched += gemsMatched;
                                    pointsCounter += gemsMatched;   
                                    totalMoves -= 1;
                                    
                         
                                    floatingTexts(window, gemsMatched);


                                    // Cascade Loop
                                    while (deleteMatch()) {
                                        pullGravity();
                                        animateGravity(window);

                                        // 🔹 Nueva verificación de matches tras la gravedad
                                        bool cascadeHasMatch = false;
                                        for (int i = 0; i < size; i++) {
                                            for (int j = 0; j < size; j++) {
                                                if (checkMatchAt(i, j)) {
                                                    cascadeHasMatch = true;
                                                }
                                            }
                                        }

                                        if (cascadeHasMatch) {
                                            int cascadeMatch = countPoints(); // now checks and counts the points normally
                                            totalMatched += cascadeMatch;
                                            pointsCounter += cascadeMatch;  // 
                                            floatingTexts(window, cascadeMatch);
                                            updateGemTaskProgress();
                                        }
                                    }


                                   

                                    /*if (gemsMatched >= 4 && enableBombGems) {

                                        int type = matrix[centerX][centerY]->getType();
                                        Vector2f gemPos = matrix[centerX][centerY]->getSprite().getPosition();
                                        delete matrix[centerX][centerY];
                                        matrix[centerX][centerY] = new BombGem(type);
                                        matrix[centerX][centerY]->getSprite().setPosition(gemPos);

                                        cout << "💣 Bomb gem created at [" << centerX << "][" << centerY << "]!\n";


                                    }*/

                                    if (totalMoves <= 0) {
                                        window.close();
                                        game.runThirdWindow(pointsCounter, gemTaskAmount);
                                    }



                                }
                                else { // If there is not match the gems go back to their original position
                                    errorSound.play();
                                    animateSwap(*matrix[x1][y1], *matrix[x2][y2], pos1, pos2, window);
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


void Board::updateGemTaskProgress() {

    
    int gemsFound = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int type = matrix[i][j]->getType();

            if (type == -1) continue;

            // Si es del tipo objetivo y está en un match, cuenta
            if (type == gemTask && checkMatchAt(i, j)) {
                gemsFound++;
            }
        }
    }

    if (gemsFound > 0) {
        gemTaskAmount -= gemsFound;
        if (gemTaskAmount < 0) gemTaskAmount = 0;

        barPoints = gemsFound; // para la barra
        thereIsProgress = true;
        setProgress(thereIsProgress);

        cout << "Gem task progress (cascade included): " << gemsFound<< endl;
    }

}



int Board::noInitialMatch(int i, int j) {
	
	int randType;

	do {
		randType = rand() % 5;  // rand num between 0 and 4
	} while (
		// horizontal check to the left (two equals in a row)
		(j >= 2 && matrix[i][j - 1]->getType() == randType && matrix[i][j - 2]->getType() == randType) ||
		// vertical check up (two equals in a row)
		(i >= 2 && matrix[i - 1][j]->getType() == randType && matrix[i - 2][j]->getType() == randType)
		);

	return randType;
}

bool Board::checkMatchAt(int x, int y) {
    
    int gemType = matrix[x][y]->getType();
    if (gemType == -1) return false;

    int horizontalCounter = 1, verticalCounter = 1;

    // Horizontal Left
    for (int j = y - 1; j >= 0 && matrix[x][j]->getType() == gemType; j--) horizontalCounter++;
    // Horizontal Right
    for (int j = y + 1; j < size && matrix[x][j]->getType() == gemType; j++) horizontalCounter++;
    if (horizontalCounter >= 3) return true;

    // Vertical Top
    for (int i = x - 1; i >= 0 && matrix[i][y]->getType() == gemType; i--) verticalCounter++;
    // Vertical Bottom
    for (int i = x + 1; i < size && matrix[i][y]->getType() == gemType; i++) verticalCounter++;
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
    int totalPoints = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] && matrix[i][j]->getType() == -1) {  // deleted
                continue;
            }

            
            if (checkMatchAt(i, j)) {
                totalPoints += matrix[i][j]->getPointsValue();
            }
        }
    }

    return totalPoints;
   
}


bool Board::deleteMatch()    {
    bool found = false;
    vector<pair<int, int>> toDelete;

    // Horizontal
    for (int i = 0; i < size; i++) {
        int j = 0;
        while (j < size) {
            int currentGem = matrix[i][j]->getType();
            if (currentGem == -1) { j++; continue; }

            int start = j;
            while (j + 1 < size && matrix[i][j + 1]->getType() == currentGem) j++;
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
            int currentGem = matrix[i][j]->getType();
            if (currentGem == -1) { i++; continue; }

            int start = i;
            while (i + 1 < size && matrix[i + 1][j]->getType() == currentGem) i++;
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
        matrix[p.first][p.second]->setType(-1);

    return found;
}

void Board::pullGravity() {

    const float offsetX = 250.f;   // same values as in fillMatrix
    const float offsetY = 150.f;
    const float tileSize = 70.f;
        
    // Loop through each column
    for (int col = 0; col < size; col++) {

        int emptySpot = size - 1; // start from the bottom

        // --- Download existing gems ---
        for (int row = size - 1; row >= 0; row--) {
            if (matrix[col][row]->getType() != -1) {
                // If we find a valid gem and there's space below it
                if (row != emptySpot) {
                    // We use swap to move the gem and avoid duplicates
                    swap(matrix[col][emptySpot], matrix[col][row]);

                    // We update the visual position
                    matrix[col][emptySpot]->getSprite().setPosition(
                        offsetX + tileSize * col,
                        offsetY + tileSize * emptySpot
                    );

                    // We leave the top position marked as empty
                    matrix[col][row]->setType(-1);
                }
                emptySpot--;
            }
        }

        // --- Generate new gems in the upper slots ---
        for (int row = emptySpot; row >= 0; row--) {
            int newType = rand() % 5; // number of gem types

            // Set the new type (only the value and transparency change)
            matrix[col][row]->setType(newType);

            // Assign the correct texture
            matrix[col][row]->initGem(newType);

            // Screen position
            matrix[col][row]->getSprite().setPosition(
                offsetX + tileSize * col,
                offsetY + tileSize * row
            );
        }
    }
}


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

int Board::getGemTaskAmount() {
    return gemTaskAmount;
}

int Board::getGemTask() {
    return gemTask;
}

void Board::setTask(int gems) {
    gemTask = gems;
}

void Board::initBar() {

    targetProgressPoints = gemTaskAmount;
    currentProgressPoints = 0;
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
   
    Color Green(67, 219, 38);
    Color Purple(150, 32, 216);
    Color Yellow(242, 158, 26);
   
    if (event.type == Event::MouseButtonPressed) {
        Vector2i mousePos = Mouse::getPosition(window);
        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
       
        if (thereIsMatch) {
          
            if (currentProgressPoints < targetProgressPoints) {

                currentProgressPoints += barPoints;
                if (currentProgressPoints > targetProgressPoints) currentProgressPoints = targetProgressPoints;

                float progress = static_cast<float>(currentProgressPoints) / targetProgressPoints;
                fill.setSize(Vector2f(maxWidth * progress, 30));
            }

            // Color changes
            if (levelNumber == 1) fill.setFillColor(Purple);
            if (levelNumber == 2) fill.setFillColor(Yellow);
            if (levelNumber == 3) fill.setFillColor(Green);
            if (levelNumber == 4) fill.setFillColor(Color::Cyan);
            if (levelNumber == 5) fill.setFillColor(Color::Red);
            cout << "Points from this match: " << barPoints << endl;
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
    Text task(to_string(getGemTaskAmount()),font, 40); task.setPosition(250, 20);
    
   
    Sprite taskGem(Gem::getTexture(getGemTask())); taskGem.setScale(.60f, .60f); taskGem.setPosition(150, 80);

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

        Event event;
        window.clear();
        drawScene(window, event);
        window.display();
    }

    // set the final positions
    g1.getSprite().setPosition(targetPos2);
    g2.getSprite().setPosition(targetPos1);
}

void Board::animateGravity(RenderWindow& window) {
    const float duration = 0.7f; // duración total de la animación
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
            startPositions[col * size + row] = matrix[col][row]->getSprite().getPosition();
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
                matrix[col][row]->getSprite().setPosition(pos);
            }
        }
        Event event;
        window.clear();
        drawScene(window, event);
        window.display();
    }

    // Asegurarse que todas las gemas acaben exactamente en su destino
    for (int col = 0; col < size; col++) {
        for (int row = 0; row < size; row++) {
            matrix[col][row]->getSprite().setPosition(endPositions[col * size + row]);
        }
    }
}





void Board::floatingTexts(RenderWindow& window, int matchedGems) {
   

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
        // Here we draw the whole thing background and the floating great and amazing
        window.clear();
        drawScene(window, event); 
        if (matchedGems >= 5) window.draw(amazing);
        else window.draw(great);
        window.display();
       
       
       
    }
}

