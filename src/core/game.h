#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <array>

#include "player.h"
#include "types.h"

class Game
{;
public:
    Game() = default;

    Game& at(std::uint8_t pos, CellType type) noexcept;
    CellType at(std::uint8_t pos) const noexcept;
    CellType winner() noexcept;
    Game& fill() noexcept;
    Player& player1() noexcept;
    Player& player2() noexcept;
    ttt_field_t::size_type field_size() const noexcept;
    const Player* current() const noexcept;
    std::uint8_t compute_pos(const Player& player, int cur_pos, int shift) const noexcept;
    std::uint8_t height() const noexcept;
    std::uint8_t width() const noexcept;

    Game(const Game& _) = delete;
    Game(Game&& _) = delete;
    Game& operator=(const Game& _) = delete;
    Game& operator=(Game&& _) = delete;

private:
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

    typedef std::array<Player, 2> _players_t;

    _players_t _players {
        Player(0, CellType::Cross),
        Player(1, CellType::Zero)
    };
    _players_t::iterator _current {_players.begin()};
};



#endif //GAME_H
