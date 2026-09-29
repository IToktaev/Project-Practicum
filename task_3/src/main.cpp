#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Toktaev"
    );

    sf::RectangleShape houseWall({200.f, 200.f});
    houseWall.setPosition({300.f, 200.f});
    houseWall.setFillColor(sf::Color::Yellow);
    houseWall.setOutlineThickness(5.f);
    houseWall.setOutlineColor(sf::Color::Black);

    sf::CircleShape houseWindow(50.f);
    houseWindow.setPosition({350.f, 250.f});
    houseWindow.setFillColor(sf::Color::Blue);
    houseWindow.setOutlineThickness(5.f);
    houseWindow.setOutlineColor(sf::Color::Black);

    sf::ConvexShape houseRoof;
    houseRoof.setPointCount(3);
    houseRoof.setPoint(0, {0.f, 60.f});
    houseRoof.setPoint(1, {100.f, 0.f});
    houseRoof.setPoint(2, {200.f, 60.f});
    houseRoof.setPosition({300.f, 140.f});
    houseRoof.setFillColor(sf::Color::Red);
    houseRoof.setOutlineThickness(5.f);
    houseRoof.setOutlineColor(sf::Color::Black);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }      
        }

        window.clear(sf::Color::Blue);

        window.draw(houseWall);
        window.draw(houseRoof);
        window.draw(houseWindow);

        window.display();
    }

    return 0;
}