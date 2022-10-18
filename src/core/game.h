#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <array>

enum class CellType
{
    Empty, Cross, Zero
};

typedef std::array<CellType, 3> ttt_field_t;

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

    ttt_field_t _field{};

public:
    Game() = default;

    Game& at(std::uint8_t pos, CellType type) noexcept;
    CellType at(std::uint8_t pos) const noexcept;
    CellType winner() noexcept;
    ttt_field_t& field() noexcept;

    Game(const Game& _) = delete;
    Game(Game&& _) = delete;
    Game& operator=(const Game& _) = delete;
    Game& operator=(Game&& _) = delete;
};



#endif //GAME_H
