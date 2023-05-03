/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** AmbientLight
*/

#ifndef AMBIENTLIGHT_HPP_
    #define AMBIENTLIGHT_HPP_

    #include "IShape.hpp"
    #include "../Material/AmbientMat.hpp"

    namespace raytracer {
        class AmbientLight : public IShape {
            public:
                AmbientLight(Math::Color c) : _mat(std::make_shared<AmbientMat>(c)) {}
                virtual bool hit(UNUSED const Ray &r, UNUSED double min, UNUSED double max, HitRecord &rec) const override
                {
                    if (rec.getMaterial() == nullptr) {
                        rec.setMaterial(_mat);
                        return false;
                    } else
                        return true;
                }

                virtual bool bounding_box(UNUSED double time0, UNUSED double time1, AABB& output_box) const override
                {
                    output_box = raytracer::AABB(Math::Vector3D(-INFINITY, -INFINITY, -INFINITY), Math::Vector3D(INFINITY, INFINITY, INFINITY));
                    return true;
                }

                virtual double densityValue(UNUSED const Math::Vector3D &o, UNUSED const Math::Vector3D &v) const override {return 0;};
                virtual Math::Vector3D random(UNUSED const Math::Vector3D & o) const override {return Math::Vector3D(1, 0, 0);};

            protected:
            private:
                std::shared_ptr<AmbientMat> _mat;
        };
    }

#endif /* !AMBIENTLIGHT_HPP_ */
