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
    #include "../Scene.hpp"

    namespace raytracer {
        class HittablePDF : public IDensity {
            public:
                HittablePDF( std::shared_ptr<raytracer::IShape> p, const Math::Vector3D &o) : ptr(p), sptr(nullptr), origin(o) {}
                HittablePDF( std::shared_ptr<raytracer::Scene> p, const Math::Vector3D &o) : ptr(nullptr), sptr(p), origin(o) {}

                virtual double value(const Math::Vector3D &d) const override
                {
                    if (ptr)
                        return ptr->densityValue(origin, d);
                    return sptr->densityValue(origin, d);
                }

                virtual Math::Vector3D generate() const override
                {
                    if (ptr)
                        return ptr->random(origin);
                    return sptr->random(origin);
                }

                operator std::shared_ptr<IDensity>() const {
                    return std::make_shared<HittablePDF>(*this);
                }

            protected:
            private:
                std::shared_ptr<raytracer::IShape> ptr;
                std::shared_ptr<raytracer::Scene> sptr;
                Math::Vector3D origin;

        };
    }

#endif /* !HITTABLEPDF_HPP_ */
