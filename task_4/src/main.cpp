#include <SFML/Graphics.hpp>

const sf::Color Gray(128, 128, 128);
const sf::Color Black(0, 0, 0);

const float speed = 100.f;
const float size = 100.f;

struct Position
{
    float xPos;
    float yPos;
};

void move(float dt, Position& position) {
    if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) &&
        position.yPos - speed * dt >= 0
    ) {
        position.yPos -= speed * dt;
    }
    if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) &&
        position.yPos + size + speed * dt <= 600
    ) {
        position.yPos += speed * dt;
    }
    if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) &&
        position.xPos + size + speed * dt <= 800
    ) {
        position.xPos += speed * dt;
    }
    if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) &&
        position.xPos - speed * dt >= 0
    ) {
        position.xPos -= speed * dt;
    }
}

void update(sf::RenderWindow& window, float dt, Position& position) {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }     
    }

    move(dt, position);
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Toktaev"
    );

    sf::Clock clock;
    Position position = {50.f, 50.f};

    sf::RectangleShape player({size, size});
    player.setPosition({position.xPos, position.yPos});
    player.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        update(window, dt, position);

        window.clear(sf::Color::Blue);

        player.setPosition({position.xPos, position.yPos});
        window.draw(player);

        window.display();
    }

    return 0;
}