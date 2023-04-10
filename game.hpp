
#pragma once
#include "grid.hpp"
#include "gen.hpp"

struct Game {

    Grid& grid;
    BombGenerator& generator;
    std::vector<sf::Vector2f> flags;
    std::vector<sf::Vector2f> uncovered;
    bool bombed = false;

    Game(Grid& grid_, BombGenerator& generator_)
    : grid {grid_}
    , generator {generator_}
    {}

    void flag(uint32_t x, uint32_t y) {
        sf::Vector2f nearestTile = grid.nearestTile(x, y);
        auto it = std::find(flags.begin(), flags.end(), nearestTile);
        if (it != flags.end()) {
            flags.erase(it);
        } else {
            flags.emplace_back(nearestTile.x, nearestTile.y);
        }
    }

    void uncover(uint32_t x, uint32_t y) {
        sf::Vector2f nearestTile = grid.nearestTile(x, y);
        if (std::find(flags.begin(), flags.end(), nearestTile) != flags.end()) {
            return;
        }
        auto it = std::find(generator.bomb_positions.begin(), generator.bomb_positions.end(),
                            grid.posToOrd(nearestTile));
        if (it != generator.bomb_positions.end()) {
            bombed = true;
            return;
        }
        if (std::find(uncovered.begin(), uncovered.end(), nearestTile) == uncovered.end()) {
            uncovered.emplace_back(nearestTile.x, nearestTile.y);
        }
        it = std::find(generator.empty_positions.begin(), generator.empty_positions.end(),
                            grid.posToOrd(nearestTile));
        if (it != generator.empty_positions.end()) {
            generator.empty_positions.erase(it);
            for (sf::Vector2u adjacent : grid.adjacentTiles(grid.posToOrd(nearestTile))) {
                if (std::find(uncovered.begin(), uncovered.end(), grid.ordToPos(adjacent)) == uncovered.end()) {
                    uncovered.emplace_back(grid.ordToPos(adjacent).x, grid.ordToPos(adjacent).y);
                    if (std::find(generator.empty_positions.begin(), generator.empty_positions.end(), adjacent) !=
                        generator.empty_positions.end()) {
                        uncover(static_cast<uint32_t>(grid.ordToPos(adjacent).x),
                                static_cast<uint32_t>(grid.ordToPos(adjacent).y));
                    }
                }
            }
        }
    }

    void generate() {
        grid.choosePositions();
        generator.generate();
        generator.naive_numbering();
    }

    void restart() {
        bombed = false;
        flags.clear();
        uncovered.clear();
        generator.clear();
        generator.generate();
        generator.naive_numbering();
    }

};