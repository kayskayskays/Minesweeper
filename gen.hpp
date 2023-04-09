
#pragma once
#include <random>
#include <algorithm>

namespace sf {
    typedef Vector3<uint32_t> Vector3u;
};

struct Rand {

    static uint32_t generate(uint32_t min, uint32_t max) {
        std::random_device rd;
        std::uniform_int_distribution<uint32_t> urd(min, max);
        return urd(rd);
    }

};

struct BombGenerator {

    uint32_t dim_x = 9;
    uint32_t dim_y = 9;
    uint32_t bomb_count = 10;

    std::vector<sf::Vector2u> bomb_positions;
    std::vector<sf::Vector3u> num_positions;
    std::vector<sf::Vector2u> empty_positions;

    explicit
    BombGenerator(uint32_t dim_x_, uint32_t dim_y_ = 9, uint32_t bomb_count_ = 10)
    : dim_x {dim_x_}
    , dim_y {dim_y_}
    , bomb_count {bomb_count_}
    {}
    BombGenerator() = default;

    void generate() {

        uint32_t x, y;

        for (uint32_t i{bomb_count}; i--;) {
            x = Rand::generate(1, dim_x);
            y = Rand::generate(1, dim_y);
            if (bomb_positions.empty() || std::find(bomb_positions.begin(),
                                                    bomb_positions.end(), sf::Vector2u{x, y}) == bomb_positions.end()) {
                bomb_positions.emplace_back(x, y);
            } else {
                i++;
            }
        }
    }

    [[nodiscard]]
    uint32_t adjacent_bombs(uint32_t x, uint32_t y) const {

        uint32_t count = 0;

        if (std::find(bomb_positions.begin(), bomb_positions.end(), sf::Vector2u{x, y + 1}) != bomb_positions.end()) {
            count += 1;
        }
        if (std::find(bomb_positions.begin(), bomb_positions.end(), sf::Vector2u{x, y - 1}) != bomb_positions.end()) {
            count += 1;
        }
        if (std::find(bomb_positions.begin(), bomb_positions.end(), sf::Vector2u{x + 1, y}) != bomb_positions.end()) {
            count += 1;
        }
        if (std::find(bomb_positions.begin(), bomb_positions.end(), sf::Vector2u{x + 1, y + 1}) != bomb_positions.end()) {
            count += 1;
        }
        if (std::find(bomb_positions.begin(), bomb_positions.end(), sf::Vector2u{x + 1, y - 1}) != bomb_positions.end()) {
            count += 1;
        }
        if (std::find(bomb_positions.begin(), bomb_positions.end(), sf::Vector2u{x - 1, y}) != bomb_positions.end()) {
            count += 1;
        }
        if (std::find(bomb_positions.begin(), bomb_positions.end(), sf::Vector2u{x - 1, y + 1}) != bomb_positions.end()) {
            count += 1;
        }
        if (std::find(bomb_positions.begin(), bomb_positions.end(), sf::Vector2u{x - 1, y - 1}) != bomb_positions.end()) {
            count += 1;
        }
        return count;
    }

    void naive_numbering() {

        uint32_t count = 0;

        for (uint32_t i{dim_x}; i > 0; i--) {
            for (uint32_t j{dim_y}; j > 0; j--) {

                if ((count = adjacent_bombs(i, j)) != 0 &&
                std::find(bomb_positions.begin(), bomb_positions.end(), sf::Vector2u{i, j}) == bomb_positions.end()) {
                    num_positions.emplace_back(i, j, count);
                } else if ((count = adjacent_bombs(i, j) == 0) &&
                std::find(bomb_positions.begin(), bomb_positions.end(), sf::Vector2u{i, j}) == bomb_positions.end()) {
                    empty_positions.emplace_back(i, j);
                }
            }
        }
    }
};