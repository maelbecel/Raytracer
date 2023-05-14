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
        if (type == "lambertian")
            return std::make_shared<Lambertian>(albedo);
        if (type == "metal")
            return std::make_shared<Metal>(albedo, fuzz);
        if (type == "diffuseLight")
            return std::make_shared<DiffuseLight>(albedo);
        return nullptr;
    }

    std::shared_ptr<IMaterial> MaterialFactory::createMaterial(std::string type, double refraction)
    {
        if (type == "dielectric")
            return std::make_shared<Dielectric>(refraction);
        if (type == "noise")
            return std::make_shared<Lambertian>(std::make_shared<Noise>(refraction));
        return nullptr;
    }

    std::shared_ptr<IMaterial> MaterialFactory::createMaterial(std::string type, Math::Vector3D colorA, Math::Vector3D colorB)
    {
        if (type == "chessboard")
            return std::make_shared<Lambertian>(std::make_shared<Checker>(colorA, colorB));
        return nullptr;
    }
}
