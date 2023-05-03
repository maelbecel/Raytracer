/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Cosine
*/

#ifndef COSINE_HPP_
    #define COSINE_HPP_

    #include "../Maths/Orthonormal.hpp"
    #include "IDensity.hpp"

    namespace raytracer {
        class Cosine : public IDensity {
            public:
                Cosine(const Math::Vector3D& w)
                {
                    uvw.build_from_w(w);
                }

                virtual double value(const Math::Vector3D &direction) const override
                {
                    auto cosine = direction.unit_vector().dot(uvw.w());
                    return cosine <= 0 ? 0 : cosine / M_PI;
                }

                virtual Math::Vector3D generate() const override
                {
                    return uvw.local(Math::Orthonormal::random_cosine_direction());
                }

            protected:
            private:
                Math::Orthonormal uvw;

        };
    }

#endif /* !COSINE_HPP_ */
