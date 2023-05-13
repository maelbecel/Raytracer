/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Preview
*/

#ifndef PREVIEW_HPP_
    #define PREVIEW_HPP_

    #include "../Maths/Vector3D.hpp"
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>

    class Preview {

        public:

            Preview(double width, double height);

            ~Preview();

            void addPixel(Math::Color color, double x, double y, int samples);
            void display();

            bool accept;

        private:
            double _width;
            double _height;
            sf::RenderWindow win;
            std::unique_ptr<sf::Uint8[]> pixels;
            sf::Texture texture;
            sf::Sprite sprite;
            sf::RectangleShape buttons[2];
    };

#endif /* !PREVIEW_HPP_ */