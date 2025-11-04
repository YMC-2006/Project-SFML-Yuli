#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;


class TextBox {
private:
    RectangleShape box;
    Text text;
    Font font;
    bool isSelected = false;
    bool isPassword = false;
    string input;
    int maxChars = 10;

public:
    TextBox(float x, float y, float width, float height, bool password = false) {
        font.loadFromFile("arial.ttf"); 
        isPassword = password;

        box.setPosition(x, y);
        box.setSize({ width, height });
        box.setFillColor(Color(255, 255, 255, 255));
        box.setOutlineColor(Color::Black);
        box.setOutlineThickness(2);

        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(Color::Black);
        text.setPosition(x + 10, y + 5);
    }

    void handleEvent(const Event& event, const RenderWindow& window) {
        if (event.type == Event::MouseButtonPressed) {
            Vector2f mousePos = (Vector2f)Mouse::getPosition(window);
            isSelected = box.getGlobalBounds().contains(mousePos);
            box.setOutlineColor(isSelected ? Color::Cyan : Color::Black);
        }

        if (isSelected && event.type == Event::TextEntered) {
            if (event.text.unicode == 8) { // Backspace deletes! very important
                if (!input.empty()) input.pop_back();
            }
            else if (event.text.unicode == 13) {
                isSelected = false; // Enter key = stop typing
            }
            else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                if (input.size() < maxChars) {
                    input += static_cast<char>(event.text.unicode);
                }
               // else nothing happens it doesn't add anything else :)
            }

            string display = isPassword ? string(input.size(), '*') : input; // type text is hidden by *
            text.setString(display); // just to display the **
        }
    }

    void draw(RenderWindow& window) {
        window.draw(box);
        window.draw(text);
    }

    string getText() const { return input; }
    void clear() { input.clear(); text.setString(""); }
};
