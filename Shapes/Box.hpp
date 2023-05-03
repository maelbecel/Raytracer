/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Box
*/

#ifndef BOX_HPP_
    #define BOX_HPP_

    #include "IShape.hpp"
    #include "XYRectangle.hpp"
    #include "XZRectangle.hpp"
    #include "YZRectangle.hpp"
    #include <memory>
    #include <vector>

    namespace raytracer {
        class Box : public IShape {
            public:
                Box() {};
                Box(const Math::Vector3D &p0, const Math::Vector3D &p1, std::shared_ptr<IMaterial> ptr)
                {
                    box_min = p0;
                    box_max = p1;

                    sides.push_back(std::make_shared<XYRectangle>(p0.getX(), p1.getX(), p0.getY(), p1.getY(), p1.getZ(), ptr));
                    sides.push_back(std::make_shared<XYRectangle>(p0.getX(), p1.getX(), p0.getY(), p1.getY(), p0.getZ(), ptr));

                    sides.push_back(std::make_shared<XZRectangle>(p0.getX(), p1.getX(), p0.getZ(), p1.getZ(), p1.getY(), ptr));
                    sides.push_back(std::make_shared<XZRectangle>(p0.getX(), p1.getX(), p0.getZ(), p1.getZ(), p0.getY(), ptr));

                    sides.push_back(std::make_shared<YZRectangle>(p0.getY(), p1.getY(), p0.getZ(), p1.getZ(), p1.getX(), ptr));
                    sides.push_back(std::make_shared<YZRectangle>(p0.getY(), p1.getY(), p0.getZ(), p1.getZ(), p0.getX(), ptr));

                }

                virtual bool hit(const Ray &r, double min, double max, HitRecord &rec) const override
                {
                    HitRecord tempRec;
                    bool hitAnything = false;
                    auto closestSoFar = max;

                    for (auto side : sides) {
                        if (side->hit(r, min, closestSoFar, tempRec)) {
                            hitAnything = true;
                            closestSoFar = tempRec.getT();
                            rec = tempRec;
                        }
                    }
                    return hitAnything;
                }

                virtual bool bounding_box(UNUSED double time0, UNUSED double time1, AABB& output_box) const override
                {
                    output_box = AABB(box_min, box_max);
                    return true;
                }

                virtual double densityValue(UNUSED const Math::Vector3D &o, UNUSED const Math::Vector3D &v) const override {return 0;};
                virtual Math::Vector3D random(UNUSED const Math::Vector3D & o) const override {return Math::Vector3D(1, 0, 0);};

            protected:
            private:
                Math::Vector3D box_min;
                Math::Vector3D box_max;
                std::vector<std::shared_ptr<IShape>> sides;
        };
    }

#endif /* !BOX_HPP_ */
