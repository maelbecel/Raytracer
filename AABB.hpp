/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** AABB
*/

#ifndef AABB_HPP_
    #define AABB_HPP_

    #include "Maths/Vector3D.hpp"
    #include "Ray.hpp"

    namespace raytracer {
        class AABB {
            public:
                AABB() {};
                AABB(const Math::Vector3D &a, const Math::Vector3D &b) {_min = a; _max = b;}
                AABB(const AABB &box, const Math::Vector3D v)
                {
                    _min = Math::Vector3D(fmin(box.min().getX(), v.getX()),
                                            fmin(box.min().getY(), v.getY()),
                                            fmin(box.min().getZ(), v.getZ()));
                    _max = Math::Vector3D(fmax(box.max().getX(), v.getX()),
                                            fmax(box.max().getY(), v.getY()),
                                            fmax(box.max().getZ(), v.getZ()));
                }

                Math::Vector3D min() const {return _min;}
                Math::Vector3D max() const {return _max;}

                bool hit(const raytracer::Ray &r, double min, double max) const {
                        auto t0 = fmin((_min.getX() - r.Origin.getX()) / r.Direction.getX(),
                                        (_max.getX() - r.Origin.getX()) / r.Direction.getX());
                        auto t1 = fmax((_min.getX() - r.Origin.getX()) / r.Direction.getX(),
                                        (_max.getX() - r.Origin.getX()) / r.Direction.getX());

                        min = fmax(t0, min);
                        max = fmin(t1, max);
                        if (max <= min)
                            return false;

                        t0 = fmin((_min.getY() - r.Origin.getY()) / r.Direction.getY(),
                                        (_max.getY() - r.Origin.getY()) / r.Direction.getY());
                        t1 = fmax((_min.getY() - r.Origin.getY()) / r.Direction.getY(),
                                        (_max.getY() - r.Origin.getY()) / r.Direction.getY());

                        min = fmax(t0, min);
                        max = fmin(t1, max);
                        if (max <= min)
                            return false;

                        t0 = fmin((_min.getZ() - r.Origin.getZ()) / r.Direction.getZ(),
                                        (_max.getZ() - r.Origin.getZ()) / r.Direction.getZ());
                        t1 = fmax((_min.getZ() - r.Origin.getZ()) / r.Direction.getZ(),
                                        (_max.getZ() - r.Origin.getZ()) / r.Direction.getZ());

                        min = fmax(t0, min);
                        max = fmin(t1, max);
                        if (max <= min)
                            return false;
                        return true;
                };

                AABB surrounding_box(AABB box) const {
                    Math::Vector3D small(fmin(_min.getX(), box.min().getX()),
                                        fmin(_min.getY(), box.min().getY()),
                                        fmin(_min.getZ(), box.min().getZ()));
                    Math::Vector3D big(fmax(_max.getX(), box.max().getX()),
                                        fmax(_max.getY(), box.max().getY()),
                                        fmax(_max.getZ(), box.max().getZ()));
                    return AABB(small, big);
                }

            private:
                Math::Vector3D _min;
                Math::Vector3D _max;
        };
    }

#endif /* !AABB_HPP_ */
