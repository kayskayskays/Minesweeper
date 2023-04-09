#include <SFML/graphics.hpp>
#include <iostream>

int main() {

    constexpr uint32_t window_width = 1000;
    constexpr uint32_t window_height = 1000;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Minesweeper", sf::Style::Default, settings);
    const uint32_t frame_rate = 60;
    window.setFramerateLimit(frame_rate);

    while (window.isOpen()) {

        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            window.clear(sf::Color::White);
            window.display();
        }

    }
    return 0;
}
