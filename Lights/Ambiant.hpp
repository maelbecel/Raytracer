/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Ambiant
*/

#ifndef AMBIANT_HPP_
    #define AMBIANT_HPP_

    #include "ILight.hpp"
    #include "../Maths/Vector3D.hpp"

    namespace raytracer {
        class Ambiant : public ILight {
            public:
                Ambiant(Math::Point3D point){_color = Color(155, 155, 50); _point = point;};

                Math::Vector3D getLightVector(Math::Point3D point) const;
                double getLightDistance(Math::Point3D point) const;
                double getLightIntensity(Math::Point3D point) const;
                double getLightAngle(Math::Vector3D normal, Math::Point3D point) const;
        };
    }

#endif /* !AMBIANT_HPP_ */
