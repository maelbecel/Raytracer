/*
** EPITECH PROJECT, 2023
** Raztracer
** File description:
** XzRectangle
*/

#ifndef XZ_RECTANGLE_HPP_
    #define XZ_RECTANGLE_HPP_

    #include "IShape.hpp"

    namespace raytracer {
        class XZRectangle : public IShape {
            public:
                XZRectangle() {}
                XZRectangle(double _x0, double _x1, double _z0, double _z1, double _k, std::shared_ptr<IMaterial> _mat)
                    : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mat(_mat) {}

                virtual bool hit(const Ray &r, double min, double max, HitRecord &rec) const override
                {
                    auto t = (k - r.Origin.getY()) / r.Direction.getY();
                    if (t < min || t > max)
                        return false;

                    auto x = r.Origin.getX() + t * r.Direction.getX();
                    auto z = r.Origin.getZ() + t * r.Direction.getZ();
                    if (x < x0 || x > x1 || z < z0 || z > z1)
                        return false;

                    rec.u = (x - x0)/(x1 - x0);
                    rec.v = (z - z0)/(z1 - z0);
                    rec.setT(t);

                    auto outward = Math::Vector3D(0, 1, 0);
                    rec.setFaceNormal(r, outward);
                    rec.setMaterial(mat);
                    rec.setP(r.at(t));
                    return true;
                }

                virtual bool bounding_box(UNUSED double time0, UNUSED double time1, AABB& output_box) const override
                {
                    output_box = AABB(Math::Vector3D(x0, k - 0.0001, z0), Math::Vector3D(x1, k + 0.0001, z1));
                    return true;
                }

                virtual double densityValue(UNUSED const Math::Vector3D &o, UNUSED const Math::Vector3D &v) const override
                {
                    HitRecord rec;
                    if (!hit(Ray(o, v), 0.001, INFINITY, rec))
                        return 0;
                    auto area = (x1 - x0) * (z1 - z0);
                    auto distance_squared = rec.getT() * rec.getT() * v.len_squared();
                    auto cosine = fabs(v.dot(rec.getNormal()) / v.len());

                    return distance_squared / (cosine * area);
                }

                virtual Math::Vector3D random(UNUSED const Math::Vector3D & o) const override
                {
                    auto point = Math::Vector3D(random_double_mm(x0, x1), k, random_double_mm(z0, z1));
                    return point - o;
                }

            protected:
            private:
                double x0, x1, z0, z1, k;
                std::shared_ptr<IMaterial> mat;
        };
    }

#endif /* !Xz_RECTANGLE_HPP_ */
