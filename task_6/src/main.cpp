#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const float PLAYER_SPEED = 100.f;
const float PLAYER_SIZE = 100.f;
const sf::Color PLAYER_COLOR = sf::Color::Green;

const sf::Vector2 ENEMY_VELOCITY = {200.f, 150.f};
const sf::Color ENEMY_COLOR = sf::Color::Yellow;
const sf::Color ENEMY_INTERSECTION_COLOR = sf::Color::Red;
const float ENEMY_X_SIZE = 100.f;
const float ENEMY_Y_SIZE = 50.f;

struct Player
{
    float speed;
    sf::Color color;
    sf::Vector2f position;
    sf::Vector2f size;

    sf::RectangleShape spriteRect;
};

struct Enemy {
    sf::Vector2f size;
    sf::Vector2f velocity;
    sf::Vector2f position;
    sf::Color color;

    sf::RectangleShape spriteRect;
};

void Move(sf::Vector2f& position, float dt) {
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
        position.y + PLAYER_SIZE + PLAYER_SPEED * dt <= WINDOW_HEIGHT
    ) {
        position.y += PLAYER_SPEED * dt;
    }
    if (
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) &&
        position.x + PLAYER_SIZE + PLAYER_SPEED * dt <= WINDOW_WIDTH
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

void PlayerUpdate(Player& player, float dt) {
    Move(player.position, dt);

    player.spriteRect.setPosition({player.position.x, player.position.y});
    player.spriteRect.setFillColor(player.color);
}

void PlayerInit(Player& player) {
    player.size.x = PLAYER_SIZE;
    player.size.y = PLAYER_SIZE;
    player.speed = PLAYER_SPEED;
    player.color = PLAYER_COLOR;
    player.position = {50.f, 50.f};

    player.spriteRect.setSize({
        player.size.x,
        player.size.y
    });

    player.spriteRect.setPosition(player.position);
}

void PlayerDraw(sf::RenderWindow& window, Player player) {
    window.draw(player.spriteRect);
}

void EnemyInit(Enemy& enemy) {
    enemy.size.x = ENEMY_X_SIZE;
    enemy.size.y = ENEMY_Y_SIZE;
    enemy.color = ENEMY_COLOR;
    enemy.velocity = ENEMY_VELOCITY;
    enemy.position = {200.f, 200.f};

    enemy.spriteRect.setSize({
        enemy.size.x,
        enemy.size.y
    });

    enemy.spriteRect.setPosition(enemy.position);
    enemy.spriteRect.setFillColor(enemy.color);
}

void EnemyUpdate(Enemy& enemy, float dt) {
    if (
        enemy.position.x + enemy.velocity.x * dt <= 0 ||
        enemy.position.x + enemy.velocity.x * dt >= WINDOW_WIDTH - enemy.size.x
    ) {
        enemy.velocity.x = -enemy.velocity.x;
    }

    if (
        enemy.position.y + enemy.velocity.y * dt <= 0 ||
        enemy.position.y + enemy.velocity.y * dt >= WINDOW_HEIGHT - enemy.size.y
    ) {
        enemy.velocity.y = -enemy.velocity.y;
    }

    enemy.position += enemy.velocity * dt;

    enemy.spriteRect.setPosition({enemy.position.x, enemy.position.y});
    enemy.spriteRect.setFillColor(enemy.color);
}

void EnemyDraw(sf::RenderWindow& window, Enemy enemy) {
    window.draw(enemy.spriteRect);
}

void CheckCollision(Player player, Enemy& enemy) {
    if (player.spriteRect.getGlobalBounds().findIntersection(enemy.spriteRect.getGlobalBounds())) {
        enemy.color = ENEMY_INTERSECTION_COLOR;
    } else {
        enemy.color = ENEMY_COLOR;
    }
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Toktaev"
    );

    sf::Clock clock;
    Player player;
    Enemy enemy;
    
    PlayerInit(player);
    EnemyInit(enemy);

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }     
        }

        PlayerUpdate(player, dt);
        EnemyUpdate(enemy, dt);
        CheckCollision(player, enemy);

        window.clear(sf::Color::Blue);

        PlayerDraw(window, player);
        EnemyDraw(window, enemy);

        window.display();
    }

    return 0;
}