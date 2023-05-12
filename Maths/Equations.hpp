/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Equations
*/

#ifndef EQUATIONS_HPP_
    #define EQUATIONS_HPP_

    #include <cmath>
    #include <vector>

    #define IsZero(x) ((x) > -1e-9 && (x) < 1e-9)

namespace Math {
    class Equations {

        public:
            Equations(){};

            std::vector<double> SolveQuadric(std::vector<double> coeffs, std::vector<double> solutions)
            {
                double p, q;
                double discriminant;

                p = coeffs.at(1) / (2 * coeffs.at(2));
                q = coeffs.at(0) / coeffs.at(2);

                discriminant = p * p - q;

                if (IsZero(discriminant))
                {
                    solutions.push_back(-p);
                    return solutions;
                }
                else if (discriminant < 0)
                    return solutions;
                else
                {
                    double sqrt_discriminant = sqrt(discriminant);

                    solutions.push_back(sqrt_discriminant - p);
                    solutions.push_back(-sqrt_discriminant - p);
                    return solutions;
                }
                return solutions;
            };

            std::vector<double> SolveCubic(std::vector<double> coeffs, std::vector<double> solutions)
            {
                int i, num;
                double sub;
                double A, B, C;
                double sq_A, p, q;
                double cb_p, D;

                A = coeffs.at(2) / coeffs.at(3);
                B = coeffs.at(1) / coeffs.at(3);
                C = coeffs.at(0) / coeffs.at(3);

                sq_A = A * A;
                p = 1.0 / 3 * (-1.0 / 3 * sq_A + B);
                q = 1.0 / 2 * (2.0 / 27 * A * sq_A - 1.0 / 3 * A * B + C);

                cb_p = p * p * p;
                D = q * q + cb_p;

                if (IsZero(D))
                {
                    if (IsZero(q))
                    {
                        solutions.push_back(0);
                        num = 1;
                    }
                    else
                    {
                        double u = cbrt(-q);
                        solutions.push_back(2 * u);
                        solutions.push_back(-u);
                        num = 2;
                    }
                }
                else if (D < 0)
                {
                    double phi = 1.0 / 3 * std::acos(-q / sqrt(-cb_p));
                    double t = 2 * sqrt(-p);

                    solutions.push_back(t * cos(phi));
                    solutions.push_back(-t * cos(phi + M_PI / 3));
                    solutions.push_back(-t * cos(phi - M_PI / 3));
                    num = 3;
                }
                else
                {
                    double sqrt_D = sqrt(D);
                    double u = cbrt(sqrt_D - q);
                    double v = -cbrt(sqrt_D + q);

                    solutions.push_back(u + v);
                    num = 1;
                }

                sub = 1.0 / 3 * A;

                for (i = 0; i < num; ++i)
                    solutions.at(i) -= sub;

                return solutions;
            };

            std::vector<double> SolveQuartic(std::vector<double> coeffs, std::vector<double> solutions)
            {
                int i, num = 0;
                double z, u, v, sub;
                double A, B, C, D;
                double sq_A, p, q, r;

                A = coeffs.at(3) / coeffs.at(4);
                B = coeffs.at(2) / coeffs.at(4);
                C = coeffs.at(1) / coeffs.at(4);
                D = coeffs.at(0) / coeffs.at(4);

                sq_A = A * A;
                p = -3.0 / 8 * sq_A + B;
                q = 1.0 / 8 * sq_A * A - 1.0 / 2 * A * B + C;
                r = -3.0 / 256 * sq_A * sq_A + 1.0 / 16 * sq_A * B - 1.0 / 4 * A * C + D;

                if (IsZero(r))
                {
                    coeffs.push_back(q);
                    coeffs.push_back(p);
                    coeffs.push_back(0);
                    coeffs.push_back(1);

                    solutions = SolveCubic(coeffs, solutions);

                    solutions[num++] = 0;
                }
                else
                {
                    coeffs.at(0) = 1.0 / 2 * r * p - 1.0 / 8 * q * q;
                    coeffs.at(1) = -r;
                    coeffs.at(2) = -1.0 / 2 * p;
                    coeffs.at(3) = 1;

                    (void)SolveCubic(coeffs, solutions);

                    z = solutions.at(0);

                    u = z * z - r;
                    v = 2 * z - p;

                    if (IsZero(u))
                        u = 0;
                    else if (u > 0)
                        u = sqrt(u);
                    else
                        return solutions;

                    if (IsZero(v))
                        v = 0;
                    else if (v > 0)
                        v = sqrt(v);
                    else
                        return solutions;

                    coeffs.at(0) = z - u;
                    coeffs.at(1) = q < 0 ? -v : v;
                    coeffs.at(2) = 1;

                    solutions = SolveQuadric(coeffs, solutions);

                    coeffs.at(0) = z + u;
                    coeffs.at(1) = q < 0 ? v : -v;
                    coeffs.at(2) = 1;

                    for (std::size_t i = 0; i < solutions.size(); i++)
                        solutions.at(i) += num;
                    SolveQuadric(coeffs, solutions);
                }
                sub = 1.0 / 4 * A;

                for (i = 0; i < (int)solutions.size() && i < num; ++i)
                    solutions.at(i) -= sub;
                return solutions;
            };
    };
};

#endif /* !EQUATIONS_HPP_ */
