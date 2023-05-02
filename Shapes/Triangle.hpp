/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Triangle
*/

#ifndef TRIANGLE_HPP_
    #define TRIANGLE_HPP_

    #include "IShape.hpp"

    namespace raytracer {
        class Triangle : public IShape {
            public:
                Triangle(Math::Vector3D A, Math::Vector3D B, Math::Vector3D C, std::shared_ptr<IMaterial> mat) : _A(A), _B(B), _C(C), _mat(mat) {}
                Triangle(Triangle &other) {
                    _A = other._A;
                    _B = other._B;
                    _C = other._C;
                    _mat = other._mat;
                }

                virtual bool hit(const Ray &r, UNUSED double min, double max, HitRecord &rec) const override
                {
                    Math::Vector3D edge1, edge2, h, s, q;
                    double a, f, u, v;
                    edge1 = _B - _A;
                    edge2 = _C - _A;
                    h = r.Direction.cross(edge2);
                    a = edge1.dot(h);
                    if (a > -0.00001 && a < 0.00001)
                        return false;
                    f = 1 / a;
                    s = r.Origin - _A;
                    u = f * s.dot(h);
                    if (u < 0.0 || u > 1.0)
                        return false;
                    q = s.cross(edge1);
                    v = f * r.Direction.dot(q);
                    if (v < 0.0 || u + v > 1.0)
                        return false;
                    double t = f * edge2.dot(q);
                    if (t > 0.00001 && t < max) {
                        rec.setT(t);
                        rec.setP(r.at(t));
                        rec.setNormal((edge1.cross(edge2)).normalize());
                        rec.setMaterial(_mat);
                        return true;
                    }
                    return false;
                }

                virtual bool bounding_box(UNUSED double time0, UNUSED double time1, raytracer::AABB& output_box) const override
                {
                    output_box = raytracer::AABB(_A, _B);
                    output_box = raytracer::AABB(output_box, _C);
                    return true;
                }

                Math::Vector3D _A;
                Math::Vector3D _B;
                Math::Vector3D _C;
                std::shared_ptr<IMaterial> _mat;
            protected:
            private:
        };
    };

#endif /* !TRIANGLE_HPP_ */
