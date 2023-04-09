
#include <SFML/graphics.hpp>
#include <iostream>
#include "renderer.hpp"
#include "grid.hpp"

int main() {

    constexpr uint32_t window_width = 1000;
    constexpr uint32_t window_height = 1000;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Minesweeper", sf::Style::Default, settings);
    const uint32_t frame_rate = 60;
    window.setFramerateLimit(frame_rate);

    Grid grid(window_width, window_height, 9, 9);
    // need to add support for when dim_x != dim_y
    grid.choosePositions();

    Renderer renderer{window};

    while (window.isOpen()) {

        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        renderer.render(grid);
        window.display();
    }

    return 0;
}
