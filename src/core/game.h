#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <array>

#define FIELD_SIZE 9

enum class CellType
{
    Empty, Cross, Zero
};

class Game
{;
    /*
     * 0 1 2
     * 3 4 5
     * 6 7 8
     */
    std::array<
            std::array<int, 3>, 8> _win_patterns {{
                /* horizontal */
                {0, 1, 2},
                {3, 4, 5},
                {6, 7, 8},

                /* vertical */
                {0, 3, 6},
                {1, 4, 7},
                {2, 5, 8},

                /* diagonal */
                {0, 4, 8},
                {2, 4, 6}
            }};

    std::array<CellType, FIELD_SIZE> _field{};


public:
    Game() = default;

    Game& at(std::uint8_t pos, CellType type) noexcept;
    CellType at(std::uint8_t pos) const noexcept;
    CellType winner();

    Game(const Game& _) = delete;
    Game(Game&& _) = delete;
    Game& operator=(const Game& _) = delete;
    Game& operator=(Game&& _) = delete;
};



#endif //GAME_H
