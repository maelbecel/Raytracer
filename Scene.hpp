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
    #include "Camera.hpp"
    #include "Lights/ILight.hpp"
    #include "Object.hpp"
    #include "Object.hpp"
    #include "./Shapes/Sphere.hpp"
    #include "./Shapes/Triangle.hpp"
    #include "./Maths/Point3D.hpp"
    #include "./Lights/Ambiant.hpp"
    #include "./Lights/ILight.hpp"
    #include <iostream>
    #include <fstream>
    #include <memory>

    #define HEIGHT 1080
    #define WIDTH 1920

    namespace raytracer {
        class Scene {
            public:
                Scene() {_camera = nullptr;};

                ~Scene() {
                    _lights.clear();
                    _objects.clear();
                };

                void render(void);
                void get_ray(raytracer::Ray r, Math::Point3D point);

                void addCamera(std::shared_ptr<Camera> camera) {_camera = camera;};
                void addLight(std::shared_ptr<raytracer::ILight> light) {_lights.push_back(light);};
                void addObject(std::shared_ptr<Object> object) {_objects.push_back(object);};

                std::shared_ptr<Camera> getCamera(void) {return _camera;};
                std::vector<std::shared_ptr<raytracer::ILight>> getLights(void) {return _lights;};
                std::vector<std::shared_ptr<Object>> getObjects(void) {return _objects;};

            protected:
            private:
                std::ofstream _file = std::ofstream("image.ppm");
                std::shared_ptr<Camera> _camera;
                std::vector<std::shared_ptr<raytracer::ILight>> _lights;
                std::vector<std::shared_ptr<Object>> _objects;
        };
    }

#endif /* !SCENE_HPP_ */
