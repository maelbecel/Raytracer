/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Ray
*/

#ifndef RAY_HPP_
    #define RAY_HPP_

    #include "./Maths/Point3D.hpp"

    namespace raytracer {
        class Ray {
            public:
                Ray(): Origin(), Direction() {};
                Ray(Math::Point3D origin, Math::Vector3D direction): Origin(origin), Direction(direction) {}
                Ray(const Ray &other): Origin(other.Origin), Direction(other.Direction) {}
                Ray &operator=(const Ray &other) {
                    Origin = other.Origin;
                    Direction = other.Direction;
                    return *this;
                }
                ~Ray() = default;

                Math::Point3D Origin;
                Math::Vector3D Direction;

            protected:
            private:
        };
    }

#endif /* !RAY_HPP_ */
