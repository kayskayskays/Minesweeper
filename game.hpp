
#pragma once
#include "grid.hpp"
#include "gen.hpp"

struct Game {

    Grid& grid;
    BombGenerator& generator;
    std::vector<sf::Vector2f> flags;

    Game(Grid& grid_, BombGenerator& generator_)
    : grid {grid_}
    , generator {generator_}
    {}

    void flag(sf::Event::MouseButtonEvent click) {
        sf::Vector2f nearestCell = grid.nearestCell(click.x, click.y);
        auto it = std::find(flags.begin(), flags.end(), nearestCell);
        if (it != flags.end()) {
            flags.erase(it);
        } else {
            flags.emplace_back(nearestCell.x, nearestCell.y);
        }
    }

    void generate() {
        grid.choosePositions();
        generator.generate();
        generator.naive_numbering();
    }

};