/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Scene
*/

#include "Scene.hpp"
#include "./Object/HittablePDF.hpp"
#include "./Shapes/Translation.hpp"
#include "./Shapes/XRotation.hpp"
#include "./Shapes/YRotation.hpp"
#include "./Shapes/ZRotation.hpp"
#include "./Parser/Builder.hpp"
#include "./Preview/Loading.hpp"
#include "./Preview/Preview.hpp"
#include "GifCreator.hpp"
#include "CommandRunner.hpp"
#include <exception>

namespace raytracer {
    /**
     * The function writes a pixel color to a file with a specified number of
     * samples and applies gamma correction.
     *
     * @param out The output file stream to write the pixel color to.
     * @param pixel A Math::Color object representing the color of a pixel in the
     * image being rendered.
     * @param samples The number of samples taken to compute the color of a pixel.
     * This is used to calculate the final color of the pixel by averaging the
     * colors of all the samples taken.
     */
    void Scene::writePixel(std::ofstream &out, Math::Color pixel, int samples)
    {
        auto r = pixel.getX();
        auto g = pixel.getY();
        auto b = pixel.getZ();

        r = ( r != r) ? 0 : r;
        g = ( g != g) ? 0 : g;
        b = ( b != b) ? 0 : b;

        auto scale = 1.0 / samples;
        r = CLAMP(sqrt(scale * r), 0.0, 0.999);
        g = CLAMP(sqrt(scale * g), 0.0, 0.999);
        b = CLAMP(sqrt(scale * b), 0.0, 0.999);

        out.put(static_cast<int>(256 * r));
        out.put(static_cast<int>(256 * g));
        out.put(static_cast<int>(256 * b));
    }

    /**
     * The function writes a pixel color to a buffer with a specified number of
     * samples and applies gamma correction.
     *
     * @param buffer A reference to a string that will store the pixel data in the
     * form of RGB values.
     * @param pixel A Math::Color object representing the color of a pixel in the
     * scene.
     * @param samples The number of samples taken for each pixel to calculate the
     * final color value. This is used to scale the color values before writing
     * them to the output buffer.
     */
    void Scene::writePixel(std::string &buffer, Math::Color pixel, int samples)
    {
        auto r = pixel.getX();
        auto g = pixel.getY();
        auto b = pixel.getZ();

        r = ( r != r) ? 0 : r;
        g = ( g != g) ? 0 : g;
        b = ( b != b) ? 0 : b;

        auto scale = 1.0 / samples;
        r = CLAMP(sqrt(scale * r), 0.0, 0.999);
        g = CLAMP(sqrt(scale * g), 0.0, 0.999);
        b = CLAMP(sqrt(scale * b), 0.0, 0.999);

        buffer += static_cast<char>(256 * r);
        buffer += static_cast<char>(256 * g);
        buffer += static_cast<char>(256 * b);
    }

    /**
     * The function adds a non-null object to a vector of shared pointers to
     * IShape.
     *
     * @param object The parameter "object" is a shared pointer to an object that
     * implements the "IShape" interface. This function is a member function of
     * the "Scene" class and is used to add an object to the list of objects in
     * the scene. If the object is null, an error message is printed
     */
    void Scene::addObject(std::shared_ptr<raytracer::IShape> object)
    {
        if (object == nullptr)
            std::cerr << "cannot add nullptr object" << std::endl;
        else
            _objects.push_back(object);
    }

    /**
     * The function adds a shape object to a scene with specified rotations around
     * the x, y, and z axes.
     *
     * @param object A shared pointer to an object that implements the IShape
     * interface. This object represents a geometric shape that can be added to
     * the scene.
     * @param r r is a Math::Vector3D object that represents the rotation angles
     * around the x, y, and z axes, respectively. The function adds the given
     * object to the scene with the specified rotation angles. If any of the
     * rotation angles are zero, no rotation is applied around that axis. If all
     *
     * @return The function does not return anything. It has a void return type.
     */
    void Scene::addObjectRotated(std::shared_ptr<raytracer::IShape> object, Math::Vector3D r)
    {
        if (object == nullptr) {
            std::cerr << "cannot add nullptr object" << std::endl;
            return;
        }
        auto obj = object;
        if (r.getX() != 0)
            obj = std::make_shared<XRotation>(obj, r.getX());
        if (r.getY() != 0)
            obj = std::make_shared<YRotation>(obj, r.getY());
        if (r.getZ() != 0)
            obj = std::make_shared<ZRotation>(obj, r.getZ());

        _objects.push_back(obj);
    }

    /**
     * The function returns a vector of shared pointers to objects in a scene.
     *
     * @return A `std::vector` of `std::shared_ptr` objects that implement the
     * `raytracer::IShape` interface.
     */
    std::vector<std::shared_ptr<raytracer::IShape>> Scene::getObjects(void) const
    {
        return _objects;
    }

    /**
     * The function calculates the color of a ray in a scene by recursively
     * tracing the path of the ray and accounting for material properties and
     * lighting.
     *
     * @param r The ray being traced in the scene.
     * @param background The background color to be used if the ray does not hit
     * any objects in the scene.
     * @param lights `lights` is a shared pointer to a `Scene` object that
     * contains all the light sources in the scene. It is used to calculate the
     * contribution of the lights to the final color of the object being rendered.
     * @param depth The maximum recursion depth for ray tracing. It determines how
     * many times the ray tracing algorithm will bounce a ray off surfaces before
     * terminating.
     *
     * @return a Math::Color value, which represents the color of the ray after it
     * has interacted with objects in the scene.
     */
    Math::Color Scene::rayColor(Ray r, const Math::Color &background, std::shared_ptr<Scene> lights, int depth, Math::Color ambiant)
    {
        HitRecord rec;

        if (depth <= 0)
            return Math::Color(0, 0, 0);
        if (!hit(r, 0.001, INFINITY, rec))
            return background;

        ScatterRecord srec;
        Math::Color emitted = rec.getMaterial()->emitted(r, rec.getU(), rec.getV(), rec, rec.getP());

        if (!rec.getMaterial()->scatter(r, rec, srec))
            return emitted;

        if (srec.is_specular)
            return srec.attenuation * rayColor(srec.specular, background, lights, depth - 1, ambiant);

        std::shared_ptr<IDensity> light = std::make_shared<HittablePDF>(lights, rec.getP());
        Mix p(light, srec.density_ptr);
        Ray scattered = Ray(rec.getP(), p.generate(), r.time());
        auto pdf = p.value(scattered.Direction);
        // std::cerr << "[" << depth << "] At = " << srec.attenuation << "\tPdf = "<< pdf << "\tscat = " << rec.getMaterial()->scatter_pdf(r, rec, scattered) << std::endl;

        //auto x = emitted + srec.attenuation * rec.getMaterial()->scatter_pdf(r, rec, scattered) * rayColor(scattered, background, lights, depth - 1, ambiant) / pdf;
        auto x = emitted + srec.attenuation * rec.getMaterial()->scatter_pdf(r, rec, scattered) * rayColor(scattered, background, lights, depth - 1, ambiant) / pdf;
        // auto x = emitted + srec.attenuation * rec.getMaterial()->scatter_pdf(r, rec, scattered) * rayColor(scattered, background, lights, depth - 1, ambiant) / pdf;
        // std::cerr << "[" << depth << "]" << emitted << " + " << srec.attenuation << " * "<< rayColor(scattered, background, lights, depth - 1, ambiant)<< " / " << pdf << " = " << x << std::endl;
        // std::cerr << "[" << depth << "]" << emitted << " + " << srec.attenuation << " * "<< rec.getMaterial()->scatter_pdf(r, rec, scattered)<< " * "<<rayColor(scattered, background, lights, depth - 1, ambiant)<< " / " << pdf << " = " << x << std::endl;
        return x;
    }

    /**
     * The function calculates the color of a ray in a scene by recursively
     * tracing the path of the ray and accounting for material properties and
     * lighting.
     *
     * @param r The ray being traced in the scene.
     * @param background The background color to be used if the ray does not hit
     * any objects in the scene.
     * @param lights `lights` is a shared pointer to a `Scene` object that
     * contains all the light sources in the scene. It is used to calculate the
     * contribution of the lights to the final color of the object being rendered.
     * @param depth The maximum recursion depth for ray tracing. It determines how
     * many times the ray tracing algorithm will bounce a ray off surfaces before
     * terminating.
     *
     * @return a Math::Color value, which represents the color of the ray after it
     * has interacted with objects in the scene.
     */
    Math::Color Scene::previewRayColor(Ray r, const Math::Color &background, std::shared_ptr<Scene> lights, int depth, Math::Color ambiant)
    {
        HitRecord rec;

        if (depth <= 0)
            return Math::Color(0, 0, 0);
        if (!hit(r, 0.001, INFINITY, rec))
            return background;

        ScatterRecord srec;
        Math::Color emitted = rec.getMaterial()->emitted(r, rec.getU(), rec.getV(), rec, rec.getP());

        if (!rec.getMaterial()->scatter(r, rec, srec))
            return emitted;

        if (srec.is_specular)
            return srec.attenuation * rayColor(srec.specular, background, lights, depth - 1, ambiant);

        std::shared_ptr<IDensity> light = std::make_shared<HittablePDF>(lights, rec.getP());
        Mix p(light, srec.density_ptr);
        Ray scattered = Ray(rec.getP(), p.generate(), r.time());

        auto x = emitted + srec.attenuation * rec.getMaterial()->scatter_pdf(r, rec, scattered);
        return x;
    }

    /**
     * This function checks if a ray intersects with any objects in a scene and
     * returns the closest intersection.
     *
     * @param r The Ray object that is being tested for intersection with the
     * objects in the scene.
     * @param min The minimum distance along the ray that the intersection can
     * occur. Any intersection closer than this distance will be ignored.
     * @param max The maximum distance along the ray at which an intersection can
     * occur. Any intersection beyond this distance will be ignored.
     * @param rec `rec` is a reference to a `HitRecord` object that will be
     * updated with information about the closest object that the ray `r`
     * intersects with in the scene. This information includes the point of
     * intersection, the normal at the point of intersection, the material of the
     * object, and the distance
     *
     * @return The function `hit` is returning a boolean value indicating whether
     * or not the input ray intersects with any objects in the scene.
     */
    bool Scene::hit(const Ray &r, double min, double max, HitRecord &rec)
    {
        HitRecord tempRec;
        bool hitAnything = false;
        auto closestSoFar = max;

        for (auto object : _objects) {
            if (object->hit(r, min, closestSoFar, tempRec)) {
                hitAnything = true;
                closestSoFar = tempRec.getT();
                rec = tempRec;
            }
        }
        return hitAnything;
    }

    /**
     * This function calculates the bounding box of a scene by iterating through
     * all objects in the scene and computing their individual bounding boxes.
     *
     * @param time0 The start time of the animation or simulation for which the
     * bounding box is being calculated.
     * @param time1 time1 is a double value representing the end time of the
     * scene's animation. It is used in the bounding_box function to calculate the
     * bounding box of the scene's objects over a specific time interval, from
     * time0 to time1.
     * @param output `output` is a reference to an `AABB` (axis-aligned bounding
     * box) object that will be modified by the function to contain the bounding
     * box of the scene. The function will calculate the bounding box of all
     * objects in the scene and modify `output` to contain the minimum and maximum
     * coordinates
     *
     * @return a boolean value. It returns true if the bounding box of the scene
     * can be computed successfully, and false otherwise.
     */
    bool Scene::bounding_box(double time0, double time1, AABB &output) const
    {
        if (_objects.empty())
            return false;

        AABB tempBox;
        bool firstBox = true;

        for (const auto& object : _objects) {
            if (!object->bounding_box(time0, time1, tempBox))
                return false;
            if (firstBox)
                output = tempBox;
            else
                output = output.surrounding_box(tempBox);
            firstBox = false;
        }
        return true;
    }

    /**
     * This function calculates the density value of a scene by summing up the
     * density values of all objects in the scene.
     *
     * @param o o is a 3D vector representing the origin point of a ray in the
     * scene. It is the starting point from which the ray is cast.
     * @param v The parameter `v` is a `Math::Vector3D` representing the direction
     * of the ray being traced in the scene.
     *
     * @return The function `densityValue` returns a `double` value which is the
     * sum of the density values of all objects in the scene, weighted by the
     * inverse of the number of objects in the scene.
     */
    double Scene::densityValue(const Math::Vector3D &o, const Math::Vector3D &v) const
    {
        auto weight = 1.0 / _objects.size();
        auto sum = 0.0;

        for (const auto& object : _objects)
            sum += weight * object->densityValue(o, v);

        return sum;
    }

    /**
     * The function returns a random Vector3D object from a list of objects in a
     * scene.
     *
     * @param o The parameter "o" is a constant reference to a Math::Vector3D
     * object, which represents the origin point of the scene. It is used as a
     * parameter for the "random" function of one of the objects in the scene,
     * which returns a random point on the surface of that object.
     *
     * @return A random point in the scene, represented as a 3D vector, based on a
     * randomly selected object in the scene and a given origin point.
     */
    Math::Vector3D Scene::random(const Math::Vector3D &o) const
    {
        auto int_size = static_cast<int>(_objects.size());
        auto index = static_cast<int>(random_double_mm(0, int_size - 1));
        return _objects[index]->random(o);
    }

    /**
     * The function generates a preview of a rendered scene using ray tracing.
     *
     * @param parser A reference to a Builder object used to parse the scene file
     * and extract relevant information such as camera settings, image dimensions,
     * and rendering options.
     * @param lights The `lights` parameter is an instance of the `Scene` class,
     * which represents the scene containing all the objects and lights in the
     * scene being rendered. It is passed as a shared pointer to the `rayColor`
     * function to calculate the color of each pixel.
     * @param quality The quality parameter is used to determine the level of
     * detail in the preview image. It specifies the number of pixels that are
     * skipped between each pixel that is actually rendered. A higher quality
     * value will result in a lower resolution preview image, but will also render
     * faster.
     * @param ambiant The ambiant parameter is a Math::Color object that
     * represents the ambient light in the scene. It is used in the rayColor
     * function to calculate the color of a pixel based on the ambient light in
     * the scene.
     */
    void Scene::loadingRenderer(Builder::Builder &parser, Scene lights, Math::Color ambiant)
    {
        raytracer::Camera cam = parser.parseCamera();
        const int image_height = parser.getImageHeight();
        const int image_width = parser.getImageHeight() * cam.getRatio();
        const int samples_per_pixel = parser.getSamplesPerPixel();
        const int depth = parser.getMaxDepth();
        Math::Vector3D background = parser.getBackground();

        Loading loading(image_width, image_height);

        std::ofstream _file("Rendu.ppm", std::ios::binary);

        _file << "P6\n" << image_width << ' ' << image_height << "\n255\n";
        for (int j = image_height-1; j >= 0; j--) {
            std::cerr << "\rScanlines remaining: " << image_height - j - 1 << " / " << image_height << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                Math::Color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s) {
                    auto u = (i + random_double()) / (image_width-1);
                    auto v = (j + random_double()) / (image_height-1);
                    raytracer::Ray r = cam.getRay(u, v);
                    pixel_color += rayColor(r, background, std::make_shared<raytracer::Scene>(lights), depth, ambiant);
                }
                writePixel(_file, pixel_color, samples_per_pixel);
                if (!loading.addPixel(pixel_color, i, image_height - j - 1, samples_per_pixel))
                    return;
            }
        }
        std::cerr << "\nDone.\n";
    }

    /**
     * The function generates a preview of a rendered scene using ray tracing.
     *
     * @param parser A reference to a Builder object used to parse the scene file
     * and extract relevant information such as camera settings, image dimensions,
     * and rendering options.
     * @param lights The `lights` parameter is an instance of the `Scene` class,
     * which represents the scene containing all the objects and lights in the
     * scene being rendered. It is passed as a shared pointer to the `rayColor`
     * function to calculate the color of each pixel.
     * @param quality The quality parameter is used to determine the level of
     * detail in the preview image. It specifies the number of pixels that are
     * skipped between each pixel that is actually rendered. A higher quality
     * value will result in a lower resolution preview image, but will also render
     * faster.
     * @param ambiant The ambiant parameter is a Math::Color object that
     * represents the ambient light in the scene. It is used in the rayColor
     * function to calculate the color of a pixel based on the ambient light in
     * the scene.
     */
    bool Scene::previewRenderer(Builder::Builder &parser, Scene lights, Math::Color ambiant)
    {
        raytracer::Camera cam = parser.parseCamera();
        const int image_height = parser.getImageHeight();
        const int image_width = parser.getImageHeight() * cam.getRatio();
        const int samples_per_pixel = 5;
        const int depth = 5;
        Math::Vector3D background = parser.getBackground();

        Preview preview(image_width, image_height);

        for (int j = image_height-1; j >= 0; j--) {
            for (int i = 0; i < image_width; i++) {
                Math::Color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s) {
                    auto u = (i + random_double()) / (image_width-1);
                    auto v = (j + random_double()) / (image_height-1);
                    raytracer::Ray r = cam.getRay(u, v);
                    pixel_color += previewRayColor(r, background, std::make_shared<raytracer::Scene>(lights), depth, ambiant);
                }
                preview.addPixel(pixel_color, i, image_height - j - 1, samples_per_pixel);
            }
        }
        preview.display();
        return (preview.accept);
    }

    /**
     * The function ppmRendererRoutine renders a scene using multi-threading and
     * writes the pixel colors to a buffer.
     *
     * @param parser A reference to a Builder object used to parse the scene file
     * and extract relevant information such as camera settings, image dimensions,
     * and maximum recursion depth.
     * @param lights The "lights" parameter is a Scene object that contains
     * information about the lights in the scene, such as their positions, colors,
     * and intensities. This information is used to calculate the lighting and
     * shading of objects in the scene.
     * @param id id is an integer representing the thread ID or index. It is used
     * to divide the image into equal parts for parallel processing.
     * @param buffer The "buffer" parameter is a reference to a vector of strings
     * that will store the rendered image data. Each string in the vector
     * represents a row of pixels in the image. The function will write the color
     * data for each pixel to the appropriate string in the vector.
     * @param scene The scene parameter is a reference to a Scene object, which
     * contains all the objects and lights in the scene that will be rendered.
     * @param ambient The ambient parameter is a Math::Color object representing
     * the ambient light in the scene. It is used in the rayColor function to
     * calculate the color of a pixel based on the ambient light in the scene.
     */
    void ppmRendererRoutine(Builder::Builder &parser, Scene lights, int id, std::vector<std::string> &buffer, Scene &scene, Math::Color ambient)
    {
        raytracer::Camera cam = parser.parseCamera();
        const int image_height = parser.getImageHeight();
        const int image_width = parser.getImageHeight() * cam.getRatio();
        const int samples_per_pixel = parser.getSamplesPerPixel();
        const int numThreads = std::thread::hardware_concurrency();
        int start = id * (image_height / numThreads);
        int end = (id + 1) * (image_height / numThreads);
        int depth = parser.getMaxDepth();
        Math::Vector3D background = parser.getBackground();

        std::cout << "Thread " << id << " : " << start << " - " << end << std::endl;
        for (int j = start; j <= end; j++) {
            for (int i = 0; i < image_width; ++i) {
                Math::Color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s) {
                    auto u = (i + random_double()) / (image_width-1);
                    auto v = (j + random_double()) / (image_height-1);
                    raytracer::Ray r = cam.getRay(u, v);
                    pixel_color += scene.rayColor(r, background, std::make_shared<raytracer::Scene>(lights), depth, ambient);
                }
                raytracer::Scene::writePixel(buffer[j], pixel_color, samples_per_pixel);
            }
        }
        std::cout << "Thread " << id << " done." << std::endl;
    }

    /**
     * The function `ppmRenderer` renders a scene using the PPM image format and
     * writes it to a file.
     *
     * @param parser An instance of the Builder class used to parse the scene file
     * and extract relevant information such as camera position, image dimensions,
     * and maximum depth for ray tracing.
     * @param lights The `lights` parameter is an instance of the `Scene` class,
     * which represents the scene containing all the objects and lights in the
     * scene being rendered. It is used to compute the lighting and shading of the
     * objects in the scene.
     * @param ambiant The ambient color of the scene.
     */
    void Scene::ppmRenderer(Builder::Builder &parser, Scene lights, Math::Color ambiant)
    {
        raytracer::Camera cam = parser.parseCamera();
        const int image_height = parser.getImageHeight();
        const int image_width = parser.getImageHeight() * cam.getRatio();
        const int samples_per_pixel = parser.getSamplesPerPixel();
        const int depth = parser.getMaxDepth();
        Math::Vector3D background = parser.getBackground();

        auto light = std::make_shared<raytracer::DiffuseLight>(ambiant);
        addObject(std::make_shared<raytracer::Sphere>(cam.getPos() + cam.getDirection() * -1, 99, light));

        std::cerr << "Light at " << cam.getPos() + cam.getDirection() * - 1 << " from " << cam.getPos() << " and dir " << cam.getDirection() <<  std::endl;

        std::ofstream _file("Rendu.ppm", std::ios::binary);

        _file << "P6\n" << image_width << ' ' << image_height << "\n255\n";
        for (int j = image_height-1; j >= 0; --j) {
            std::cerr << "\rScanlines remaining: " << image_height - j - 1 << " / " << image_height << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                Math::Color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s) {
                    auto u = (i + random_double()) / (image_width-1);
                    auto v = (j + random_double()) / (image_height-1);
                    raytracer::Ray r = cam.getRay(u, v);
                    auto p = rayColor(r, background, std::make_shared<raytracer::Scene>(lights), depth, ambiant);
                    //std::cerr << "============================================================================\n[" << i << "][" << j << "] p = " << p << "\tpixel = "<< pixel_color << "\n=======================================================================================" << std::endl;
                    pixel_color += p;
                }
                raytracer::Scene::writePixel(_file, pixel_color, samples_per_pixel);
            }
        }
        std::cerr << "\nDone.\n";
        _file.close();
    }

    void Scene::multithreadingRenderer(Builder::Builder &parser, Scene lights, Math::Color ambiant)
    {
        raytracer::Camera cam = parser.parseCamera();
        const int image_height = parser.getImageHeight();
        const int image_width = parser.getImageHeight() * cam.getRatio();

        auto light = std::make_shared<raytracer::DiffuseLight>(ambiant);
        addObject(std::make_shared<raytracer::Sphere>(cam.getPos() + cam.getDirection() * -1, 99, light));

        std::cerr << "Light at " << cam.getPos() + cam.getDirection() * - 1 << " from " << cam.getPos() << " and dir " << cam.getDirection() <<  std::endl;
        const int numThreads = std::thread::hardware_concurrency();
        std::vector<std::thread> threads;
        std::vector<std::string> lines(image_height);

        std::ofstream _file("Rendu.ppm", std::ios::binary);

        _file << "P6\n" << image_width << ' ' << image_height << "\n255\n";
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back(ppmRendererRoutine, std::ref(parser), lights, i, std::ref(lines), std::ref(*this), ambiant);
        }

        for (auto &thread : threads) {
            thread.join();
        }

        for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
            _file << *it;
        }

        std::cerr << "\nDone.\n";
        _file.close();
    }

    /**
     * The function applies a movement to a list of shapes based on a vector of
     * moves and a frame number.
     *
     * @param list A vector of shared pointers to objects that implement the
     * IShape interface. These objects represent the shapes that will be moved in
     * the scene.
     * @param moves moves is a vector of Math::Vector3D objects representing the
     * amount of movement to apply to each shape in the list. The movement is
     * multiplied by the frame parameter to determine the total amount of movement
     * to apply.
     * @param frame The parameter "frame" represents the current frame of the
     * animation. It is used to calculate the amount of movement to apply to each
     * shape in the list based on the corresponding vector in the "moves" vector.
     *
     * @return a new instance of the Scene class with objects that have been
     * translated according to the moves vector and the current frame.
     */
    Scene Scene::applyMovement(std::vector<std::shared_ptr<IShape>> list, std::vector<Math::Vector3D> moves, int frame)
    {
        Scene scene;
        for (size_t i = 0; i < list.size() && i < moves.size(); i++)
        {
            scene.addObject(std::make_shared<Translation>(list[i], moves[i] * frame));
        }
        return scene;
    }

    /**
     * The function applies rotations to a list of shapes and returns a new scene
     * with the rotated shapes.
     *
     * @param list A vector of shared pointers to objects that implement the
     * IShape interface. These objects represent the shapes that will be rotated.
     * @param rotations The `rotations` parameter is a vector of `Math::Vector3D`
     * objects that represent the rotation angles to be applied to each shape in
     * the `list` vector. The `x` component of the vector represents the rotation
     * angle around the x-axis, the `y` component represents the
     * @param frame The "frame" parameter is an integer value that represents the
     * current frame of an animation. It is used to calculate the amount of
     * rotation to apply to each shape in the "list" parameter based on the
     * corresponding rotation vector in the "rotations" parameter.
     *
     * @return a `Scene` object.
     */
    Scene Scene::applyRotation(std::vector<std::shared_ptr<IShape>> list, std::vector<Math::Vector3D> rotations, int frame)
    {
        Scene scene;
        for (size_t i = 0; i < list.size() && i < rotations.size(); i++)
        {
            scene.addObject(std::make_shared<XRotation>(std::make_shared<YRotation>(std::make_shared<ZRotation>(list[i], rotations[i].getZ() * frame), rotations[i].getY() * frame), rotations[i].getX() * frame));
        }
        return scene;
    }

    /**
     * The function `gifRenderer` renders a scene as a GIF animation by applying
     * movement and rotation to objects and using ray tracing to generate pixel
     * colors.
     *
     * @param parser An instance of the Builder class used to parse the scene
     * description file and extract relevant information such as camera settings,
     * image dimensions, samples per pixel, and maximum recursion depth.
     * @param lights The `lights` parameter is an instance of the `Scene` class,
     * which represents the scene containing all the light sources in the scene
     * being rendered.
     * @param ambiant The ambient color of the scene.
     */
    void Scene::gifRenderer(Builder::Builder &parser, Scene lights, Math::Color ambiant)
    {
        raytracer::Camera cam = parser.parseCamera();
        const int image_height = parser.getImageHeight();
        const int image_width = parser.getImageHeight() * cam.getRatio();
        const int samples_per_pixel = parser.getSamplesPerPixel();
        const int depth = parser.getMaxDepth();
        Math::Vector3D background = parser.getBackground();

        if (!CommandRunner::isCommandExist("convert"))
            throw CommandRunner::RunError::CommandNotFound("convert");
        std::vector<Math::Vector3D> moves = parser.getMovements();
        std::vector<Math::Vector3D> rotation = parser.getRotations();
        for (; moves.size() < this->getObjects().size() ;)
            moves.push_back(Math::Vector3D(0, 0, 0));

        for (; rotation.size() < this->getObjects().size() ;)
            rotation.push_back(Math::Vector3D(0, 0, 0));


        std::vector<std::string> ppm_buffer;
        int fps = parser.getFPS();
        int time = parser.getTime();
        auto glass = std::make_shared<raytracer::Dielectric>(1.5);

        for (int i = 0; i < fps * time; i++) {
            std::string file;
            file += "P6\n";
            file += std::to_string(image_width) + ' ';
            file += std::to_string(image_height) + "\n255\n";
            Scene render = applyMovement(getObjects(), moves, i);
            render = applyRotation(render.getObjects(), rotation, i);
            for (int j = image_height-1; j >= 0; --j) {
                std::cerr << "\rScanlines remaining: " << image_height - j - 1 << " / " << image_height << " [" << i << " / " << time * fps << "]" <<' ' << std::flush;
                for (int i = 0; i < image_width; ++i) {
                    Math::Color pixel_color(0, 0, 0);
                    for (int s = 0; s < samples_per_pixel; ++s) {
                        auto u = (i + random_double()) / (image_width-1);
                        auto v = (j + random_double()) / (image_height-1);
                        raytracer::Ray r = cam.getRay(u, v);
                        pixel_color += render.rayColor(r, background, std::make_shared<raytracer::Scene>(lights), depth, ambiant);
                    }
                    raytracer::Scene::writePixel(file, pixel_color, samples_per_pixel);
                }
            }
            ppm_buffer.push_back(file);
        }
        raytracer::GifCreator::createGif("Rendu.gif", ppm_buffer, fps);
    }

}
