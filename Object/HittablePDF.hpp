/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** HittablePDF
*/

#ifndef HITTABLEPDF_HPP_
    #define HITTABLEPDF_HPP_

    #include "IDensity.hpp"
    #include "../Maths/Vector3D.hpp"
    #include "../Shapes/IShape.hpp"

    namespace raytracer {
        class HittablePDF : public IDensity {
            public:
                HittablePDF( std::shared_ptr<IShape> p, const Math::Vector3D &o) : ptr(p), origin(o) {}

                virtual double value(const Math::Vector3D &d) const override
                {
                    return ptr->densityValue(origin, d);
                }

                virtual Math::Vector3D generate() const override
                {
                    return ptr->random(origin);
                }

            protected:
            private:
                std::shared_ptr<IShape> ptr;
                Math::Vector3D origin;

        };
    }

#endif /* !HITTABLEPDF_HPP_ */
