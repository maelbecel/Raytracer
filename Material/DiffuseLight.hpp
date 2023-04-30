/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** DiffuseLight
*/

#ifndef DIFFUSELIGHT_HPP_
    #define DIFFUSELIGHT_HPP_

    #include "IMaterial.hpp"
    #include "../Texture/ITexture.hpp"
    #include "../Texture/SolidColor.hpp"

    namespace raytracer {
        class DiffuseLight : public IMaterial {
            public:
                DiffuseLight(std::shared_ptr<ITexture> e) : emit(e) {}
                DiffuseLight(Math::Color c) : emit(std::make_shared<SolidColor>(c)) {}

                virtual Math::Color emitted(double u, double v, const Math::Vector3D &p) const override
                {
                    return emit->value(u, v, p);
                }

                virtual bool scatter(UNUSED const Ray& r_in, UNUSED const HitRecord& rec, UNUSED Math::Color& attenuation, UNUSED Ray& scattered) const override
                {
                    return false;
                }

            private:
                std::shared_ptr<ITexture> emit;
        };
    }

#endif /* !DIFFUSELIGHT_HPP_ */
