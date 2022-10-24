#include <cassert>
#include <cmath>

#include "gui.h"

GUIController::GUIController(sf::RenderWindow& window, float cell_size, const std::string& font_path) noexcept
    : _window(window), _rect_list(_make_field(cell_size))
{
    _init_kb();
    assert(_font.loadFromFile(font_path) && "font loading error");

    _text.setFont(_font);
    _text.setStyle(sf::Text::Bold);
    _text.setFillColor(sf::Color::Red);
    _text.setCharacterSize(12);
    _text.setPosition(0, 0);
}

void
GUIController::draw() noexcept
{
    _draw_rects().
        _draw_cross().
        _draw_zero().
        _draw_player(game.player1(), sf::Color(255, 162, 0), 25).
        _draw_player(game.player2(), sf::Color(146, 103, 153), 25).
        _draw_text();
}

void
GUIController::logic() noexcept
{
    _paint_cells()._win_analyze();
}


void
GUIController::move(sf::Event event) noexcept
{
    size_t n = _keymap.count(event.key.code);
    if (n == 1) {
        if (sf::Keyboard::isKeyPressed(event.key.code)) {
            _keymap[event.key.code]();
        }
    }
}

void
GUIController::start() noexcept
{

    while (_window.isOpen())
    {
        logic();
        sf::Event event{};
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
            else
                move(event);
        }
        _window.clear();
        draw();
        _window.display();
    }

}

GUIController::rect_vector_t
GUIController::_make_field(float cell_size) noexcept
{
    GUIController::rect_vector_t tmp_rects(game.field_size());
    for (int i = 0; i < game.height(); i++) {
        for (int j = 0; j < game.width(); j++) {
            auto &current = tmp_rects[i + game.height() * j];
            current.setSize(sf::Vector2f(cell_size, cell_size));
            current.setPosition(current.getSize().x * (float) i,
                                current.getSize().y * (float) j);
        }
    }
    return tmp_rects;
}

void
GUIController::_init_move_key(sf::Keyboard::Key key, Player &player, int shift) noexcept
{
    _keymap.emplace(key, [&, shift]() {
        if (!is_game_over())
            player.set_pos(game.compute_pos(player, player.pos(), shift));
    });
}

void
GUIController::_init_fill_key(sf::Keyboard::Key key, Player &player) noexcept
{
    _keymap.emplace(key, [&] {
        if (!is_game_over() && game.current() == &player)
            game.fill();
    });
}

void
GUIController::_init_kb() noexcept
{
    int left_right = 1,
        up_down    = 3;

    _init_move_key(sf::Keyboard::A, game.player1(), -left_right);
    _init_move_key(sf::Keyboard::D, game.player1(), left_right);
    _init_move_key(sf::Keyboard::W, game.player1(), -up_down);
    _init_move_key(sf::Keyboard::S, game.player1(), up_down);
    _init_fill_key(sf::Keyboard::E, game.player1());

    _init_move_key(sf::Keyboard::J, game.player2(), -left_right);
    _init_move_key(sf::Keyboard::L, game.player2(), left_right);
    _init_move_key(sf::Keyboard::I, game.player2(), -up_down);
    _init_move_key(sf::Keyboard::K, game.player2(), up_down);
    _init_fill_key(sf::Keyboard::O, game.player2());

    _keymap.emplace(sf::Keyboard::Q, [&]() {
        _window.close();
    });

    _keymap.emplace(sf::Keyboard::R, [&]() {
        _window.close();
        _restart = true;
    });
}

GUIController&
GUIController::_paint_cells() noexcept
{
    for (int i = 0; i < game.field_size(); i++) {
        sf::Color color;
        switch (game.at(i)) {
            case CellType::Cross:
            case CellType::Zero:
            case CellType::Empty:
                color = sf::Color::White;
                break;
        }
        _rect_list[i].setOutlineThickness(5);
        _rect_list[i].setOutlineColor(sf::Color::Black);
        _rect_list[i].setFillColor(color);
    }
    return *this;
}


GUIController&
GUIController::_win_analyze() noexcept
{
    std::string message = "Press `R` to Restart\nPress `Q` to Quit";
    bool flag = false;

    switch (game.winner()) {
        case CellType::Cross:
            message = "Crosses win\n" + message;
            _game_over = true;
            break;
        case CellType::Zero:
            message = "Zeroes win\n" + message;
            _game_over = true;
            break;
        case CellType::Empty:
            break;
    }

    for (int i = 0; i < game.field_size(); i++) {
        if (game.at(i) == CellType::Empty)
            flag = true;
    }

    if (!flag && game.winner() == CellType::Empty) {
        message = "Draw\n" + message;
        _game_over = true;
    }

    _text.setString(message);
    if (_game_over) {
        _text.setCharacterSize(22);
        _text.setPosition((_window.getSize().x / 2) - _text.getLocalBounds().width / 2,
                          (_window.getSize().y / 2) - _text.getLocalBounds().height / 2);
    }

    return *this;
}

GUIController&
GUIController::_draw_player(const Player& player, sf::Color color, float radius) noexcept
{
    const auto& r = _rect_list[player.pos()];

    _player_shape.setRadius(radius);
    _player_shape.setPosition(r.getPosition().x + r.getSize().x / 2 - _player_shape.getRadius(),
                              r.getPosition().y + r.getSize().y / 2 - _player_shape.getRadius());
    _player_shape.setFillColor(color);
    _window.draw(_player_shape);

    return *this;
}

bool
GUIController::is_restart() const noexcept
{
    return _restart;
}

bool
GUIController::is_game_over() const noexcept
{
    return _game_over;
}

GUIController&
GUIController::_draw_cross() noexcept
{
    const float offset = 24;
    sf::RectangleShape line;
    line.setFillColor(sf::Color::Black);
    line.setSize(sf::Vector2f(
            hypotf(_rect_list[0].getSize().x, _rect_list[0].getSize().y) - offset*2, 4));


    for (int i = 0; i < game.field_size(); i++) {
        if (game.at(i) != CellType::Cross)
            continue;

        const auto& r = _rect_list[i];

        /* first diagonal */
        line.setPosition(r.getPosition().x + offset,
                         r.getPosition().y + offset);
        line.setRotation(45);
        _window.draw(line);

        /* second diagonal */
        line.setPosition(r.getPosition().x + r.getSize().x - offset,
                         r.getPosition().y + offset);
        line.setRotation(135);
        _window.draw(line);

    }
    return *this;
}

GUIController&
GUIController::_draw_rects() noexcept
{
    for (const auto& rect : _rect_list) {
        _window.draw(rect);
    }

    return *this;
}

GUIController&
GUIController::_draw_text() noexcept
{
    if (!_text.getString().isEmpty()) {
        _window.draw(_text);
    }
    return *this;
}

GUIController&
GUIController::_draw_zero() noexcept
{
    sf::CircleShape circle;
    circle.setRadius(_rect_list[0].getSize().x / 4);

    for (int i = 0; i < game.field_size(); i++)
    {
        if (game.at(i) != CellType::Zero)
            continue;

        const auto& r = _rect_list[i];

        circle.setPosition(r.getPosition().x + circle.getRadius(), r.getPosition().y + circle.getRadius());
        circle.setFillColor(sf::Color::White);
        circle.setOutlineThickness(6);
        circle.setOutlineColor(sf::Color::Black);

        _window.draw(circle);
    }

    return *this;
}

