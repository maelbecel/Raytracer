/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
    #define SPHERE_HPP_

    #include "../Ray.hpp"
    #include "../Maths/Vector3D.hpp"
    #include "IShape.hpp"
    #include <iostream>

    namespace raytracer {
        class Sphere : public IShape {
            public:
                Sphere() {};
                Sphere(Math::Vector3D center, double radius, std::shared_ptr<IMaterial> material) : _center(center), _radius(radius), _material(material) {};
                Sphere(const Sphere &other) {
                    _center = other._center;
                    _radius = other._radius;
                    _material = other._material;
                };

                Sphere &operator=(const Sphere &other) {
                    _center = other._center;
                    _radius = other._radius;
                    _material = other._material;
                    return *this;
                }

                virtual bool hit(UNUSED const Ray &r, double min, double max, HitRecord &rec) const override
                {
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
                    rec.setMaterial(_material);
                    return true;
                }

            protected:
            private:
                Math::Vector3D _center;
                double _radius;
                std::shared_ptr<IMaterial> _material;

        };
    }

#endif /* !SPHERE_HPP_ */
