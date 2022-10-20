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
        CellType    std_cell = at(pattern[i]);

        if (std_cell == CellType::Empty) {
            continue;
        }

        for (; i < pattern.size(); i++) {
            counter += (at(pattern[i]) == std_cell);
        }

        if (counter % pattern.size() == 0) {
            return std_cell;
        }
    }
    return CellType::Empty;
}

ttt_field_t& Game::field() noexcept
{
    return _field;
}

Game& Game::move(std::uint8_t pos) noexcept
{
    _current->set_pos(pos);

    return *this;
}

Game& Game::fill() noexcept
{
    if (at(_current->pos()) != CellType::Empty) {
        return *this;
    }

    at(_current->pos(),
       _current->cell());

    _current != _players.begin() ?
        _current = _players.begin() : _current = _players.end() - 1;

    return *this;
}

