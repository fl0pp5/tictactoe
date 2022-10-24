#ifndef GUI_H
#define GUI_H

#include <functional>

#include <SFML/Graphics.hpp>

#include "core/controller.h"


class GUIController : public BaseController<sf::Event>
{
public:
    typedef std::vector<sf::RectangleShape> rect_vector_t;

    explicit GUIController(sf::RenderWindow& window, float cell_size, const std::string& font_path) noexcept;

    void draw() noexcept override;
    void logic() noexcept override;
    void move(sf::Event event) noexcept override;

    bool is_game_over() const noexcept;
    bool is_restart() const noexcept;

    void start() noexcept;

private:
    std::map<sf::Keyboard::Key, std::function<void()>> _keymap;

    rect_vector_t _rect_list;
    sf::RenderWindow& _window;
    sf::CircleShape _player_shape;
    sf::Text _text;
    sf::Font _font;
    bool _restart{};
    bool _game_over{};


    rect_vector_t _make_field(float cell_size) noexcept;
    void _init_move_key(sf::Keyboard::Key key, Player& player, int shift) noexcept;
    void _init_fill_key(sf::Keyboard::Key key, Player& player) noexcept;
    void _init_kb() noexcept;

    GUIController& _draw_player(const Player& player, sf::Color color, float radius) noexcept;
    GUIController& _draw_cross() noexcept;
    GUIController& _draw_zero() noexcept;
    GUIController& _draw_rects() noexcept;
    GUIController& _draw_text() noexcept;

    GUIController& _paint_cells() noexcept;
    GUIController& _win_analyze() noexcept;
};


#endif //GUI_H
