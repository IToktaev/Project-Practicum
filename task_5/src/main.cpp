#include <SFML/Graphics.hpp>

const float PLAYER_SPEED = 100.f;
const float PLAYER_SIZE = 100.f;
const sf::Color PLAYER_COLOR = sf::Color::Red;

struct Player
{
    float speed;
    sf::Color color;
    sf::Vector2f position;
    float xSize;
    float ySize;

    sf::RectangleShape spriteRect;
};

void move(sf::Vector2f& position, float dt) {
    if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) &&
        position.y - PLAYER_SPEED * dt >= 0
    ) {
        position.y -= PLAYER_SPEED * dt;
    }
    if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) &&
        position.y + PLAYER_SIZE + PLAYER_SPEED * dt <= 600
    ) {
        position.y += PLAYER_SPEED * dt;
    }
    if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) &&
        position.x + PLAYER_SIZE + PLAYER_SPEED * dt <= 800
    ) {
        position.x += PLAYER_SPEED * dt;
    }
    if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) &&
        position.x - PLAYER_SPEED * dt >= 0
    ) {
        position.x -= PLAYER_SPEED * dt;
    }
}

void playerUpdate(Player& player, float dt) {
    move(player.position, dt);

    player.spriteRect.setPosition({player.position.x, player.position.y});
    player.spriteRect.setFillColor(player.color);
}

void playerInit(Player& player) {
    player.xSize = PLAYER_SIZE;
    player.ySize = PLAYER_SIZE;
    player.speed = PLAYER_SPEED;
    player.color = PLAYER_COLOR;

    player.spriteRect.setSize({
        player.xSize,
        player.ySize
    });

    player.spriteRect.setPosition(player.position);
    player.spriteRect.setFillColor(player.color);
}

void playerDraw(sf::RenderWindow& window, Player player) {
    window.draw(player.spriteRect);
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Toktaev"
    );

    sf::Clock clock;
    Player player;
    
    playerInit(player);

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }     
        }

        playerUpdate(player, dt);

        window.clear(sf::Color::Blue);

        playerDraw(window, player);

        window.display();
    }

    return 0;
}