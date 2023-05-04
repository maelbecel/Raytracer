/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Perlin
*/

#include "Perlin.hpp"

namespace raytracer {

    /**
     * The function permutes an array of integers using a random swapping
     * algorithm.
     *
     * @param p p is a pointer to an integer array. The function permute shuffles
     * the elements of this array randomly using a permutation algorithm.
     * @param n n is the size of the array 'p'. It represents the number of
     * elements in the array that need to be permuted.
     */
    void Perlin::permute(int *p, int n)
    {
        for (int i = n - 1; i > 0; i--) {
            int target = static_cast<int>(random_double_mm(0, i+1));
            int tmp = p[i];

            p[i] = p[target];
            p[target] = tmp;
        }
    }

    /**
     * The function generates a permutation array of integers for use in Perlin
     * noise generation.
     *
     * @return The function `perlin_generate_perm` is returning a pointer to an
     * integer array `p`. The array `p` contains a permutation of integers from 0
     * to `point_count-1`.
     */
    int *Perlin::perlin_generate_perm(void)
    {
        auto p = new int[point_count];

        for(int i = 0; i < Perlin::point_count; i++)
            p[i] = i;

        permute(p, point_count);
        return p;

    }

    /**
     * The function initializes the Perlin noise generator by generating random
     * vectors and permutation arrays.
     */
    Perlin::Perlin()
    {
        randv = new Math::Vector3D[point_count];
        for (int i = 0; i < point_count; ++i)
            randv[i] = Math::Vector3D::random(-1, 1).unit_vector();
        perm_x = perlin_generate_perm();
        perm_y = perlin_generate_perm();
        perm_z = perlin_generate_perm();
    }

    /**
     * The Perlin destructor deletes dynamically allocated arrays.
     */
    Perlin::~Perlin()
    {
        delete[] randv;
        delete[] perm_x;
        delete[] perm_y;
        delete[] perm_z;
    }

    /**
     * The function calculates Perlin noise for a given 3D point using
     * interpolation and random vectors.
     *
     * @param p p is a 3D vector representing a point in space. The noise function
     * is used to generate Perlin noise at this point.
     *
     * @return a double value, which is the result of the Perlin interpolation of
     * the noise values at the eight corners of a cube surrounding the input point
     * p.
     */
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

    /**
     * The function calculates the turbulence of a given point in 3D space using
     * Perlin noise.
     *
     * @param p p is a 3D vector representing a point in space. It is used as the
     * input to the Perlin noise function to generate a noise value at that point.
     * @param depth The depth parameter in the turb function is the number of
     * iterations or layers of Perlin noise to be added together to create the
     * final turbulence value. The higher the depth, the more detailed and complex
     * the resulting turbulence will be.
     *
     * @return the absolute value of the accumulated noise values calculated using
     * Perlin noise algorithm with the given depth and input vector. The noise
     * values are accumulated using a weighted sum, where the weight decreases by
     * a factor of 0.5 for each iteration of the loop.
     */
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

    /**
     * The function performs Perlin interpolation on a 3D grid of vectors using
     * given u, v, and w values.
     *
     * @param c A 3D array of Math::Vector3D objects representing the gradient
     * vectors at the corners of a cube in the Perlin noise lattice.
     * @param u The u parameter represents the x-coordinate of the point in the 3D
     * space being interpolated. It is used to calculate the weight of the
     * surrounding grid points in the x-direction.
     * @param v The parameter "v" is a double value used in the Perlin
     * interpolation function to calculate the weighted average of the dot
     * products between the gradient vectors and the distance vectors between the
     * grid points and the input point. It represents the vertical coordinate of
     * the input point in the 3D space.
     * @param w The parameter "w" represents the third coordinate of a 3D point in
     * space. It is used in the Perlin noise algorithm to calculate the noise
     * value at that point.
     *
     * @return a double value, which is the result of the Perlin interpolation of
     * the given 3D vector array c, with the given u, v, and w values.
     */
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

