/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Lambertian
*/

#ifndef LAMBERTIAN_HPP_
    #define LAMBERTIAN_HPP_

    #include "IMaterial.hpp"
    #include "../Texture/ITexture.hpp"
    #include "../Texture/SolidColor.hpp"
    #include "../Object/Cosine.hpp"
    #include "../Maths/Orthonormal.hpp"

    namespace raytracer {
        class Lambertian : public IMaterial {
            public:
                Lambertian(const Math::Color &color) : albedo(std::make_shared<SolidColor>(color)) {};
                Lambertian(std::shared_ptr<ITexture> a) : albedo(a) {};

                virtual bool scatter(UNUSED const Ray& r_in, const HitRecord& rec, ScatterRecord &srec) const override
                {
                    srec.is_specular = false;
                    srec.attenuation = albedo->value(rec.u, rec.v, rec.getP());
                    srec.density_ptr = std::make_shared<Cosine>(rec.getNormal());
                    return true;
                }

                virtual double scatter_pdf(UNUSED const Ray& r_in, const HitRecord& rec, const Ray& scattered) const
                {
                    auto cosine = rec.getNormal().dot(scattered.Direction.unit_vector());
                    return cosine < 0 ? 0 : cosine / M_PI;
                }

                virtual Math::Color emitted(UNUSED const Ray &r_in, UNUSED double u, UNUSED double v, UNUSED const HitRecord& rec, UNUSED const Math::Vector3D &p) const override
                {
                    return Math::Color(0, 0, 0);
                }

            protected:
            private:
                std::shared_ptr<ITexture> albedo;

        };
    }

#endif /* !LAMBERTIAN_HPP_ */
