/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Builder
*/

#ifndef BUILDER_HPP_
    #define BUILDER_HPP_

    #include <iostream>
    #include <string>
    #include <memory>
    #include <libconfig.h++>
    #include "../Camera.hpp"
    #include "../Scene.hpp"
    #include "../Maths/Vector3D.hpp"
    #include "../Material/MaterialFactory.hpp"
    #include "../Shapes/ShapeFactory.hpp"
    #include "../Shapes/Sphere.hpp"
    #include "../Shapes/XYRectangle.hpp"
    #include "../Shapes/XZRectangle.hpp"
    #include "../Shapes/YZRectangle.hpp"

    namespace Builder {
        enum fileType_e {
            PPM,
            GIF
        };
        class Builder {
            public:
                Builder(std::string path);
                ~Builder() = default;

                raytracer::Camera parseCamera(void);
                raytracer::Scene buildScene(void);
                int getImageHeight(void);
                int getSamplesPerPixel(void);
                int getMaxDepth(void);
                Math::Color getAmbient(void);
                Math::Color getBackground(void);
                fileType_e getFileType(void);
                void addLights(raytracer::Scene &scene);
            protected:
            private:
                void buildLights(raytracer::Scene &scene);
                libconfig::Config _cfg;
                Math::Vector3D parseVector3D(const libconfig::Setting &setting);
                void buildSphere(raytracer::Scene &scene);
                void buildRectangle(raytracer::Scene &scene);
                void buildBox(raytracer::Scene &scene);
                void buildCylinder(raytracer::Scene &scene);
                void buildCone(raytracer::Scene &scene);
                std::shared_ptr<raytracer::IMaterial> buildMaterial(std::string name);
        };
    }

#endif /* !BUILDER_HPP_ */
