#include "player.h"

std::uint8_t Player::pos() const noexcept {
    return _pos;
}

Player& Player::set_pos(std::uint8_t pos) noexcept {
    _pos = pos;
    return *this;
}

CellType Player::cell() const noexcept {
    return _cell;
}
