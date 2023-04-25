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
        class Object {
            public:
                Object() {};
                ~Object() = default;

                void setShape(std::shared_ptr<IShape> shape) {_shape = shape;};
                void setMaterial(std::shared_ptr<IMaterial> material) {_material = material;};

                std::shared_ptr<IShape> getShape(void) {return _shape;};
                std::shared_ptr<IMaterial> getMaterial(void) {return _material;};

            protected:
            private:
                std::shared_ptr<IShape> _shape;
                std::shared_ptr<IMaterial> _material;

        };
    }

#endif /* !OBJECT_HPP_ */
