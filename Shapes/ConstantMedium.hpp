/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** ConstantMedium
*/

#ifndef CONSTANTMEDIUM_HPP_
    #define CONSTANTMEDIUM_HPP_

    #include "IShape.hpp"
    #include "../Texture/ITexture.hpp"
    #include "../Material/Isotropic.hpp"

    namespace raytracer {
        class ConstantMedium : public IShape {
            public:
                ConstantMedium(std::shared_ptr<IShape> b, double d, std::shared_ptr<ITexture> a) : boundary(b), density(-1/d), phase(std::make_shared<Isotropic>(a)){}
                ConstantMedium(std::shared_ptr<IShape> b, double d, Math::Color c) : boundary(b), density(-1/d), phase(std::make_shared<Isotropic>(c)){}

                virtual bool hit(const Ray &r, double min, double max, HitRecord &rec) const override
                {
                    HitRecord rec1, rec2;

                    if (!boundary->hit(r, -INFINITY, INFINITY, rec1) ||
                        !boundary->hit(r, rec1.getT() + 0.0001, INFINITY, rec2))
                        return false;
                    if (rec1.getT() < min)
                        rec1.setT(min);
                    if (rec2.getT() > max)
                        rec2.setT(max);
                    if (rec1.getT() >= rec2.getT())
                        return false;
                    if (rec1.getT() < 0)
                        rec1.setT(0);

                    const auto ray_length = r.Direction.len();
                    const auto b_distance = (rec2.getT() - rec1.getT()) * ray_length;
                    const auto hit_distance = density * log(random_double());

                    if (hit_distance > b_distance)
                        return false;
                    rec.setT(rec1.getT() + hit_distance / ray_length);
                    rec.setP(r.at(rec.getT()));
                    rec.setNormal(Math::Vector3D(1, 0, 0));
                    rec.setFrontFace(true);
                    rec.setMaterial(phase);

                    return true;
                }

                virtual bool bounding_box(double time0, double time1, raytracer::AABB& output_box) const override
                {
                    return boundary->bounding_box(time0, time1, output_box);
                }

                virtual double densityValue(UNUSED const Math::Vector3D &o, UNUSED const Math::Vector3D &v) const override {return 0;};
                virtual Math::Vector3D random(UNUSED const Math::Vector3D & o) const override {return Math::Vector3D(1, 0, 0);};

            protected:
            private:
                std::shared_ptr<IShape> boundary;
                double density;
                std::shared_ptr<IMaterial> phase;
        };
    }

#endif /* !CONSTANTMEDIUM_HPP_ */
