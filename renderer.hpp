
#pragma once
#include "grid.hpp"

struct Renderer {

    sf::RenderTarget& target;

    explicit
    Renderer(sf::RenderTarget& target_)
    : target {target_}
    {}

    void render(const Grid& grid) {
        for (sf::Vector2f position : grid.grid_positions) {
            sf::RectangleShape square(sf::Vector2f(100, 100));
            square.setOutlineColor(sf::Color::Blue);
            square.setOutlineThickness(5.0f);
            square.setPosition(position - (0.5f * sf::Vector2f(square.getSize())));
            square.setFillColor(sf::Color::Magenta);
            target.draw(square);
        }
    }

};