#include "Home.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "../Game/GameState.h"
#include <iostream>

constexpr int FIRST_LEVEL = 1;
constexpr int SECOND_LEVEL = 2;
constexpr int THIRD_LEVEL = 3;

void Home::RenderHome(sf::RenderWindow& window) {
    sf::RectangleShape rectLevel1({200.f, 50.f});
    rectLevel1.setPosition({100.f, 100.f});
    rectLevel1.setFillColor(sf::Color::Red);

    sf::RectangleShape rectLevel2({200.f, 50.f});
    rectLevel2.setPosition({100.f, 200.f});
    rectLevel2.setFillColor(sf::Color::Blue);

    sf::RectangleShape rectLevel3({200.f, 50.f});
    rectLevel3.setPosition({100.f, 300.f});
    rectLevel3.setFillColor(sf::Color::Green);

    window.draw(rectLevel1);
    window.draw(rectLevel2);
    window.draw(rectLevel3);
}

GameState Home::HandleHomeStateChange(
    const sf::Event::MouseButtonPressed* mousePressed, 
    sf::RenderWindow* window,
    GameState currentState,
    Level& level
) {
    if (mousePressed) {
        if (mousePressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f pos = window->mapPixelToCoords(mousePressed->position);

            if (sf::FloatRect({100.f, 100.f}, {200.f, 50.f}).contains(pos)) {
                level.Init(FIRST_LEVEL);
                return levelState;
            } else if (sf::FloatRect({100.f, 200.f}, {200.f, 50.f}).contains(pos)) {
                level.Init(SECOND_LEVEL);
                return levelState;
            } else if (sf::FloatRect({100.f, 300.f}, {200.f, 50.f}).contains(pos)) {
                level.Init(THIRD_LEVEL);
                return levelState;
            }
        }
    }

    return currentState;
}