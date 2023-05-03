/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** MovingSphere
*/

#ifndef MOVINGSPHERE_HPP_
    #define MOVINGSPHERE_HPP_

    #include "IShape.hpp"
    #include "../Material/IMaterial.hpp"

    namespace raytracer {
        class MovingSphere : public IShape {
            public:
                MovingSphere() {};
                MovingSphere(
                    Math::Vector3D center0,
                    Math::Vector3D center1,
                    double time0,
                    double time1,
                    double radius,
                    std::shared_ptr<IMaterial> mat_ptr
                ) : center0(center0), center1(center1), time0(time0), time1(time1), radius(radius), mat_ptr(mat_ptr) {};

                Math::Vector3D center(double time) const
                {
                    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
                }

                virtual bool hit(const Ray &r, double min, double max, HitRecord &rec) const override
                {
                    Math::Vector3D oc = r.Origin - center(r.time());
                    double a = r.Direction.len_squared();
                    double half_b = oc.dot(r.Direction);
                    double c = oc.len_squared() - radius * radius;

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
                    Math::Vector3D outward_normal = (rec.getP() - center(r.time())) / radius;
                    rec.setFaceNormal(r, outward_normal);
                    rec.setMaterial(mat_ptr);
                    return true;
                }

                virtual bool bounding_box(double time0, double time1, raytracer::AABB& output_box) const override
                {
                    raytracer::AABB box0(
                        center(time0) - Math::Vector3D(radius, radius, radius),
                        center(time0) + Math::Vector3D(radius, radius, radius)
                    );
                    raytracer::AABB box1(
                        center(time1) - Math::Vector3D(radius, radius, radius),
                        center(time1) + Math::Vector3D(radius, radius, radius)
                    );
                    output_box = box0.surrounding_box(box1);
                    return true;
                }

                virtual double densityValue(UNUSED const Math::Vector3D &o, UNUSED const Math::Vector3D &v) const override {return 0;};
                virtual Math::Vector3D random(UNUSED const Math::Vector3D & o) const override {return Math::Vector3D(1, 0, 0);};

            protected:
            private:
                Math::Vector3D center0, center1;
                double time0, time1;
                double radius;
                std::shared_ptr<IMaterial> mat_ptr;
        };
    }

#endif /* !MOVINGSPHERE_HPP_ */
