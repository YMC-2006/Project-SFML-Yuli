#include <iostream>
#include <ctime>   // para time()
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "board.h"
#include "Gem.h"
using namespace std;
using namespace sf;


int randTexture;

Board::Board() { //Constructor vacido

	textures[0].loadFromFile("assets/purpleGem.png");
	textures[1].loadFromFile("assets/yellowGem.png");
	textures[2].loadFromFile("assets/greenGem.png");
	textures[3].loadFromFile("assets/blueGem.png");
	textures[4].loadFromFile("assets/redGem.png");
	fillMatrix();
}


void Board::fillMatrix() {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
		
			randTexture = noInitialMatch(i,j); //Obtains the correct texture, not 3 equals in the same row
		
			matrix[i][j].initMatrix(randTexture, textures[randTexture]);
			matrix[i][j].getSprite().setPosition(250 + 70.f * i,180 + 70.f * j);
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
                                // we swap them
                                matrix[x1][y1].getSprite().setPosition(pos2);
                                matrix[x2][y2].getSprite().setPosition(pos1);

                                // swap them on the matrix
                              
                                swap(matrix[x1][y1], matrix[x2][y2]);


                                if (checkMatchAt(x1, y1) || checkMatchAt(x2, y2)) { // If there is a match we add points and delete the match, then call the gravity func
                                    cout << "A match was found :D" << endl;
                                    int gemsMatched = countPoints();
                                    pointsCounter += gemsMatched * 10;
                                    totalMoves -= 1;

                                    // Bucle de cascada
                                    while (deleteMatch()) {
                                        pullGravity();
                                    }


                                    if (totalMoves <= 0 ) {
                                        window.close();
                                        game.runThirdWindow(pointsCounter);
                                    }
                                    
                                }
                                else { // If there is not match the gems go back to their original position

                                    swap(matrix[x1][y1], matrix[x2][y2]);
                                    matrix[x1][y1].getSprite().setPosition(pos1);
                                    matrix[x2][y2].getSprite().setPosition(pos2);
                                    errorSound.play();
                                    cout << "No match :v" << endl;
                                    window.draw(noMatchText);
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
		randType = rand() % 5;  // generamos entre 0 y 4
	} while (
		// chequea horizontal a la izquierda (dos iguales seguidos)
		(j >= 2 && matrix[i][j - 1].getType() == randType && matrix[i][j - 2].getType() == randType) ||
		// chequea vertical arriba (dos iguales seguidos)
		(i >= 2 && matrix[i - 1][j].getType() == randType && matrix[i - 2][j].getType() == randType)
		);

	return randType;
}

bool Board::checkMatchAt(int x, int y) {
    
    int gemType = matrix[x][y].getType();
    if (gemType == -1) return false;

    int horizontalCounter = 1, verticalCounter = 1;

    // Horizontal
    for (int j = y - 1; j >= 0 && matrix[x][j].getType() == gemType; j--) horizontalCounter++;
       
    
    for (int j = y + 1; j < size && matrix[x][j].getType() == gemType; j++) horizontalCounter++;
    if (horizontalCounter >= 3) return true;

    // Vertical
    for (int i = x - 1; i >= 0 && matrix[i][y].getType() == gemType; i--) verticalCounter++;
    for (int i = x + 1; i < size && matrix[i][y].getType() == gemType; i++) verticalCounter++;
    if (verticalCounter >= 3) return true;

    return false;
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
                    if (!marked[i][k]) {        // ✅ no volver a contar
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
                    if (!marked[k][j]) {        // ✅ no volver a contar
                        marked[k][j] = true;
                        totalGems++;
                    }
                    k++;
                }
            }
        }
    }

    return totalGems; // número exacto de gemas únicas
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

    // Eliminar
    for (auto& p : toDelete)
        matrix[p.first][p.second].setType(-1);

    return found;
}

void Board::pullGravity() {

    const float offsetX = 250.f;   // same values as in fillMatrix
    const float offsetY = 180.f;
    const float tileSize = 70.f;

    // Recorremos cada columna
    for (int col = 0; col < size; col++) {

        int emptySpot = size - 1;  // comenzamos desde abajo

        // --- Bajar gemas existentes ---
        for (int row = size - 1; row >= 0; row--) {
            if (matrix[col][row].getType() != -1) {
                // Si encontramos una gema válida y hay hueco debajo
                if (row != emptySpot) {
                    // Usamos swap para mover la gema y evitar duplicados
                    swap(matrix[col][emptySpot], matrix[col][row]);

                    // Actualizamos la posición visual
                    matrix[col][emptySpot].getSprite().setPosition(
                        offsetX + tileSize * col,
                        offsetY + tileSize * emptySpot
                    );

                    // Dejamos la posición de arriba marcada como vacía
                    matrix[col][row].setType(-1);
                }
                emptySpot--;
            }
        }

        // --- Generar nuevas gemas en los huecos superiores ---
        for (int row = emptySpot; row >= 0; row--) {
            int newType = rand() % 5; // número de tipos de gema

            // Marcamos el nuevo tipo (solo cambia el valor y transparencia)
            matrix[col][row].setType(newType);

            // Asignamos la textura correcta 
            matrix[col][row].getSprite().setTexture(textures[newType]);

            // Posición en pantalla
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

void Board::drawText(RenderWindow& window, Event& event) {


    Font font;
    font.loadFromFile("arial.ttf");
    Text points (to_string(getPoints()), font, 40); points.setPosition(450, 46);
    Text moves (to_string(getMoves()), font, 40); moves.setPosition(760, 46);

    window.draw(points);
    window.draw(moves);

}

void Board::startShake(RenderWindow& window, Gem& g1, Gem& g2, Vector2f pos1, Vector2f pos2) {

    const float offSet = 5.f;
    const int cycles = 3;
    const Time delay = milliseconds(30);

    for (int c = 0; c < cycles; c++) {
        g1.getSprite().setPosition(pos1.x + offSet, pos1.y);
        g2.getSprite().setPosition(pos2.x - offSet, pos2.y);
        window.draw(g1.getSprite()); // Redibuja (necesitas acceso al window)
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