/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** DirectionnalLight
*/

#ifndef DIRECTIONNALLIGHT_HPP_
    #define DIRECTIONNALLIGHT_HPP_

    #include "IShape.hpp"

    namespace raytracer {
        class DirectionnalLight : public IShape {
            public:
                DirectionnalLight(std::shared_ptr<IShape> p) : ptr(p) {}

                virtual bool hit(const Ray &r, double min, double max, HitRecord &rec) const override
                {
                    if (!ptr->hit(r, min, max, rec))
                        return false;
                    rec.setFrontFace(!rec.isFrontFace());
                    return true;
                }

                virtual bool bounding_box(double time0, double time1, raytracer::AABB& output_box) const override
                {
                    return ptr->bounding_box(time0, time1, output_box);
                }

                virtual double densityValue(UNUSED const Math::Vector3D &o, UNUSED const Math::Vector3D &v) const override {return 0;};
                virtual Math::Vector3D random(UNUSED const Math::Vector3D & o) const override {return Math::Vector3D(1, 0, 0);};

            protected:
            private:
                std::shared_ptr<IShape> ptr;
        };
    }

#endif /* !DIRECTIONNALLIGHT_HPP_ */
