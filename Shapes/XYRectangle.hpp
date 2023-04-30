/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** XYRectangle
*/

#ifndef XY_RECTANGLE_HPP_
    #define XY_RECTANGLE_HPP_

    #include "IShape.hpp"

    namespace raytracer {
        class XYRectangle : public IShape {
            public:
                XYRectangle() {}
                XYRectangle(double _x0, double _x1, double _y0, double _y1, double _k, std::shared_ptr<IMaterial> _mat)
                    : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mat(_mat) {}

                virtual bool hit(const Ray &r, double min, double max, HitRecord &rec) const override
                {
                    auto t = (k - r.Origin.getZ()) / r.Direction.getZ();
                    if (t < min || t > max)
                        return false;

                    auto x = r.Origin.getX() + t * r.Direction.getX();
                    auto y = r.Origin.getY() + t * r.Direction.getY();
                    if (x < x0 || x > x1 || y < y0 || y > y1)
                        return false;

                    rec.u = (x - x0)/(x1 - x0);
                    rec.v = (y - y0)/(y1 - y0);
                    rec.setT(t);

                    auto outward = Math::Vector3D(0, 0, 1);
                    rec.setFaceNormal(r, outward);
                    rec.setMaterial(mat);
                    rec.setP(r.at(t));
                    return true;
                }

                virtual bool bounding_box(UNUSED double time0, UNUSED double time1, raytracer::AABB& output_box) const override
                {
                    output_box = AABB(Math::Vector3D(x0, y0, k - 0.0001), Math::Vector3D(x1, y1, k + 0.0001));
                    return true;
                }

            protected:
            private:
                double x0, x1, y0, y1, k;
                std::shared_ptr<IMaterial> mat;
        };
    }

#endif /* !XY_RECTANGLE_HPP_ */
