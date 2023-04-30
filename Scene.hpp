/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Scene
*/

#ifndef SCENE_HPP_
    #define SCENE_HPP_

    #include <iostream>
    #include <vector>
    #include "./Object/HitRecord.hpp"
    #include "./Maths/Vector3D.hpp"
    #include "./Material/IMaterial.hpp"
    #include "./Shapes/IShape.hpp"
    #include "./Shapes/Sphere.hpp"
    #include <iostream>
    #include <fstream>
    #include <memory>
    namespace raytracer {
        class Scene {
            public:
                Scene() {};
                ~Scene() = default;

                bool hit(const raytracer::Ray &r, double min, double max, raytracer::HitRecord &rec);
                bool bounding_box(double time0, double time1, AABB &output) const;
                Math::Color rayColor(Ray r, const Math::Color &background, int depth);

                static void writePixel(std::ofstream &out, Math::Color pixel, int samples);

                void addObject(std::shared_ptr<raytracer::IShape> object);
                std::vector<std::shared_ptr<raytracer::IShape>> getObjects(void) const;
            protected:
            private:
                std::vector<std::shared_ptr<raytracer::IShape>> _objects;
        };
    }

#endif /* !SCENE_HPP_ */
