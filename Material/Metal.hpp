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

                virtual bool scatter(const Ray& r_in, const HitRecord& rec, Math::Color& albedo, Ray& scattered, UNUSED double &pdf) const override
                {
                    Math::Vector3D reflected = Math::Vector3D::reflect(r_in.Direction.unit_vector(), rec.getNormal());
                    scattered = Ray(rec.getP(), reflected + _fuzz * Math::Vector3D::random_in_unit_sphere(), r_in.time());
                    albedo = _albedo;
                    return (scattered.Direction.dot(rec.getNormal()) > 0);
                }

                virtual double scatter_pdf(UNUSED const Ray& r_in, UNUSED const HitRecord& rec, UNUSED const Ray& scattered) const {return 0;};

                virtual Math::Color emitted(UNUSED double u,UNUSED  double v, UNUSED const HitRecord& rec, UNUSED const Math::Vector3D &p) const override
                {
                    return Math::Color(0, 0, 0);
                }

            protected:
            private:
                Math::Color _albedo;
                double _fuzz;
        };
    }

#endif /* !METAL_HPP_ */
