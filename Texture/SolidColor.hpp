/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** SolidColor
*/

#ifndef SOLIDCOLOR_HPP_
    #define SOLIDCOLOR_HPP_

    #include "ITexture.hpp"

    namespace raytracer {
        class SolidColor : public ITexture {
            public:
                SolidColor() {}
                SolidColor(Math::Color c): color_value(c) {}

                SolidColor(double red, double green, double blue): SolidColor(Math::Color(red, green, blue)) {}

                virtual Math::Color value(UNUSED double u, UNUSED double v, UNUSED const Math::Vector3D &p) const override
                {
                    return color_value;
                }

            protected:
            private:
                Math::Color color_value;
        };
    }

#endif /* !SOLIDCOLOR_HPP_ */
