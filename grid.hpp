
#pragma once

struct Grid {

    uint32_t window_width = 1000;
    uint32_t window_height = 1000;
    uint32_t dim_x = 9;
    uint32_t dim_y = 9;

    std::vector<sf::Vector2f> grid_positions;

    Grid() = default;
    Grid(uint32_t window_width_, uint32_t window_height_ = 1000, uint32_t dim_x_ = 9, uint32_t dim_y_ = 9)
    : window_width {window_width_}
    , window_height {window_height_}
    , dim_x {dim_x_}
    , dim_y {dim_y_}
    {}

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

};