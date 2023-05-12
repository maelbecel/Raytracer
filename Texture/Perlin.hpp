/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Perlin
*/

#ifndef PERLIN_HPP_
    #define PERLIN_HPP_

    #include "../Maths/Vector3D.hpp"
    #include <vector>

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
                std::vector<Math::Vector3D> randv;
                std::vector<int> perm_x;
                std::vector<int> perm_y;
                std::vector<int> perm_z;

                static std::vector<int> perlin_generate_perm(void);
                static void permute(int *p, int n);
                static double perlin_interp(Math::Vector3D c[2][2][2], double u, double v, double w);
        };
    }

#endif /* !PERLIN_HPP_ */
