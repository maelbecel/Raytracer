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
    #include "../Maths/Orthonormal.hpp"
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
                    get_sphere_uv(outward_normal, rec.u, rec.v);
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

                virtual double densityValue(const Math::Vector3D &o, const Math::Vector3D &v) const
                {
                    HitRecord rec;
                    if (!this->hit(Ray(o, v), 0.001, INFINITY, rec))
                        return 0;

                    auto cos_theta_max = sqrt(1 - _radius * _radius / (_center - o).len_squared());
                    auto solid_angle = 2 * M_PI * (1 - cos_theta_max);

                    return 1 / solid_angle;
                }

                virtual Math::Vector3D random(const Math::Vector3D &o) const
                {
                    Math::Vector3D direction = _center - o;
                    auto distance_squared = direction.len_squared();
                    Math::Orthonormal uvw;
                    uvw.build_from_w(direction);
                    return uvw.local(Math::Vector3D::random_to_sphere(_radius, distance_squared));
                }

            protected:
            private:
                Math::Vector3D _center;
                double _radius;
                std::shared_ptr<IMaterial> _material;
                static void get_sphere_uv(const Math::Vector3D &p, double &u, double &v) {
                    double theta = acos(-p.getY());
                    double phi = atan2(-p.getZ(), p.getX()) + M_PI;

                    u = phi / (2 * M_PI);
                    v = theta / M_PI;
                }

        };
    }

#endif /* !SPHERE_HPP_ */
