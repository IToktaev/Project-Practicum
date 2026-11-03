#include "Menu.h"
#include <SFML/Graphics/RectangleShape.hpp>

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