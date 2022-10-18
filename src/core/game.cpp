#include "game.h"

CellType Game::at(std::uint8_t pos) const noexcept
{
    return _field[pos];
}

Game& Game::at(std::uint8_t pos, CellType type) noexcept
{
    _field[pos] = type;
    return *this;
}

CellType Game::winner() noexcept
{
    for (const auto &pattern : _win_patterns) {
        std::size_t i        = 0,
                    counter  = 0;
        CellType    std_cell = _field[pattern[i]];

        if (std_cell == CellType::Empty) {
            continue;
        }

        for (; i < pattern.size(); i++) {
            counter += (_field[pattern[i]] == std_cell);
        }

        if (counter % pattern.size() == 0) {
            return std_cell;
        }
    }
    return CellType::Empty;
}

ttt_field_t& Game::field() noexcept {
    return _field;
}
