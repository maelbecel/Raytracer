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

            void addPixel(Math::Color color, double x, double y, int quality);

            sf::RenderWindow win;

        private:
            std::vector<sf::RectangleShape> pixels;
    };

#endif /* !PREVIEW_HPP_ */