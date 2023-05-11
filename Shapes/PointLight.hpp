/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** PointLight
*/

#ifndef POINTLIGHT_HPP_
    #define POINTLIGHT_HPP_

    #include "../Material/DiffuseLight.hpp"
    #include "IShape.hpp"

    namespace raytracer {
        class PointLight : public IShape {
            public:
                PointLight(Math::Vector3D p, Math::Color c) : _center(p), color(c) {}
                virtual bool hit(UNUSED const Ray &r, double min, double max, HitRecord &rec) const override
                {
                    double _radius = 0.1;
                    Math::Vector3D oc = r.Origin - _center;
                    double a = r.Direction.len_squared();
                    double half_b = oc.dot(r.Direction);
                    double c = oc.len_squared() - _radius * _radius;

                    double discriminant = half_b * half_b - a * c;
                    if (discriminant < 0)
                        return false;
                    double sqrtd = sqrt(discriminant);

                    double root = (-half_b - sqrtd) / a;
                    if (root < min || max < root) {
                        root = (-half_b + sqrtd) / a;
                        if (root < min || max < root)
                            return false;
                    }
                    rec.setT(root);
                    rec.setP(r.at(rec.getT()));
                    Math::Vector3D outward_normal = (rec.getP() - _center) / _radius;
                    rec.setFaceNormal(r, outward_normal);
                    get_sphere_uv(outward_normal, rec.u, rec.v);
                    rec.setMaterial(_material);
                    return true;
                }

                virtual bool bounding_box(double time0, double time1, raytracer::AABB& output_box) const override
                {
                    output_box = raytracer::AABB(position, position);
                    return true;
                }

                virtual double densityValue(UNUSED const Math::Vector3D &o, UNUSED const Math::Vector3D &v) const override {return 0;};
                virtual Math::Vector3D random(UNUSED const Math::Vector3D & o) const override {return Math::Vector3D(1, 0, 0);};

            protected:
            private:
                Math::Vector3D _center;
                Math::Color color;
        };
    }

#endif /* !POINTLIGHT_HPP_ */
