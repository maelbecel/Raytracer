/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Triangle
*/

#ifndef TRIANGLE_HPP_
    #define TRIANGLE_HPP_

    #include "../Maths/Point3D.hpp"
    #include "IShape.hpp"
    #include "../Ray.hpp"

    namespace raytracer {
        class Triangle : public IShape {
            public:
                Triangle();
                Triangle(Math::Point3D a, Math::Point3D b, Math::Point3D c);
                Triangle(const Triangle &other);
                Triangle &operator=(const Triangle &other);
                ~Triangle() {};

                Math::Point3D A;
                Math::Point3D B;
                Math::Point3D C;

                bool hits(UNUSED raytracer::Ray ray);

            protected:
            private:
        };
    }

#endif /* !TRIANGLE_HPP_ */
