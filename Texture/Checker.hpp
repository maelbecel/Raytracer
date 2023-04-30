/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Checker
*/

#ifndef CHECKER_HPP_
    #define CHECKER_HPP_

    #include "ITexture.hpp"
    #include "SolidColor.hpp"
    #include <memory>

    namespace raytracer {
        class Checker : public ITexture {
            public:
                Checker() {};
                Checker(std::shared_ptr<ITexture> t0, std::shared_ptr<ITexture> t1): even(t0), odd(t1) {}
                Checker(Math::Color c1, Math::Color c2): even(std::make_shared<SolidColor>(c1)), odd(std::make_shared<SolidColor>(c2)) {}


                virtual Math::Color value(double u, double v, const Math::Vector3D &p) const override {
                    auto sines = sin(10 * p.getX()) * sin(10 * p.getY()) * sin(10 * p.getZ());
                    if (sines < 0)
                        return odd->value(u, v, p);
                    else
                        return even->value(u, v, p);
                }

            public:
                std::shared_ptr<ITexture> even;
                std::shared_ptr<ITexture> odd;
        };
    }

#endif /* !CHECKER_HPP_ */
