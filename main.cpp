

#include <SFML/Graphics.hpp>

#include "src/gui.h"

int main()
{
    GUIController* controller = nullptr;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    do {
        delete controller;

        sf::RenderWindow window(sf::VideoMode(420, 420),
                                "TIC-TAC-TOE", sf::Style::Default, settings);

        controller = new GUIController(window, window.getSize().x / 3, "arial.ttf");
        controller->start();
    } while (controller->is_restart());
    return 0;
}