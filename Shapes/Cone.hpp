/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Cone
*/

#ifndef CONE_HPP_
    #define CONE_HPP_

    #include "../Ray.hpp"
    #include "../Maths/Vector3D.hpp"
    #include "IShape.hpp"
    #include <iostream>

    namespace raytracer {
        class Cone : public IShape {
            public:
                Cone() {};
                Cone(Math::Vector3D center, double radius, std::shared_ptr<IMaterial> material) : _center(center), _radius(radius), _material(material) {};
                Cone(const Cone &other) {
                    _center = other._center;
                    _radius = other._radius;
                    _material = other._material;
                };

                Cone &operator=(const Cone &other) {
                    _center = other._center;
                    _radius = other._radius;
                    _material = other._material;
                    return *this;
                }

                virtual bool hit(const Ray &r, double min, double max, HitRecord &rec) const override
                {
                    Math::Vector3D oc = r.Origin - _center;
                    double a = r.Direction.getX() * r.Direction.getX() + r.Direction.getZ() * r.Direction.getZ() - r.Direction.getY() * r.Direction.getY();
                    double b = 2 * (oc.getX() * r.Direction.getX() + oc.getZ() * r.Direction.getZ() - oc.getY() * r.Direction.getY());
                    double c = oc.getX() * oc.getX() + oc.getZ() * oc.getZ() - oc.getY() * oc.getY();

                    double discriminant = b * b - 4 * a * c;
                    if (discriminant < 0)
                        return false;
                    double sqrtd = sqrt(discriminant);

                    double root = (-b - sqrtd) / (2 * a);
                    if (root < min || root > max) {
                        root = (-b + sqrtd) / (2 * a);
                        if (root < min || root > max)
                            return false;
                    }
                    rec.setT(root);
                    rec.setP(r.at(rec.getT()));
                    Math::Vector3D outward_normal = (rec.getP() - _center) / _radius;
                    rec.setFaceNormal(r, outward_normal);
                    get_cone_uv(outward_normal, rec.u, rec.v);
                    rec.setMaterial(_material);
                    return true;
                }

                virtual bool bounding_box(UNUSED double time0, UNUSED double time1, raytracer::AABB& output_box) const override
                {
                    output_box = AABB(
                        _center - Math::Vector3D(_radius, _radius, _radius),
                        _center + Math::Vector3D(_radius, _radius, _radius)
                    );
                    return true;
                }

                virtual double densityValue(UNUSED const Math::Vector3D &o, UNUSED const Math::Vector3D &v) const override {return 0;};
                virtual Math::Vector3D random(UNUSED const Math::Vector3D & o) const override {return Math::Vector3D(1, 0, 0);};

            protected:
            private:
                Math::Vector3D _center;
                double _radius;
                std::shared_ptr<IMaterial> _material;
                static void get_cone_uv(const Math::Vector3D &p, double &u, double &v) {
                    double theta = std::acos(-p.getY());
                    double phi = atan2(-p.getZ(), p.getX()) + M_PI;

                    u = phi / (2 * M_PI);
                    v = theta / M_PI;
                }

        };
    }

#endif /* !CYLINDER_HPP_ */
