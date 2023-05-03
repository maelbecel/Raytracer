/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Density
*/

#ifndef DENSITY_HPP_
    #define DENSITY_HPP_

    #include "../Maths/Vector3D.hpp"

    namespace raytracer {
        class IDensity {
            public:
                virtual ~IDensity() = default;
                virtual double value(const Math::Vector3D &direction) const = 0;
                virtual Math::Vector3D generate() const = 0;
            protected:
            private:
        };
    }

#endif /* !DENSITY_HPP_ */
