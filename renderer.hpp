
#pragma once
#include "grid.hpp"

struct Renderer {

    sf::RenderTarget& target;

    explicit
    Renderer(sf::RenderTarget& target_)
    : target {target_}
    {}

    void render(const Game& game) {

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
    }

};