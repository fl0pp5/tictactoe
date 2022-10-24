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

Player& Game::player1() noexcept
{
    return *_players.begin();
}

Player& Game::player2() noexcept
{
    return *(_players.end() - 1);
}

ttt_field_t::size_type Game::field_size() const noexcept
{
    return _field.size();
}

const Player* Game::current() const noexcept {
    return _current;
}

std::uint8_t Game::compute_pos(const Player &player, int cur_pos, int shift) const noexcept
{
    return abs(cur_pos + shift) % field_size();
}

std::uint8_t Game::height() const noexcept
{
    return field_size() / 3;
}


std::uint8_t Game::width() const noexcept
{
    return field_size() / 3;
}

