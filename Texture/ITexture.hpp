/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** ITexture
*/

#ifndef ITEXTURE_HPP_
    #define ITEXTURE_HPP_

    #include "../Maths/Vector3D.hpp"

    #define UNUSED __attribute__((unused))

    namespace raytracer {
        class ITexture {
            public:
                virtual ~ITexture() = default;
                virtual Math::Color value(double u, double v, const Math::Vector3D& p) const = 0;

            protected:
            private:
        };
    }

#endif /* !ITEXTURE_HPP_ */
