
#pragma once
#include <iostream>
#include "grid.hpp"

struct Renderer {

    sf::RenderTarget& target;
    sf::Font font;

    explicit
    Renderer(sf::RenderTarget& target_)
    : target {target_}
    {}

    void render(const Game& game) {

        if (!font.loadFromFile("avenir.ttf")) {
            std::cout << "Font error" << std::endl;
            return;
        }

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
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(static_cast<uint32_t>(game.grid.deltaX() / 4));
        text.setFillColor(sf::Color::White);
        text.setString(std::to_string(num.z));
        float height = text.getGlobalBounds().height;
        float width = text.getGlobalBounds().width;
        text.setPosition(game.grid.ordToPos(sf::Vector2u{num.x, num.y}) -
                         sf::Vector2f{width / 2, height / 2});
        text.setOutlineThickness(game.grid.deltaX() / 20);
        text.setOutlineColor(sf::Color::Black);
        target.draw(text);
    }

};