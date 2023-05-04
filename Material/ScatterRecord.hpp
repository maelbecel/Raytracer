/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** ScatterRecord
*/

#ifndef SCATTERRECORD_HPP_
    #define SCATTERRECORD_HPP_

    #include "../Maths/Vector3D.hpp"
    #include "../Object/IDensity.hpp"
    #include "../Ray.hpp"
    #include <memory>

    namespace raytracer {
        class ScatterRecord {
            public:
                Ray specular;
                bool is_specular;
                Math::Color attenuation;
                std::shared_ptr<IDensity> density_ptr;
        };
    }

#endif /* !SCATTERRECORD_HPP_ */
