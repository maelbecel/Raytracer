/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** ILight
*/

#ifndef ILIGHT_HPP_
    #define ILIGHT_HPP_

    #include "../Maths/Point3D.hpp"
    #include "../Object.hpp"

    namespace raytracer {
        class ILight {
            public:
                virtual ~ILight() = default;
                virtual Math::Vector3D getLightVector(Math::Point3D point) const = 0;
                virtual double getLightDistance(Math::Point3D point) const = 0;
                virtual double getLightIntensity(Math::Point3D point) const = 0;
                virtual double getLightAngle(Math::Vector3D normal, Math::Point3D point) const = 0;

                Color get_color(void) {return _color;};

            protected:
                Color _color;
                Math::Point3D _point;
            private:
        };
    }

#endif /* !ILIGHT_HPP_ */
