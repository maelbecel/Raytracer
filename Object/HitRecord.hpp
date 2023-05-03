/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** HitRecord
*/

#ifndef HITRECORD_HPP_
    #define HITRECORD_HPP_

    #include "../Maths/Vector3D.hpp"
    #include "../Ray.hpp"
    #include <memory>

    namespace raytracer {
        class IMaterial;
        class HitRecord {
            public:
                HitRecord() {};
                HitRecord(
                    const Math::Vector3D &p,
                    const Math::Vector3D &normal,
                    double t,
                    bool front_face,
                    std::shared_ptr<IMaterial> material
                ) : p(p), normal(normal), t(t), front_face(front_face), material(material) {}

                ~HitRecord() {};
                double getT() const { return t; };
                double getU() const { return u; };
                double getV() const { return v; };
                Math::Vector3D getP() const { return p; };
                Math::Vector3D getNormal() const { return normal; };
                bool isFrontFace() const { return front_face; };
                std::shared_ptr<IMaterial> getMaterial() const { return material; };
                void setT(double t) { this->t = t; };
                void setP(Math::Vector3D p) { this->p = p; };
                void setNormal(Math::Vector3D normal) { this->normal = normal; };
                void setFrontFace(bool front_face) { this->front_face = front_face; };
                void setMaterial(std::shared_ptr<IMaterial> material) { this->material = material; };

                void setFaceNormal(const Ray &, const Math::Vector3D &);
                double u, v;
            private:
                Math::Vector3D p;
                Math::Vector3D normal;
                double t;
                bool front_face;
                std::shared_ptr<IMaterial> material = nullptr;
        };
    }

#endif /* !HITRECORD_HPP_ */
