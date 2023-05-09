/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Preview
*/

#include "Preview.hpp"

Preview::Preview(double width, double height)
{
    win.create(sf::VideoMode(width, height), "Preview");
    pixels = std::vector<sf::RectangleShape>();
}

void Preview::addPixel(Math::Color color, double x, double y, int quality)
{
    if (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                win.close();
        }
        win.clear();
        sf::RectangleShape pixel(sf::Vector2f(quality, quality));
        pixel.setPosition(x, y);
        pixel.setFillColor(sf::Color(color.getX() * 255, color.getY() * 255, color.getZ() * 255));
        pixels.push_back(pixel);
        for (std::size_t i = 0; i < pixels.size(); i++)
            win.draw(pixels[i]);
        win.display();
    }
}

Preview::~Preview()
{
    win.close();
}
