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
        r = CLAMP(sqrt(scale * r), 0.0, 0.999);
        g = CLAMP(sqrt(scale * g), 0.0, 0.999);
        b = CLAMP(sqrt(scale * b), 0.0, 0.999);

        out.put(static_cast<int>(256 * r));
        out.put(static_cast<int>(256 * g));
        out.put(static_cast<int>(256 * b));
    }

    void Scene::addObject(std::shared_ptr<raytracer::IShape> object)
    {
        _objects.push_back(object);
    }

    std::vector<std::shared_ptr<raytracer::IShape>> Scene::getObjects(void) const
    {
        return _objects;
    }

    Math::Color Scene::rayColor(Ray r, const Math::Color &background, std::shared_ptr<IShape> &lights, int depth)
    {
        HitRecord rec;

        if (depth <= 0)
            return Math::Color(0, 0, 0);
        if (!hit(r, 0.001, INFINITY, rec))
            return background;

        Ray scattered;
        Math::Color attenuation;
        Math::Color emitted = rec.getMaterial()->emitted(rec.getU(), rec.getV(), rec, rec.getP());
        double pdf;
        Math::Color albedo;

        if (!rec.getMaterial()->scatter(r, rec, albedo, scattered, pdf))
            return emitted;

        auto p0 = std::make_shared<raytracer::HittablePDF>(lights, rec.getP());
        auto p1 = std::make_shared<raytracer::Cosine>(rec.getNormal());
        raytracer::Mix mixed(p0, p1);

        scattered = Ray(rec.getP(), mixed.generate(), r.time());
        pdf = mixed.value(scattered.Direction);
        return emitted + albedo * rec.getMaterial()->scatter_pdf(r, rec, scattered) * rayColor(scattered, background, lights, depth - 1) / pdf;
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
}
