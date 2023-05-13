/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Loading
*/

#include "Loading.hpp"

Loading::Loading(double width, double height)
{
    _width = width;
    _height = height;
    win.create(sf::VideoMode(_width, _height), "Loading");
    pixels = std::make_unique<sf::Uint8[]>(width * height * 4);
    texture.create(width, height);
    sprite.setTexture(texture, true);
}

void Loading::addPixel(Math::Color color, double x, double y, int samples)
{
    if (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                win.close();
        }
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
        texture.update(pixels.get());
        win.clear();
        win.draw(sprite);
        win.display();
    }
}

Loading::~Loading()
{
    win.close();
}
