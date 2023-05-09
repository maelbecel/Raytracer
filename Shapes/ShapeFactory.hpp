/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** ShapeFactory
*/

#ifndef SHAPEFACTORY_HPP_
    #define SHAPEFACTORY_HPP_

    #include <memory>
    #include "../Shapes/IShape.hpp"
    #include "../Material/IMaterial.hpp"
    #include "../Shapes/Sphere.hpp"
    #include "../Shapes/XYRectangle.hpp"
    #include "../Shapes/XZRectangle.hpp"
    #include "../Shapes/YZRectangle.hpp"
    #include "../Shapes/DirectionnalLight.hpp"
    #include "../Shapes/Box.hpp"

    namespace raytracer {
        class ShapeFactory {
            public:
                ShapeFactory();
                ~ShapeFactory() = default;

                std::shared_ptr<IShape> createShape(std::string type, Math::Vector3D center, double radius, std::shared_ptr<IMaterial> material);
                std::shared_ptr<IShape> createShape(std::string type, std::string axis, double a, double b, double c, double d, double k, std::shared_ptr<IMaterial> material);
                std::shared_ptr<IShape> createShape(std::string type, Math::Vector3D p0, Math::Vector3D p1, std::shared_ptr<IMaterial> material);
            protected:
            private:
        };
    }

#endif /* !SHAPEFACTORY_HPP_ */
