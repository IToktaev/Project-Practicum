#include <SFML/Graphics.hpp>

const sf::Color GRAY(128, 128, 128);
const sf::Color BLACK(0, 0, 0);

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Toktaev"
    );

    sf::Color currentColor = BLACK;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::KeyPressed>()) {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter) {
                    window.close();  
                }

                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space) {
                    if (currentColor == BLACK) {
                        currentColor = GRAY;
                    } else {
                        currentColor = BLACK;
                    }
                }
            }
                
        }

        window.clear(currentColor);
        window.display();
    }

    return 0;
}