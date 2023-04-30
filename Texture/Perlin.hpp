/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Perlin
*/

#ifndef PERLIN_HPP_
    #define PERLIN_HPP_

    #include "../Maths/Vector3D.hpp"

    namespace raytracer {
        class Perlin {
            public:
                Perlin();
                ~Perlin();

                double noise(const Math::Vector3D& p) const;
                double turb(const Math::Vector3D& p, int depth = 7) const;

            protected:
            private:
                static const int point_count = 256;
                Math::Vector3D *randv;
                int *perm_x;
                int *perm_y;
                int *perm_z;

                static int* perlin_generate_perm();
                static void permute(int *p, int n);
                static double perlin_interp(Math::Vector3D c[2][2][2], double u, double v, double w);
        };
    }

#endif /* !PERLIN_HPP_ */
