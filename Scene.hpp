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
    #include "./Object/Cosine.hpp"
    #include "./Object/Mix.hpp"
    #include "./Maths/Vector3D.hpp"
    #include "./Material/IMaterial.hpp"
    #include "./Shapes/IShape.hpp"
    #include "./Shapes/Sphere.hpp"
    #include <iostream>
    #include <fstream>
    #include <memory>

    namespace Parser {
        class Parser;
    }
    namespace raytracer {
        class Scene {
            public:
                Scene() {};
                ~Scene() = default;

                bool hit(const raytracer::Ray &r, double min, double max, raytracer::HitRecord &rec);
                bool bounding_box(double time0, double time1, AABB &output) const;
                Math::Color rayColor(Ray r, const Math::Color &background, std::shared_ptr<Scene> lights, int depth);

                static void writePixel(std::ofstream &out, Math::Color pixel, int samples);
                static void writePixel(std::string &buffer, Math::Color pixel, int samples);

                void addObject(std::shared_ptr<raytracer::IShape> object);
                std::vector<std::shared_ptr<raytracer::IShape>> getObjects(void) const;
                double densityValue(const Math::Vector3D &o, const Math::Vector3D &v) const;
                Math::Vector3D random(const Math::Vector3D &o) const;
                void ppmRenderer(Parser::Parser &parser, Scene lights);
                void gifRenderer(Parser::Parser &parser, Scene lights);
                Scene applyMovement(std::vector<std::shared_ptr<IShape>> list, std::vector<Math::Vector3D> moves, int frame);
                Scene applyRotation(std::vector<std::shared_ptr<IShape>> list, std::vector<Math::Vector3D> rotations, int frame);


            protected:
            private:
                std::vector<std::shared_ptr<raytracer::IShape>> _objects;
        };
    }

#endif /* !SCENE_HPP_ */
