/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** LimitedCylinder
*/

#ifndef LIMITEDCYLINDER_HPP_
    #define LIMITEDCYLINDER_HPP_

    #include "../Ray.hpp"
    #include "../Maths/Vector3D.hpp"
    #include "IShape.hpp"
    #include <iostream>

    namespace raytracer {
        class LimitedCylinder : public IShape {
            public:
                LimitedCylinder() {};
                LimitedCylinder(Math::Vector3D center, double radius, double height, std::shared_ptr<IMaterial> material) : _center(center), _radius(radius), _height(height), _material(material) {};
                LimitedCylinder(const LimitedCylinder &other) {
                    _center = other._center;
                    _radius = other._radius;
                    _height = other._height;
                    _material = other._material;
                };

                LimitedCylinder &operator=(const LimitedCylinder &other) {
                    _center = other._center;
                    _radius = other._radius;
                    _height = other._height;
                    _material = other._material;
                    return *this;
                }

                virtual bool hit(const Ray &r, double min, double max, HitRecord &rec) const override
                {
                    Math::Vector3D oc = r.Origin - _center;
                    double a = r.Direction.getX() * r.Direction.getX() + r.Direction.getZ() * r.Direction.getZ();
                    double b = 2 * (oc.getX() * r.Direction.getX() + oc.getZ() * r.Direction.getZ());
                    double c = oc.getX() * oc.getX() + oc.getZ() * oc.getZ() - _radius * _radius;
                    double t2 = 0;
                    // double ymax = _center.getY() + _height;
                    // double ymin = _center.getY();

                    double discriminant = b * b - 4 * a * c;
                    if (discriminant < 0)
                        return false;
                    double sqrtd = sqrt(discriminant);

                    double t1 = (-b - sqrtd) / (2 * a);
                    if (t1 < min || t1 > max) {
                        t2 = (-b + sqrtd) / (2 * a);
                        if (t2 < min || t2 > max)
                            return false;
                    }
                    double t = (t1 > t2) ? t1 : t2;

                    if (oc.getY() + t * r.Direction.getY() < -_radius || oc.getY() + t * r.Direction.getY() > _radius)
                        return false;
                    rec.setT(t);
                    rec.setP(r.at(rec.getT()));
                    Math::Vector3D outward_normal = (rec.getP() - _center) / _radius;
                    rec.setFaceNormal(r, outward_normal);
                    get_cylinder_uv(outward_normal, rec.u, rec.v);
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
                double _height;
                std::shared_ptr<IMaterial> _material;
                static void get_cylinder_uv(const Math::Vector3D &p, double &u, double &v) {
                    double theta = std::acos(-p.getY());
                    double phi = atan2(-p.getZ(), p.getX()) + M_PI;

                    u = phi / (2 * M_PI);
                    v = theta / M_PI;
                }

        };
    }

#endif /* !LIMITEDCYLINDER_HPP_ */
