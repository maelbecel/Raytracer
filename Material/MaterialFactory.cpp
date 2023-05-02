/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** MaterialFactory
*/

#include "MaterialFactory.hpp"

namespace raytracer {
    MaterialFactory::MaterialFactory() {}

    std::shared_ptr<IMaterial> MaterialFactory::createMaterial(std::string type, Math::Vector3D albedo, double fuzz)
    {
        if (type == "Lambertian")
            return std::make_shared<Lambertian>(albedo);
        if (type == "Metal")
            return std::make_shared<Metal>(albedo, fuzz);
        return nullptr;
    }

    std::shared_ptr<IMaterial> MaterialFactory::createMaterial(std::string type, double refraction)
    {
        if (type == "Dielectric")
            return std::make_shared<Dielectric>(refraction);
        return nullptr;
    }
}
