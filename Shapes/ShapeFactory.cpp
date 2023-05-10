/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** ShapeFactory
*/

#include "ShapeFactory.hpp"

namespace raytracer {
    ShapeFactory::ShapeFactory() {}

    std::shared_ptr<IShape> ShapeFactory::createShape(std::string type, Math::Vector3D center, double radius, std::shared_ptr<IMaterial> material)
    {
        if (type == "sphere")
            return std::make_shared<Sphere>(center, radius, material);
        if (type == "cone")
            return std::make_shared<Cone>(center, radius, material);
        if (type == "cylinder")
            return std::make_shared<Cylinder>(center, radius, material);
        return nullptr;
    }

    std::shared_ptr<IShape> ShapeFactory::createShape(std::string type, Math::Vector3D center, double radius, double height, std::shared_ptr<IMaterial> material)
    {
        if (type == "cylinder")
            return std::make_shared<LimitedCylinder>(center, radius, height, material);
        return nullptr;
    }

    std::shared_ptr<IShape> ShapeFactory::createShape(std::string type, std::string axis, double a, double b, double c, double d, double k, std::shared_ptr<IMaterial> material)
    {
        if (type == "rectangle") {
            if (axis == "XY")
                return std::make_shared<XYRectangle>(a, b, c, d, k, material);
            else if (axis == "XZ")
                return std::make_shared<XZRectangle>(a, b, c, d, k, material);
            else if (axis == "YZ")
                return std::make_shared<YZRectangle>(a, b, c, d, k, material);
        } else if (type == "light") {
            if (axis == "XY")
                return std::make_shared<raytracer::DirectionnalLight>(std::make_shared<XYRectangle>(a, b, c, d, k, material));
            else if (axis == "XZ")
                return std::make_shared<raytracer::DirectionnalLight>(std::make_shared<XZRectangle>(a, b, c, d, k, material));
            else if (axis == "YZ")
                return std::make_shared<raytracer::DirectionnalLight>(std::make_shared<YZRectangle>(a, b, c, d, k, material));
        }
        return nullptr;
    }

    std::shared_ptr<IShape> ShapeFactory::createShape(std::string type, Math::Vector3D p0, Math::Vector3D p1, std::shared_ptr<IMaterial> material)
    {
        if (type == "box")
            return std::make_shared<raytracer::Box>(p0, p1, material);
        return nullptr;
    }

}