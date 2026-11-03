#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class Menu {
    public: 
        void RenderMenu(sf::RenderWindow& window);
        void BackToLevel();
        void ToHome();
};