/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** MaterialFactory
*/

#ifndef MATERIALFACTORY_HPP_
#define MATERIALFACTORY_HPP_

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>
#include "IMaterial.hpp"
#include "../Maths/Vector3D.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"
#include "Dielectric.hpp"
#include "DiffuseLight.hpp"

namespace raytracer {
    class MaterialFactory {
        public:
            MaterialFactory();
            ~MaterialFactory() = default;

            std::shared_ptr<IMaterial> createMaterial(std::string type, Math::Vector3D albedo, double fuzz = 0.0);
            std::shared_ptr<IMaterial> createMaterial(std::string type, double refraction);
        protected:
        private:
    };
}

#endif /* !MATERIALFACTORY_HPP_ */
