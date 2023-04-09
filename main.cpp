
#include <SFML/graphics.hpp>
#include "game.hpp"
#include "renderer.hpp"

int main() {

    constexpr uint32_t window_width = 1000;
    constexpr uint32_t window_height = 1000;

    // might not be constexpr later on
    constexpr uint32_t dim_x = 9;
    constexpr uint32_t dim_y = 9;
    constexpr uint32_t bomb_count = 10;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Minesweeper", sf::Style::Default, settings);

    constexpr uint32_t frame_rate = 60;
    window.setFramerateLimit(frame_rate);

    Grid grid(window_width, window_height, dim_x, dim_y);
    // need to add support for when dim_x != dim_y
    BombGenerator generator(dim_x, dim_y, bomb_count);
    Game game(grid, generator);
    game.generate();

    Renderer renderer{window};

    while (window.isOpen()) {

        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        renderer.render(game);
        window.display();
    }

    return 0;
}
