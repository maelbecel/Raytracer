/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Scene
*/

#include "Scene.hpp"
#include "./Object/HittablePDF.hpp"
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
    Math::Color Scene::rayColor(Ray r, const Math::Color &background, std::shared_ptr<Scene> lights, int depth)
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
            return srec.attenuation * rayColor(srec.specular, background, lights, depth - 1);

        std::shared_ptr<IDensity> light = std::make_shared<HittablePDF>(lights, rec.getP());
        Mix p(light, srec.density_ptr);
        Ray scattered = Ray(rec.getP(), p.generate(), r.time());
        auto pdf = p.value(scattered.Direction);

        return emitted + srec.attenuation * rec.getMaterial()->scatter_pdf(r, rec, scattered) * rayColor(scattered, background, lights, depth - 1) / pdf;
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

}
