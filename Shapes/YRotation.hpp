/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** YRotation
*/

#ifndef YROTATION_HPP_
    #define YROTATION_HPP_

    #include "IShape.hpp"

    namespace raytracer
    {
        class YRotation : public IShape {
            public:
                YRotation(std::shared_ptr<IShape> p, double angle) : ptr(p)
                {
                    auto radians = angle * M_PI / 180;

                    sin_theta = sin(radians);
                    cos_theta = cos(radians);
                    hasBox = ptr->bounding_box(0, 1, bbox);

                    Math::Vector3D min(INFINITY, INFINITY, INFINITY);
                    Math::Vector3D max(-INFINITY, -INFINITY, -INFINITY);

                    for (int i = 0; i < 2; i++)
                        for (int j = 0; j < 2; j++)
                            for (int k = 0; k < 2; k++) {
                                auto x = i * bbox.max().getX() + (1 - i) * bbox.min().getX();
                                auto y = j * bbox.max().getY() + (1 - j) * bbox.min().getY();
                                auto z = k * bbox.max().getZ() + (1 - k) * bbox.min().getZ();

                                auto newx =  cos_theta * x + sin_theta * z;
                                auto newz = -sin_theta * x + cos_theta * z;

                                Math::Vector3D tester(newx, y, newz);

                                min.setX(fmin(min.getX(), tester.getX()));
                                max.setX(fmax(max.getX(), tester.getX()));

                                min.setY(fmin(min.getY(), tester.getY()));
                                max.setY(fmax(max.getY(), tester.getY()));

                                min.setZ(fmin(min.getZ(), tester.getZ()));
                                max.setZ(fmax(max.getZ(), tester.getZ()));

                            }
                    bbox = AABB(min, max);
                }

                virtual bool hit(const Ray &r, double min, double max, HitRecord &rec) const override
                {
                    Math::Vector3D origin(r.Origin);
                    Math::Vector3D direction(r.Direction);

                    origin.setX(cos_theta * r.Origin.getX() - sin_theta * r.Origin.getZ());
                    origin.setZ(sin_theta * r.Origin.getX() + cos_theta * r.Origin.getZ());
                    direction.setX(cos_theta * r.Direction.getX() - sin_theta * r.Direction.getZ());
                    direction.setZ(sin_theta * r.Direction.getX() + cos_theta * r.Direction.getZ());

                    Ray rotated(origin, direction, r.time());
                    if (!ptr->hit(rotated, min, max, rec))
                        return false;

                    Math::Vector3D p(rec.getP());
                    Math::Vector3D normal(rec.getNormal());

                    p.setX(cos_theta * rec.getP().getX() + sin_theta * rec.getP().getZ());
                    p.setZ(-sin_theta * rec.getP().getX() + cos_theta * rec.getP().getZ());
                    normal.setX(cos_theta * rec.getNormal().getX() + sin_theta * rec.getNormal().getZ());
                    normal.setZ(-sin_theta * rec.getNormal().getX() + cos_theta * rec.getNormal().getZ());

                    rec.setP(p);
                    rec.setFaceNormal(rotated, normal);
                    return true;
                }

                virtual bool bounding_box(UNUSED double time0, UNUSED double time1, raytracer::AABB& output_box) const override
                {
                    output_box = bbox;
                    return hasBox;
                }

            protected:
            private:
                std::shared_ptr<IShape> ptr;
                double sin_theta;
                double cos_theta;
                bool hasBox;
                AABB bbox;
        };
    }

#endif /* !YROTATION_HPP_ */
