#include <SFML/Graphics.hpp>

const float SPEED = 100.f;
const float SIZE = 100.f;

struct Position
{
    float xPos;
    float yPos;
};

void Move(float dt, Position& position) {
    if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) &&
        position.yPos - SPEED * dt >= 0
    ) {
        position.yPos -= SPEED * dt;
    }
    if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) &&
        position.yPos + SIZE + SPEED * dt <= 600
    ) {
        position.yPos += SPEED * dt;
    }
    if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) &&
        position.xPos + SIZE + SPEED * dt <= 800
    ) {
        position.xPos += SPEED * dt;
    }
    if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) &&
        position.xPos - SPEED * dt >= 0
    ) {
        position.xPos -= SPEED * dt;
    }
}

void Update(sf::RenderWindow& window, float dt, Position& position) {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }     
    }

    Move(dt, position);
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Toktaev"
    );

    sf::Clock clock;
    Position position = {50.f, 50.f};

    sf::RectangleShape player({SIZE, SIZE});
    player.setPosition({position.xPos, position.yPos});
    player.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        Update(window, dt, position);

        window.clear(sf::Color::Blue);

        player.setPosition({position.xPos, position.yPos});
        window.draw(player);

        window.display();
    }

    return 0;
}