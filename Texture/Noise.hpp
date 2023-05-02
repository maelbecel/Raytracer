/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Noise
*/

#ifndef NOISE_HPP_
    #define NOISE_HPP_

    #include "ITexture.hpp"
    #include "Perlin.hpp"

    namespace raytracer
    {
        class Noise : public ITexture {
            public:
                Noise() {};
                Noise(double s) : scale(s) {}

                virtual Math::Color value(UNUSED double u , UNUSED double v, const Math::Vector3D &p ) const override {
                    return Math::Color(1, 1, 1) * 0.5 * (1 + sin(scale * p.getZ() + 10 * noise.turb(p)));
                }

            protected:
            private:
                Perlin noise;
                double scale;
        };
    }

#endif /* !NOISE_HPP_ */
