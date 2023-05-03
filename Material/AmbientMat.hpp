/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** AmbiantLight
*/

#ifndef AMBIENTMAT_HPP_
    #define AMBIENTMAT_HPP_

    #include "IMaterial.hpp"
    #include "../Texture/ITexture.hpp"

    namespace raytracer {
        class AmbientMat : public IMaterial {
            public:
                AmbientMat(Math::Vector3D c) : color(c) {}
                virtual bool scatter(UNUSED const Ray& r_in, UNUSED const HitRecord& rec, UNUSED Math::Color& albedo, UNUSED Ray& scattered, UNUSED double &pdf) const override
                {
                    return true;
                }

                virtual Math::Color emitted(UNUSED double u, UNUSED double v, UNUSED const HitRecord& rec, UNUSED const Math::Vector3D &p) const override
                {
                    return color;
                }

                virtual double scatter_pdf(UNUSED const Ray& r_in, UNUSED const HitRecord& rec, UNUSED const Ray& scattered) const {return 0;};

            protected:
            private:
                Math::Vector3D color;
        };
    }

#endif /* !AMBIENTLMAT_HPP_ */
