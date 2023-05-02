/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Plan
*/

#ifndef PLAN_HPP_
    #define PLAN_HPP_

    #include "IShape.hpp"

    namespace raytracer {
        class Plan : public IShape {
            public:
                Plan(Math::Vector3D vector, Math::Vector3D center, std::shared_ptr<IMaterial> mat) : _vector(vector), _center(center), _mat(mat) {}
                virtual bool hit(const Ray &r, double min, double max, HitRecord &rec) const override
                {
                    auto t = (_center - r.Origin).dot(_vector) / r.Direction.dot(_vector);
                    if (t < min || t > max)
                        return false;
                    rec.setT(t);
                    rec.setP(r.at(rec.getT()));
                    rec.setNormal(_vector);
                    rec.setMaterial(_mat);
                    return true;
                }

                virtual bool bounding_box(UNUSED double time0, UNUSED double time1, raytracer::AABB& output_box) const override
                {
                    output_box = raytracer::AABB(Math::Vector3D(-INFINITY, -INFINITY, -INFINITY), Math::Vector3D(INFINITY, INFINITY, INFINITY));
                    return true;
                }

            protected:
            private:
                Math::Vector3D _vector;
                Math::Vector3D _center;
                std::shared_ptr<IMaterial> _mat;
        };
    }

#endif /* !PLAN_HPP_ */
