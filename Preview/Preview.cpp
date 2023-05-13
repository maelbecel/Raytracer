/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Preview
*/

#include "Preview.hpp"

Preview::Preview(double width, double height)
{
    _width = width;
    _height = height;
    accept = false;
    win.create(sf::VideoMode(_width, _height), "Preview");
    pixels = std::make_unique<sf::Uint8[]>(width * height * 4);
    texture.create(width, height);
    sprite.setTexture(texture, true);
    
    buttons[1].setSize(sf::Vector2f(20,20));
    buttons[1].setPosition(width - buttons[1].getSize().x * 2, height - buttons[1].getSize().y * 2);
    buttons[1].setFillColor(sf::Color::Red);
    buttons[1].setOutlineColor(sf::Color::Black);
    buttons[1].setOutlineThickness(2);

    buttons[0].setSize(sf::Vector2f(20,20));
    buttons[0].setPosition(width - buttons[0].getSize().x * 2 - buttons[1].getSize().x * 2, height - buttons[0].getSize().y * 2);
    buttons[0].setFillColor(sf::Color::Green);
    buttons[0].setOutlineColor(sf::Color::Black);
    buttons[0].setOutlineThickness(2);
}

void Preview::addPixel(Math::Color color, double x, double y, int samples)
{
    auto r = color.getX();
    auto g = color.getY();
    auto b = color.getZ();

    r = ( r != r) ? 0 : r;
    g = ( g != g) ? 0 : g;
    b = ( b != b) ? 0 : b;

    auto scale = 1.0 / samples;
    r = CLAMP(sqrt(scale * r), 0.0, 0.999);
    g = CLAMP(sqrt(scale * g), 0.0, 0.999);
    b = CLAMP(sqrt(scale * b), 0.0, 0.999);

    int pos = (y - 1) * win.getSize().x * 4 + x * 4;
    if ((x > 0 && x < win.getSize().x) && (y > 0 && y < win.getSize().y)) {
        pixels[0 + pos] = r * 256;
        pixels[1 + pos] = g * 256;
        pixels[2 + pos] = b * 256;
        pixels[3 + pos] = 255;
    }
}

void Preview::display()
{
    texture.update(pixels.get());
    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                win.close();
        }
        win.clear();
        win.draw(sprite);
        if (buttons[0].getGlobalBounds().contains(sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y)) {
            buttons[0].setOutlineColor(sf::Color::White);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                buttons[0].setOutlineColor(sf::Color(133, 133, 133, 255));
                accept = true;
                win.close();
            }
        } else
            buttons[0].setOutlineColor(sf::Color::Black);
        win.draw(buttons[0]);
        if (buttons[1].getGlobalBounds().contains(sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y)) {
            buttons[1].setOutlineColor(sf::Color::White);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                buttons[1].setOutlineColor(sf::Color(133, 133, 133, 255));
                win.close();
            }
        } else
            buttons[1].setOutlineColor(sf::Color::Black);
        win.draw(buttons[1]);
        win.display();
    }
}

Preview::~Preview()
{
    win.close();
}
