/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Ray
*/

#ifndef RAY_HPP_
    #define RAY_HPP_

    #include "./Maths/Vector3D.hpp"

    namespace raytracer {
        class Ray {
            public:
                Ray();
                Ray(Math::Vector3D origin, Math::Vector3D direction);
                Ray(const Ray &other);
                Ray &operator=(const Ray &other);

                Math::Vector3D at(double x) const;
                ~Ray() {};

                Math::Vector3D Origin;
                Math::Vector3D Direction;

            protected:
            private:
        };
    }

#endif /* !RAY_HPP_ */
