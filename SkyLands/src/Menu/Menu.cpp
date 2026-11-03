#include "Menu.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "../Game/GameState.h"
#include <iostream>

void Menu::RenderMenu(sf::RenderWindow& window) {
    sf::RectangleShape toHome({200.f, 50.f});
    toHome.setPosition({100.f, 100.f});
    toHome.setFillColor(sf::Color::Red);

    sf::RectangleShape toLevel({200.f, 50.f});
    toLevel.setPosition({100.f, 200.f});
    toLevel.setFillColor(sf::Color::Blue);

    window.draw(toHome);
    window.draw(toLevel);
}

GameState Menu::HandleMenuStateChange(
    const sf::Event::MouseButtonPressed* mousePressed, 
    sf::RenderWindow* window
) {
     if (mousePressed) {
        if (mousePressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f pos = window->mapPixelToCoords(mousePressed->position);

            if(sf::FloatRect({100.f, 100.f}, {200.f, 50.f}).contains(pos)) {
                return homeState;
                std::cout << "To Home\n";
            }

            if(sf::FloatRect({100.f, 200.f}, {200.f, 50.f}).contains(pos)) {
                return levelState;
                std::cout << "Back to level\n";
            }
        }
    }
}