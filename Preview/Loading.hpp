/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Loading
*/

#ifndef LOADING_HPP_
    #define LOADING_HPP_

    #include "../Maths/Vector3D.hpp"
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>

    class Loading {

        public:

            Loading(double width, double height);

            ~Loading();

            void addPixel(Math::Color color, double x, double y, int samples);

        private:
            double _width;
            double _height;
            sf::RenderWindow win;
            std::unique_ptr<sf::Uint8[]> pixels;
            sf::Texture texture;
            sf::Sprite sprite;
    };

#endif /* !PREVIEW_HPP_ */