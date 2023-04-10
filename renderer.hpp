
#pragma once
#include <iostream>
#include <utility>
#include "grid.hpp"

struct Renderer {

    sf::RenderTarget& target;
    sf::Font font;
    sf::Text text;
    std::vector<std::pair<uint32_t, sf::Color>> color_map;
    float text_width = 0, text_height = 0;

    explicit
    Renderer(sf::RenderTarget& target_)
    : target {target_}{
        color_map = {{1, sf::Color{1, 0, 240}},
                     {2, sf::Color{4, 126, 0}},
                     {3, sf::Color{254, 0, 0}},
                     {4, sf::Color{1, 1, 128}},
                     {5, sf::Color{129, 1, 1}},
                     {6, sf::Color{0, 128, 128}},
                     {7, sf::Color{0, 0, 0}},
                     {8, sf::Color{128, 128, 128}}};
        text.setFont(font);
    }

    void render(const Game& game) {

        if (!font.loadFromFile("avenir.ttf")) {
            std::cout << "Font error" << std::endl;
            return;
        }

        text.setCharacterSize(static_cast<uint32_t>(game.grid.deltaX() / 2));
        text.setString('0');
        text_width = text.getGlobalBounds().width;

        for (sf::Vector2f position: game.grid.grid_positions) {
            sf::RectangleShape square(sf::Vector2f(game.grid.deltaX(), game.grid.deltaY())); // fix this
            square.setOutlineColor(sf::Color{96, 96, 96});
            square.setOutlineThickness(5.0f);
            square.setPosition(position - 0.5f * square.getSize());
            square.setFillColor(sf::Color{154, 154, 154});
            target.draw(square);
        }

        for (sf::Vector2f click: game.uncovered) {
            sf::RectangleShape square(sf::Vector2f(game.grid.deltaX() - 5.0f, game.grid.deltaY() - 5.0f)); // fix this
            square.setPosition(click - 0.5f * square.getSize());
            square.setOutlineColor(sf::Color{96, 96, 96});
            square.setOutlineThickness(5.0f);
            square.setFillColor(sf::Color{121, 121, 121});
            target.draw(square);
            auto it = std::find(game.generator.safe_positions.begin(), game.generator.safe_positions.end(),
                                game.grid.posToOrd(click));
            if (it != game.generator.safe_positions.end()) {
                uint32_t index = it - game.generator.safe_positions.begin();
                drawInt(game, game.generator.num_positions[index]);
            }
        }

        for (sf::Vector2f click: game.flags) {
            sf::CircleShape triangle(1.0f, 3);
            triangle.rotate(90);
            triangle.setOrigin(1.0f, 1.0f);
            triangle.setOutlineColor(sf::Color::Yellow);
            triangle.setOutlineThickness(0.1f);
            triangle.setFillColor(sf::Color::Red);
            triangle.scale(game.grid.deltaX() / 4, game.grid.deltaY() / 4);
            triangle.setPosition(click.x, click.y);
            if (std::find(game.uncovered.begin(), game.uncovered.end(), click) == game.uncovered.end()) {
                target.draw(triangle);
            }
        }

        if (game.bombed) {
            for (sf::Vector2u bomb: game.generator.bomb_positions) {
                sf::CircleShape circle(1.0f);
                circle.setOrigin(1.0f, 1.0f);
                circle.setOutlineColor(sf::Color::Red);
                circle.setOutlineThickness(0.1f);
                circle.setFillColor(sf::Color{38, 38, 38});
                circle.scale(game.grid.deltaX() / 3, game.grid.deltaY() / 3);
                circle.setPosition(game.grid.ordToPos(bomb));
                if (std::find(game.flags.begin(), game.flags.end(), game.grid.ordToPos(bomb)) == game.flags.end()) {
                    target.draw(circle);
                }
            }
        }
    }

    void drawInt(const Game& game, sf::Vector3u num) {
        text.setFillColor(color_map[num.z - 1].second);
        text.setString(std::to_string(num.z));
        text_height = text.getGlobalBounds().height;
        text.setPosition(game.grid.ordToPos(sf::Vector2u{num.x, num.y}) - sf::Vector2f{text_width / 2,
                                                                                       3 * text_height / 4 });
        target.draw(text);
    }

};