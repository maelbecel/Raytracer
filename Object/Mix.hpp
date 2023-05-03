/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Mix
*/

#ifndef MIX_HPP_
    #define MIX_HPP_

    #include "IDensity.hpp"
    #include <memory>

    namespace raytracer {
        class Mix : public IDensity {
            public:
                Mix(std::shared_ptr<IDensity> p0, std::shared_ptr<IDensity> p1)
                {
                    p[0] = p0;
                    p[1] = p1;
                }

                virtual double value(const Math::Vector3D &direction) const override
                {
                    return 0.5 * p[0]->value(direction) + 0.5 * p[1]->value(direction);
                }

                virtual Math::Vector3D generate() const override
                {
                    if (random_double() < 0.5)
                        return p[0]->generate();
                    return p[1]->generate();
                }

            private:
                std::shared_ptr<IDensity> p[2];
        };
    }

#endif /* !MIX_HPP_ */
