/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Builder
*/

#include "Builder.hpp"

namespace Builder {
    Builder::Builder(std::string path)
    {
        try {
            _cfg.readFile(path.c_str());
        } catch (const libconfig::FileIOException &fioex) {
            std::cerr << "I/O error while reading file." << std::endl;
            return;
        } catch (const libconfig::ParseException &pex) {
            std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
            return;
        }
    }

    raytracer::Camera Builder::parseCamera(void)
    {
        const libconfig::Setting &root = _cfg.getRoot();
        try {
            double width = root["camera"]["ratio"][0];
            double height = root["camera"]["ratio"][1];
            double ratio = width / height;
            return raytracer::Camera(parseVector3D(root["camera"]["lookFrom"]),
                                    parseVector3D(root["camera"]["lookAt"]),
                                    parseVector3D(root["camera"]["up"]), root["camera"]["fov"],
                                    ratio, root["camera"]["aperture"], root["camera"]["focus"], 0, 1);
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found." << std::endl;
        } catch (const libconfig::SettingTypeException &stex) {
            std::cerr << "Setting type mismatch." << std::endl;
        }
        return raytracer::Camera();
    }

    Math::Vector3D Builder::parseVector3D(const libconfig::Setting &setting)
    {
        double x, y, z;

        if (setting.getLength() != 3)
            throw libconfig::SettingTypeException(setting, "Vector3D must have 3 values");
        x = setting[0];
        y = setting[1];
        z = setting[2];
        return Math::Vector3D(x, y, z);
    }

    raytracer::Scene Builder::buildScene(void)
    {
        raytracer::Scene scene;
        buildSphere(scene);
        buildRectangle(scene);
        buildLights(scene);
        buildBox(scene);
        buildCylinder(scene);
        buildCone(scene);
        return scene;
    }

    void Builder::buildCone(raytracer::Scene& scene)
    {
        try {
            const libconfig::Setting &root = _cfg.getRoot();
            const libconfig::Setting &cones = root["primitives"]["cone"];
            raytracer::ShapeFactory factory;
            for (int i = 0; i < cones.getLength(); i++) {
                const libconfig::Setting &cone = cones[i];
                std::shared_ptr<raytracer::IMaterial> material = buildMaterial(cone["material"]);
                std::shared_ptr<raytracer::IShape> shape = factory.createShape("cone", parseVector3D(cone["center"]), cone["angle"], material);
                scene.addObject(shape);
            }
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found (cone)." << std::endl;
        } catch (const libconfig::SettingTypeException &stex) {
            std::cerr << "Setting type mismatch." << std::endl;
        }
    }

    void Builder::buildCylinder(raytracer::Scene &scene)
    {
        try {
            const libconfig::Setting &root = _cfg.getRoot();
            const libconfig::Setting &cylinders = root["primitives"]["limitedCylinder"];
            raytracer::ShapeFactory factory;
            for (int i = 0; i < cylinders.getLength(); i++) {
                const libconfig::Setting &cylinder = cylinders[i];
                std::shared_ptr<raytracer::IMaterial> material = buildMaterial(cylinder["material"]);
                std::shared_ptr<raytracer::IShape> shape = factory.createShape("cylinder", parseVector3D(cylinder["center"]), cylinder["radius"], cylinder["height"], material);
                scene.addObject(shape);
            }
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found (limited cylinder)." << std::endl;
        } catch (const libconfig::SettingTypeException &stex) {
            std::cerr << "Setting type mismatch." << std::endl;
        }
        try {
            const libconfig::Setting &root = _cfg.getRoot();
            const libconfig::Setting &cylinders = root["primitives"]["cylinder"];
            raytracer::ShapeFactory factory;
            for (int i = 0; i < cylinders.getLength(); i++) {
                const libconfig::Setting &cylinder = cylinders[i];
                std::shared_ptr<raytracer::IMaterial> material = buildMaterial(cylinder["material"]);
                std::shared_ptr<raytracer::IShape> shape = factory.createShape("cylinder", parseVector3D(cylinder["center"]), cylinder["radius"], material);
                scene.addObject(shape);
            }
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found (cylinder)." << std::endl;
        } catch (const libconfig::SettingTypeException &stex) {
            std::cerr << "Setting type mismatch." << std::endl;
        }
    }

    void Builder::buildBox(raytracer::Scene &scene)
    {
        try {
            const libconfig::Setting &root = _cfg.getRoot();
            const libconfig::Setting &boxes = root["objects"]["box"];
            raytracer::ShapeFactory factory;
            for (int i = 0; i < boxes.getLength(); i++) {
                const libconfig::Setting &box = boxes[i];
                std::shared_ptr<raytracer::IMaterial> material = buildMaterial(box["material"]);
                std::shared_ptr<raytracer::IShape> shape = factory.createShape("box", parseVector3D(box["max"]), parseVector3D(box["min"]), material);
                scene.addObject(shape);
            }
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found (box)." << std::endl;
        } catch (const libconfig::SettingTypeException &stex) {
            std::cerr << "Setting type mismatch." << std::endl;
        }
    }

    void Builder::buildLights(raytracer::Scene &scene)
    {
        const libconfig::Setting &root = _cfg.getRoot();
        const libconfig::Setting &lights = root["objects"]["directionalLight"];
        raytracer::ShapeFactory factory;

        for (int i = 0; i < lights.getLength(); i++) {
            const libconfig::Setting &light = lights[i];
            std::shared_ptr<raytracer::IMaterial> material = buildMaterial(light["material"]);
            std::string axis = light["axis"];
            double a = light["a"], b = light["b"], c = light["c"], d = light["d"], k = light["k"];
            std::shared_ptr<raytracer::IShape> shape = factory.createShape("light", axis, a, b, c, d, k, material);
            scene.addObject(shape);
        }
    }

    void Builder::buildSphere(raytracer::Scene &scene)
    {
        const libconfig::Setting &root = _cfg.getRoot();
        const libconfig::Setting &spheres = root["primitives"]["sphere"];
        raytracer::ShapeFactory factory;

        for (int i = 0; i < spheres.getLength(); i++) {
            const libconfig::Setting &sphere = spheres[i];
            std::shared_ptr<raytracer::IMaterial> material = buildMaterial(sphere["material"]);
            double radius = sphere["r"];
            std::shared_ptr<raytracer::IShape> shape = factory.createShape("sphere", parseVector3D(sphere["center"]), radius, material);
            scene.addObject(shape);
        }
    }

    void Builder::buildRectangle(raytracer::Scene &scene)
    {
        const libconfig::Setting &root = _cfg.getRoot();
        const libconfig::Setting &rectangles = root["primitives"]["rectangle"];
        raytracer::ShapeFactory factory;

        for (int i = 0; i < rectangles.getLength(); i++) {
            const libconfig::Setting &rect = rectangles[i];
            std::shared_ptr<raytracer::IMaterial> material = buildMaterial(rect["material"]);
            std::string axis = rect["axis"];
            double a = rect["a"], b = rect["b"], c = rect["c"], d = rect["d"], k = rect["k"];
            std::shared_ptr<raytracer::IShape> shape = factory.createShape("rectangle", axis, a, b, c, d, k, material);
            scene.addObject(shape);
        }
    }

    std::shared_ptr<raytracer::IMaterial> Builder::buildMaterial(std::string name)
    {
        const libconfig::Setting &root = _cfg.getRoot();
        const libconfig::Setting &mat = root["material"][name.c_str()];
        raytracer::MaterialFactory factory;
        std::string type = mat["type"];

        if (type == "lambertian") {
            return factory.createMaterial(type, parseVector3D(mat["albedo"]));
        } else if (type == "metal") {
            return factory.createMaterial(type, parseVector3D(mat["albedo"]), mat["fuzz"]);
        } else if (type == "dielectric") {
            return factory.createMaterial(type, mat["refraction"]);
        } else if (type == "diffuseLight") {
            return factory.createMaterial(type, parseVector3D(mat["color"]));
        }
        return nullptr;
    }

    int Builder::getImageHeight(void)
    {
        const libconfig::Setting &root = _cfg.getRoot();
        try {
            return root["image"]["height"];
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found." << std::endl;
        } catch (const libconfig::SettingTypeException &stex) {
            std::cerr << "Setting type mismatch." << std::endl;
        }
        return 0;
    }

    int Builder::getSamplesPerPixel(void)
    {
        const libconfig::Setting &root = _cfg.getRoot();
        try {
            return root["image"]["samples"];
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found." << std::endl;
        } catch (const libconfig::SettingTypeException &stex) {
            std::cerr << "Setting type mismatch." << std::endl;
        }
        return 0;
    }

    int Builder::getMaxDepth(void)
    {
        const libconfig::Setting &root = _cfg.getRoot();
        try {
            return root["image"]["maxDepth"];
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found." << std::endl;
        } catch (const libconfig::SettingTypeException &stex) {
            std::cerr << "Setting type mismatch." << std::endl;
        }
        return 0;
    }
}
