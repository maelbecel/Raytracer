/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Translation
*/

#ifndef TRANSLATION_HPP_
    #define TRANSLATION_HPP_

    #include "IShape.hpp"

    namespace raytracer {
        class Translation : public IShape{
            public:
                Translation(std::shared_ptr<IShape> p, Math::Vector3D o) : ptr(p), offset(o) {}

                virtual bool hit(const Ray &r, double min, double max, HitRecord &rec) const override
                {
                    Ray moved(r.Origin - offset, r.Direction, r.time());

                    if (!ptr->hit(moved, min, max, rec))
                        return false;
                    rec.setP(rec.getP() + offset);
                    rec.setFaceNormal(moved, rec.getNormal());
                    return true;
                }

                virtual bool bounding_box(double time0, double time1, raytracer::AABB& output_box) const override
                {
                    if(!ptr->bounding_box(time0, time1, output_box))
                        return false;
                    output_box = AABB(output_box.min() + offset, output_box.max() + offset);
                    return true;
                }

            protected:
            private:
                std::shared_ptr<IShape> ptr;
                Math::Vector3D offset;
        };
    }

#endif /* !TRANSLATION_HPP_ */
