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

                virtual Math::Color emitted(UNUSED const Ray &r_in, double u, double v, UNUSED const HitRecord& rec, const Math::Vector3D &p) const override
                {
                    if (rec.isFrontFace())
                        return emit->value(u, v, p);
                    else
                        return Math::Color(0,0,0);
                }

                virtual double scatter_pdf(UNUSED const Ray& r_in, UNUSED const HitRecord& rec, UNUSED const Ray& scattered) const {return 0;};

                virtual bool scatter(UNUSED const Ray& r_in, UNUSED const HitRecord& rec, UNUSED ScatterRecord &srec) const override
                {
                    return false;
                }

            private:
                std::shared_ptr<ITexture> emit;
        };
    }

#endif /* !DIFFUSELIGHT_HPP_ */
