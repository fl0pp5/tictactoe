#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>

#include "types.h"


class Player
{
    std::uint8_t _pos;
    CellType     _cell;
public:
    Player(std::uint8_t pos, CellType cell)
            : _pos(pos), _cell(cell) {}

    Player(Player&& other) = default;

    std::uint8_t pos() const noexcept;
    Player& set_pos(std::uint8_t pos) noexcept;
    CellType cell() const noexcept;

    Player(const Player& _) = delete;
    Player& operator=(const Player& _) = delete;
    Player& operator=(Player&& _) = delete;
};


#endif //PLAYER_H
