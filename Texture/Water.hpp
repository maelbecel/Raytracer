/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Water
*/

#ifndef WATER_HPP_
    #define WATER_HPP_

    #include "ITexture.hpp"
    #include "Perlin.hpp"

    namespace raytracer {
        class Water : public ITexture {
            public:
                Water(double waves, Math::Color color) : _waves(waves), _color(color), _perlin() {}
                Water(Water &other) {
                    _waves = other._waves;
                    _color = other._color;
                    _perlin = other._perlin;
                }

                virtual Math::Color value(UNUSED double u, UNUSED double v, const Math::Vector3D& p) const override
                {
                    return _color * 0.5 * (1 + sin(_waves * p.getZ() + 10 * _perlin.turb(p)));
                }

            protected:
            private:
                double _waves;
                Math::Color _color;
                Perlin _perlin;
        };
    }

#endif /* !WATER_HPP_ */
