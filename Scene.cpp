/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Scene
*/

#include "Scene.hpp"

namespace raytracer {
    void Scene::writePixel(std::ofstream &out, Math::Color pixel, int samples)
    {
        auto r = pixel.getX();
        auto g = pixel.getY();
        auto b = pixel.getZ();

        auto scale = 1.0 / samples;
        r = clamp(sqrt(scale * r), 0.0, 0.999);
        g = clamp(sqrt(scale * g), 0.0, 0.999);
        b = clamp(sqrt(scale * b), 0.0, 0.999);

        out.put(static_cast<int>(256 * r));
        out.put(static_cast<int>(256 * g));
        out.put(static_cast<int>(256 * b));
    }

    void Scene::addObject(std::shared_ptr<raytracer::IShape> object)
    {
        _objects.push_back(object);
    }

    std::vector<std::shared_ptr<raytracer::IShape>> Scene::getObjects(void)
    {
        return _objects;
    }


    Math::Color Scene::rayColor(Ray r, int depth)
    {
        HitRecord rec;

        if (depth <= 0)
            return Math::Color(0, 0, 0);
        if (hit(r, 0.001, INFINITY, rec)) {
            Ray scattered;
            Math::Color attenuation;
            if (rec.getMaterial()->scatter(r, rec, attenuation, scattered))
                return attenuation * rayColor(scattered, depth - 1);
            return Math::Color(0, 0, 0);
        }
        Math::Vector3D unitDirection = r.Direction.unit_vector();
        auto t = 0.5 * (unitDirection.getY() + 1.0);
        return (1.0 - t) * Math::Color(1.0, 1.0, 1.0) + t * Math::Color(0.5, 0.7, 1.0);
    }

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
}
