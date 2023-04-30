/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Dielectric
*/

#ifndef DIELECTRIC_HPP_
    #define DIELECTRIC_HPP_

    #include "IMaterial.hpp"

    namespace raytracer {
        class Dielectric : public IMaterial{
            public:
                Dielectric(double index) : _index(index) {};

                virtual bool scatter(const Ray& r_in, const HitRecord& rec, Math::Color& attenuation, Ray& scattered) const override
                {
                    attenuation = Math::Color(1.0, 1.0, 1.0);
                    double refraction_ratio = rec.isFrontFace() ? (1.0 / _index) : _index;
                    Math::Vector3D unit_direction = r_in.Direction.unit_vector();
                    double cos_theta = fmin((-unit_direction).dot(rec.getNormal()), 1.0);
                    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
                    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
                    Math::Vector3D direction;
                    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
                        direction = Math::Vector3D::reflect(unit_direction, rec.getNormal());
                    else
                        direction = Math::Vector3D::refract(unit_direction, rec.getNormal(), refraction_ratio);
                    scattered = Ray(rec.getP(), direction, r_in.time());
                    return true;
                }

                virtual Math::Color emitted(UNUSED double u, UNUSED double v, UNUSED const Math::Vector3D &p) const override
                {
                    return Math::Color(0, 0, 0);
                }

            protected:
            private:
                double _index;
                static double reflectance(double cos, double ref)
                {
                    auto r = (1 - ref) / (1 + ref);
                    r = r * r;
                    return r + (1 - r) * pow((1 - cos), 5);
                }
        };
    }

#endif /* !DIELECTRIC_HPP_ */

