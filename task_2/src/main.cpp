#include <SFML/Graphics.hpp>

const sf::Color Gray(128, 128, 128);
const sf::Color Black(0, 0, 0);

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Toktaev"
    );

    sf::Color currentColor = Black;

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
                    if (currentColor == Black) {
                        currentColor = Gray;
                    } else {
                        currentColor = Black;
                    }
                }
            }
                
        }

        window.clear(currentColor);
        window.display();
    }

    return 0;
}