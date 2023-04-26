/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Object
*/

#ifndef OBJECT_HPP_
    #define OBJECT_HPP_

    #include "Shapes/IShape.hpp"
    #include "Material/IMaterial.hpp"
    #include <memory>

    namespace raytracer {
        class Color {
            public:
                int R;
                int G;
                int B;
                Color() : R(0), G(0), B(0) {};
                Color(int r, int g, int b) : R(r), G(g), B(b) {};
        };
        class Object {
            public:
                Object() {};
                Object(std::shared_ptr<IShape> shape, std::shared_ptr<IMaterial> _material);
                ~Object() = default;

                void setShape(std::shared_ptr<IShape> shape) {_shape = shape;};
                void setMaterial(std::shared_ptr<IMaterial> material) {_material = material;};
                void setColor(Color color) {_color = color;};

                std::shared_ptr<IShape> getShape(void) {return _shape;};
                std::shared_ptr<IMaterial> getMaterial(void) {return _material;};
                Color getColor(void) {return _color;};

                Math::Vector3D getNormal(Math::Point3D point);

            protected:
            private:
                std::shared_ptr<IShape> _shape;
                std::shared_ptr<IMaterial> _material;
                Color _color;

        };
    }

#endif /* !OBJECT_HPP_ */
