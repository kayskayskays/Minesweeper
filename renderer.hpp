
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

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(static_cast<uint32_t>(game.grid.deltaX() / 4));
        text.setFillColor(sf::Color::White);

        for (sf::Vector2f position : game.grid.grid_positions) {
            sf::RectangleShape square(sf::Vector2f(game.grid.deltaX(), game.grid.deltaY())); // fix this
            square.setOutlineColor(sf::Color::Blue);
            square.setOutlineThickness(5.0f);
            square.setPosition(position - (0.5f * square.getSize()));
            square.setFillColor(sf::Color::Magenta);
            target.draw(square);
        }

        for (sf::Vector2u bomb : game.generator.bomb_positions) {
            sf::CircleShape circle(game.grid.deltaX() / 3);
            circle.setOutlineColor(sf::Color::Black);
            circle.setOutlineThickness(3.0f);
            circle.setPosition(game.grid.ordToPos(bomb) - sf::Vector2f{game.grid.deltaX() / 3, game.grid.deltaY() / 3});
            circle.setFillColor(sf::Color::Green);
            target.draw(circle);
        }

        for (sf::Vector3u num : game.generator.num_positions) {
            text.setString(std::to_string(num.z));
            text.setPosition(game.grid.ordToPos(sf::Vector2u{num.x, num.y}));
            target.draw(text);
        }
    }

};