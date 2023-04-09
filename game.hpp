
#pragma once
#include "grid.hpp"
#include "gen.hpp"

struct Game {

    Grid& grid;
    BombGenerator& generator;

    Game(Grid& grid_, BombGenerator& generator_)
    : grid {grid_}
    , generator {generator_}
    {}

    void generate() {
        grid.choosePositions();
        generator.generate();
    }

};