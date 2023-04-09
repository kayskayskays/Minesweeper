
#pragma once
#include <cmath>

struct Grid {

    uint32_t window_width = 1000;
    uint32_t window_height = 1000;

    uint32_t dim_x = 9;
    uint32_t dim_y = 9;

    std::vector<sf::Vector2f> grid_positions;

    explicit
    Grid(uint32_t window_width_, uint32_t window_height_ = 1000, uint32_t dim_x_ = 9, uint32_t dim_y_ = 9)
    : window_width {window_width_}
    , window_height {window_height_}
    , dim_x {dim_x_}
    , dim_y {dim_y_}
    {}
    Grid() = default;

    void choosePositions() {

        float x;
        float y;

        for (uint32_t i{dim_x}; i--;) {
            for (uint32_t j{dim_y}; j--;) {
                // padding of 1/10 window size on top and bottom
                x = static_cast<float>(window_width) / 10 + 4 * static_cast<float>(i) *
                        static_cast<float>(window_width) / (5 * static_cast<float>(dim_x - 1));
                y = static_cast<float>(window_height) / 10 + 4 * static_cast<float>(j) *
                        static_cast<float>(window_height) / (5 * static_cast<float>(dim_y - 1));
                grid_positions.emplace_back(x, y);
            }
        }
    }

    sf::Vector2u posToOrd(sf::Vector2f position) {
        uint32_t x = 1;
        uint32_t y = 1;

        auto it = std::find(grid_positions.begin(), grid_positions.end(), position);
        uint32_t index = it - grid_positions.begin();
        index = -index + grid_positions.size();
        if (index % dim_y == 0) {
            y = index / dim_y;
        } else {
            y = index / dim_y + 1;
        }
        x = index - (y - 1) * dim_y;
        return {x, y};
    }

    sf::Vector2f ordToPos(sf::Vector2u coordinate) {
        uint32_t index = grid_positions.size() - 1;
        index -= dim_x * (coordinate.y - 1);
        index -= coordinate.x - 1;
        return grid_positions[index];
    }

    sf::Vector2f nearestCell(uint32_t x, uint32_t y) {

        float dist;
        float min_dist = -1;
        sf::Vector2f nearest;

        for (sf::Vector2f position : grid_positions) {
            dist = sqrtf((static_cast<float>(x) - position.x) * (static_cast<float>(x) - position.x) +
                    (static_cast<float>(y) - position.y) * (static_cast<float>(y) - position.y));
            if (min_dist == -1 || min_dist > dist) {
                min_dist = dist;
                nearest = position;
            }
        }
        return nearest;
    }

    [[nodiscard]]
    float deltaX() const {
        return grid_positions[0].x - grid_positions[dim_y].x;
    }

    [[nodiscard]]
    float deltaY() const {
        return grid_positions[0].y - grid_positions[1].y;
    }

    static std::vector<sf::Vector2u> adjacentTiles(sf::Vector2u tile) {
        std::vector<sf::Vector2u> adjacent;
        if (tile.y + 1 <= 9)
            adjacent.emplace_back(tile.x, tile.y + 1);
        if (tile.y - 1 > 0)
            adjacent.emplace_back(tile.x, tile.y - 1);
        if (tile.x + 1 <= 9) {
            adjacent.emplace_back(tile.x + 1, tile.y);
            if (tile.y + 1 <= 9)
                adjacent.emplace_back(tile.x + 1, tile.y + 1);
            if (tile.y - 1 > 0)
                adjacent.emplace_back(tile.x + 1, tile.y - 1);
        }
        if (tile.x - 1 > 0) {
            adjacent.emplace_back(tile.x - 1, tile.y);
            if (tile.y + 1 <= 9)
                adjacent.emplace_back(tile.x - 1, tile.y + 1);
            if (tile.y - 1 > 0)
                adjacent.emplace_back(tile.x - 1, tile.y - 1);
        }
        return adjacent;
    }

};