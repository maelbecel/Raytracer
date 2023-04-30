/*
** EPITECH PROJECT, 2023
** Raztracer
** File description:
** YzRectangle
*/

#ifndef YZ_RECTANGLE_HPP_
    #define YZ_RECTANGLE_HPP_

    #include "IShape.hpp"

    namespace raytracer {
        class YZRectangle : public IShape {
            public:
                YZRectangle() {}
                YZRectangle(double _y0, double _y1, double _z0, double _z1, double _k, std::shared_ptr<IMaterial> _mat)
                    : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mat(_mat) {}

                virtual bool hit(const Ray &r, double min, double may, HitRecord &rec) const override
                {
                    auto t = (k - r.Origin.getX()) / r.Direction.getX();
                    if (t < min || t > may)
                        return false;

                    auto y = r.Origin.getY() + t * r.Direction.getY();
                    auto z = r.Origin.getZ() + t * r.Direction.getZ();
                    if (y < y0 || y > y1 || z < z0 || z > z1)
                        return false;

                    rec.u = (y - y0)/(y1 - y0);
                    rec.v = (z - z0)/(z1 - z0);
                    rec.setT(t);

                    auto outward = Math::Vector3D(1, 0, 0);
                    rec.setFaceNormal(r, outward);
                    rec.setMaterial(mat);
                    rec.setP(r.at(t));
                    return true;
                }

                virtual bool bounding_box(UNUSED double time0, UNUSED double time1, AABB& output_box) const override
                {
                    output_box = AABB(Math::Vector3D(k - 0.0001, y0, z0), Math::Vector3D(k + 0.0001, y1, z1));
                    return true;
                }

            protected:
            private:
                double y0, y1, z0, z1, k;
                std::shared_ptr<IMaterial> mat;
        };
    }

#endif /* !Yz_RECTANGLE_HPP_ */
