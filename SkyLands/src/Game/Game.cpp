#include "Game.h"
#include <algorithm>
#include <iostream>

const float FLOOR_Y = 700.0f;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Game::Game()
    :   window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "SkyLands"),
        view(sf::FloatRect({0.0f, 0.0f}, {WINDOW_WIDTH, WINDOW_HEIGHT}))
{

}

sf::Vector2f Game::CountCameraPosition() {
    sf::Vector2f targetCenter = player.GetPosition();

    float minX = WINDOW_WIDTH / 2.0f;
    float maxX = map.GetWidth() * TILE_SIZE - WINDOW_WIDTH / 2.0f;
    float minY = WINDOW_HEIGHT / 2.0f;
    float maxY = map.GetHeight() * TILE_SIZE - WINDOW_HEIGHT / 2.0f;

    float clampedX = std::clamp(targetCenter.x, minX, maxX);
    float clampedY = std::clamp(targetCenter.y, minY, maxY);

    return {clampedX, clampedY};
}

void Game::Run()
{
    map.MapInit();

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        sf::Vector2f tileSetSize = {
            static_cast<float>(map.GetWidth() * TILE_SIZE), 
            static_cast<float>(map.GetHeight() * TILE_SIZE)
        };
        player.Update(dt, tileSetSize, FLOOR_Y, map);

        view.setCenter(CountCameraPosition());

        window.setView(view);
        map.MapDraw(window);
        player.Draw(window);

        window.display();
    }
}

//надо ВЕЗДЕ сделать префиксную нотацию m_
