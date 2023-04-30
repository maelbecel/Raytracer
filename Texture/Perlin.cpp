/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Perlin
*/

#include "Perlin.hpp"

namespace raytracer {

    void Perlin::permute(int *p, int n)
    {
        for (int i = n - 1; i > 0; i--) {
            int target = static_cast<int>(random_double_mm(0, i+1));
            int tmp = p[i];

            p[i] = p[target];
            p[target] = tmp;
        }
    }

    int *Perlin::perlin_generate_perm(void)
    {
        auto p = new int[point_count];

        for(int i = 0; i < Perlin::point_count; i++)
            p[i] = i;

        permute(p, point_count);
        return p;

    }

    Perlin::Perlin()
    {
        randv = new Math::Vector3D[point_count];
        for (int i = 0; i < point_count; ++i)
            randv[i] = Math::Vector3D::random(-1, 1).unit_vector();
        perm_x = perlin_generate_perm();
        perm_y = perlin_generate_perm();
        perm_z = perlin_generate_perm();
    }

    Perlin::~Perlin()
    {
        delete[] randv;
        delete[] perm_x;
        delete[] perm_y;
        delete[] perm_z;
    }

    double Perlin::noise(const Math::Vector3D &p) const
    {
        auto u = p.getX() - floor(p.getX());
        auto v = p.getY() - floor(p.getY());
        auto w = p.getZ() - floor(p.getZ());

        auto i = static_cast<int>(floor(p.getX()));
        auto j = static_cast<int>(floor(p.getY()));
        auto k = static_cast<int>(floor(p.getZ()));
        Math::Vector3D c[2][2][2];

        for (int di = 0; di < 2; di++)
            for (int dj = 0; dj < 2; dj++)
                for (int dk = 0; dk < 2; dk++)
                    c[di][dj][dk] = randv[
                        perm_x[(i + di) & 255] ^
                        perm_y[(j + dj) & 255] ^
                        perm_z[(k + dk) & 255]
                    ];

        return perlin_interp(c, u, v, w);
    }

    double Perlin::turb(const Math::Vector3D &p, int depth) const
    {
        auto accum = 0.0;
        auto temp_p = p;
        auto weight = 1.0;

        for (int i = 0; i < depth; i++) {
            accum += weight * noise(temp_p);
            weight *= 0.5;
            temp_p *= 2;
        }
        return fabs(accum);
    }

    double Perlin::perlin_interp(Math::Vector3D c[2][2][2], double u, double v, double w)
    {
        auto uu = u * u * (3 - 2 * u);
        auto vv = v * v * (3 - 2 * v);
        auto ww = w * w * (3 - 2 * w);
        auto accum = 0.0;

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k= 0; k < 2; k++) {
                    Math::Vector3D weight(u - i, v - j, w - k);
                    accum +=    (i * uu + (1 - i) * (1 - uu))
                              * (j * vv + (1 - j) * (1 - vv))
                              * (k * ww + (1 - k) * (1 - ww))
                              * c[i][j][k].dot(weight);
                }
        return accum;
    }

}

