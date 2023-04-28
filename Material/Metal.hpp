/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Metal
*/

#ifndef METAL_HPP_
    #define METAL_HPP_

    #include "IMaterial.hpp"

    namespace raytracer {
        class Metal : public IMaterial {
            public:
                Metal(const Math::Color &albedo, double fuzz) : _albedo(albedo), _fuzz(fuzz) {};
                ~Metal() = default;

                virtual bool scatter(const Ray& r_in, const HitRecord& rec, Math::Color& attenuation, Ray& scattered) const override
                {
                    Math::Vector3D reflected = Math::Vector3D::reflect(r_in.Direction.unit_vector(), rec.getNormal());
                    scattered = Ray(rec.getP(), reflected + _fuzz * Math::Vector3D::random_in_unit_sphere());
                    attenuation = _albedo;
                    return (scattered.Direction.dot(rec.getNormal()) > 0);
                }

            protected:
            private:
                Math::Color _albedo;
                double _fuzz;
        };
    }

#endif /* !METAL_HPP_ */
