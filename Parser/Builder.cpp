/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Builder
*/

#include "Builder.hpp"

namespace Builder {
    /**
     * The function reads a configuration file and handles any exceptions that may
     * occur during the process.
     *
     * @param path The path parameter is a string that represents the file path of
     * the configuration file that the Builder object will read.
     *
     * @return If an exception is caught, the function will return without doing
     * anything. If no exception is caught, the function will continue executing
     * without returning anything.
     */
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

    /**
     * The function returns the ambient light color from a configuration file.
     *
     * @return a Math::Color object, which is constructed from a Math::Vector3D
     * object that is parsed from a configuration file setting called
     * "ambientLight". If the setting is not found or there is a type mismatch, an
     * error message is printed to the console and a default Math::Vector3D object
     * with values (0, 0, 0) is returned.
     */
    Math::Color Builder::getAmbient(void)
    {
        const libconfig::Setting &root = _cfg.getRoot();
        try {
            return Math::Vector3D(parseVector3D(root["objects"]["ambientLight"]));
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found (ambientLight)." << std::endl;
        } catch (const libconfig::SettingTypeException &stex) {
            std::cerr << "Setting type mismatch." << std::endl;
        }
        return Math::Vector3D(0, 0, 0);
    }

    /**
     * The function returns the background color of an image specified in a
     * configuration file.
     *
     * @return a Math::Color object, which is constructed from a Math::Vector3D
     * object that is parsed from a configuration file setting for the background
     * color of an image. If the setting is not found or there is a type mismatch,
     * an error message is printed to the console and a default black color is
     * returned.
     */
    Math::Color Builder::getBackground(void)
    {
        const libconfig::Setting &root = _cfg.getRoot();
        try {
            return Math::Vector3D(parseVector3D(root["image"]["background"]));
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found (Background)." << std::endl;
        } catch (const libconfig::SettingTypeException &stex) {
            std::cerr << "Setting type mismatch." << std::endl;
        }
        return Math::Vector3D(0, 0, 0);
    }

    fileType_e Builder::getFileType(void)
    {
        const libconfig::Setting &root = _cfg.getRoot();
        try {
            std::string name = root["image"]["type"];
            if      (name == "ppm") return PPM;
            else if (name == "gif") return GIF;
            else                    return PPM;
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found (Image type)." << std::endl;
        } catch (const libconfig::SettingTypeException &stex) {
            std::cerr << "Setting type mismatch." << std::endl;
        }
        return PPM;
    }

    /**
     * The function parses camera settings from a configuration file and returns a
     * camera object.
     *
     * @return The function `parseCamera` returns a `raytracer::Camera` object. If
     * there is an exception caught, it returns a default-constructed
     * `raytracer::Camera` object.
     */
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

    /**
     * The function parses a libconfig Setting object and returns a Math::Vector3D
     * object with its x, y, and z values.
     *
     * @param setting `setting` is a reference to a `libconfig::Setting` object,
     * which is a node in a configuration file. It is used to retrieve the values
     * of a Vector3D object in the configuration file.
     *
     * @return The function `parseVector3D` is returning a `Math::Vector3D` object
     * with the x, y, and z values parsed from the `libconfig::Setting` object
     * passed as a parameter.
     */
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

    /**
     * The function builds a raytracer scene by adding various objects and lights
     * to it.
     *
     * @return The function `buildScene` is returning an object of type
     * `raytracer::Scene`.
     */
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

    /**
     * The function builds cone shapes with specified materials and adds them to a
     * scene.
     *
     * @param scene The `scene` parameter is a reference to a `raytracer::Scene`
     * object, which represents the 3D scene being rendered by the raytracer. The
     * `buildCone` function adds cone objects to this scene.
     */
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

    /**
     * The function builds cylinder shapes with specified materials and dimensions
     * and adds them to a scene.
     *
     * @param scene The `scene` parameter is a reference to a `raytracer::Scene`
     * object, which is where the created objects will be added to.
     */
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

    /**
     * This function builds a box object in a raytracer scene using settings from
     * a configuration file.
     *
     * @param scene A reference to a raytracer::Scene object, which represents the
     * scene being built.
     */
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

    /**
     * The function builds directional lights for a raytracer scene using settings
     * from a configuration file.
     *
     * @param scene A reference to a raytracer::Scene object that will be modified
     * by adding new objects to it.
     */
    void Builder::buildLights(raytracer::Scene &scene)
    {
        try {
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
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found (lights)." << std::endl;
        } catch (const libconfig::SettingTypeException &stex) {
            std::cerr << "Setting type mismatch." << std::endl;
        }
    }

    /**
     * This function builds spheres with specified materials and adds them to a
     * scene.
     *
     * @param scene A reference to a raytracer::Scene object, which represents the
     * scene being built.
     */
    void Builder::buildSphere(raytracer::Scene &scene)
    {
        try {
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
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found (Sphere)." << std::endl;
        } catch (const libconfig::SettingTypeException &stex) {
            std::cerr << "Setting type mismatch." << std::endl;
        }
    }

    /**
     * The function builds rectangles with specified dimensions and materials and
     * adds them to a scene.
     *
     * @param scene A reference to a raytracer::Scene object, which represents the
     * scene being built.
     */
    void Builder::buildRectangle(raytracer::Scene &scene)
    {
        try {
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
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found (Rectangle)." << std::endl;
        } catch (const libconfig::SettingTypeException &stex) {
            std::cerr << "Setting type mismatch." << std::endl;
        }
    }

    /**
     * The function builds a material object based on the type and properties
     * specified in a configuration file.
     *
     * @param name The name of the material to be built, as specified in the
     * configuration file.
     *
     * @return A `std::shared_ptr` to an object of type `raytracer::IMaterial`.
     * The specific type of material being returned depends on the value of the
     * `type` variable and the corresponding `if` statement that is executed. If
     * none of the `if` statements match, then a `nullptr` is returned.
     */
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

    /**
     * This function retrieves the height of an image from a configuration file
     * using the libconfig library in C++.
     *
     * @return an integer value which represents the height of an image. However,
     * if the height setting is not found or if there is a type mismatch, the
     * function will return 0.
     */
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

    /**
     * This function retrieves the number of samples per pixel from a
     * configuration file.
     *
     * @return an integer value which represents the number of samples per pixel.
     * If the value is not found or there is a type mismatch, the function returns
     * 0.
     */
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

    /**
     * This function retrieves the maximum depth value from a configuration file.
     *
     * @return an integer value which represents the maximum depth of an image. If
     * the value is not found or there is a type mismatch, the function returns 0.
     */
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
