
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

        if(!font.loadFromFile("avenir.ttf")) {
            std::cout << "Font error" << std::endl;
            return;
        }

        for (sf::Vector2f position : game.grid.grid_positions) {
            sf::RectangleShape square(sf::Vector2f(game.grid.deltaX(), game.grid.deltaY())); // fix this
            square.setOutlineColor(sf::Color{96, 96, 96});
            square.setOutlineThickness(1.0f);
            square.setPosition(position - 0.5f * square.getSize());
            square.setFillColor(sf::Color{154, 154, 154});
            target.draw(square);
        }

        for (sf::Vector2u bomb : game.generator.bomb_positions) {
            sf::CircleShape circle(1.0f);
            circle.setOrigin(1.0f, 1.0f);
            circle.setOutlineColor(sf::Color::Red);
            circle.setOutlineThickness(0.1f);
            circle.scale(game.grid.deltaX() / 3, game.grid.deltaY() / 3);
            circle.setPosition(game.grid.ordToPos(bomb));
            circle.setFillColor(sf::Color{38, 38, 38});
            target.draw(circle);
        }

        for (sf::Vector3u num : game.generator.num_positions) {
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
    }

};