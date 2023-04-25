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
    #include <memory>

    namespace raytracer {
        class Scene {
            public:
                Scene() {_camera = nullptr;};

                ~Scene() {
                    _lights.clear();
                    _objects.clear();
                };

                void render(void);
                void addCamera(std::shared_ptr<Camera> camera) {_camera = camera;};
                void addLight(std::shared_ptr<ILight> light) {_lights.push_back(light);};
                void addObject(std::shared_ptr<Object> object) {_objects.push_back(object);};

                std::shared_ptr<Camera> getCamera(void) {return _camera;};
                std::vector<std::shared_ptr<ILight>> getLights(void) {return _lights;};
                std::vector<std::shared_ptr<Object>> getObjects(void) {return _objects;};

            protected:
            private:
                std::shared_ptr<Camera> _camera;
                std::vector<std::shared_ptr<ILight>> _lights;
                std::vector<std::shared_ptr<Object>> _objects;
        };
    }

#endif /* !SCENE_HPP_ */
