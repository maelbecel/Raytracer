/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** MatrixRotation
*/

#ifndef MATRIXROTATION_HPP_
    #define MATRIXROTATION_HPP_

    #include "IShape.hpp"


    namespace raytracer {
        class MatrixRotation : public IShape {
            public:
                MatrixRotation(std::shared_ptr<IShape> p, int m[3][3]) : ptr(p)
                {
                    Math::Vector3D min(INFINITY, INFINITY, INFINITY);
                    Math::Vector3D max(-INFINITY, -INFINITY, -INFINITY);

                    for (int i = 0; i < 3; i++)
                        for (int j = 0; j < 3; j++)
                            matrix[i][j] = m[i][j];

                    hasBox = ptr->bounding_box(0, 1, bbox);

                    for (int i = 0; i < 2; i++)
                        for (int j = 0; j < 2; j++)
                            for (int k = 0; k < 2; k++) {
                                auto x = i * bbox.max().getX() + (1 - i) * bbox.min().getX();
                                auto y = j * bbox.max().getY() + (1 - j) * bbox.min().getY();
                                auto z = k * bbox.max().getZ() + (1 - k) * bbox.min().getZ();

                                auto newx =  matrix[i][0] * x + matrix[i][1] * y + matrix[i][2] * z;
                                auto newy =  matrix[j][0] * x + matrix[j][1] * y + matrix[j][2] * z;
                                auto newz =  matrix[k][0] * x + matrix[k][1] * y + matrix[k][2] * z;

                                Math::Vector3D tester(newx, newy, newz);

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

                    for (int i = 0; i < 3; i++) {
                        origin.setX(matrix[i][0] * r.Origin.getX());
                        origin.setY(matrix[i][1] * r.Origin.getY());
                        origin.setZ(matrix[i][2] * r.Origin.getZ());
                        direction.setX(matrix[i][0] * r.Direction.getX());
                        direction.setY(matrix[i][1] * r.Direction.getY());
                        direction.setZ(matrix[i][2] * r.Direction.getZ());
                    }
                    Ray rotated_r(origin, direction);
                    if (!ptr->hit(rotated_r, min, max, rec))
                        return false;
                    Math::Vector3D p(rec.getP());
                    Math::Vector3D normal(rec.getNormal());

                    for (int i = 0; i < 3; i++) {
                        p.setX(matrix[i][0] * rec.getP().getX());
                        p.setY(matrix[i][1] * rec.getP().getY());
                        p.setZ(matrix[i][2] * rec.getP().getZ());
                        normal.setX(matrix[i][0] * rec.getNormal().getX());
                        normal.setY(matrix[i][1] * rec.getNormal().getY());
                        normal.setZ(matrix[i][2] * rec.getNormal().getZ());
                    }
                    rec.setP(p);
                    rec.setNormal(normal);
                    return true;
                }

                virtual bool bounding_box(double time0, double time1, AABB &output_box) const override
                {
                    output_box = bbox;
                    return hasBox;
                }
            protected:
            private:
                std::shared_ptr<IShape> ptr;
                int matrix[3][3];
                bool hasBox;
                AABB bbox;
        };
    }

#endif /* !MATRIXROTATION_HPP_ */
