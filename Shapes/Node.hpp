/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Node
*/

#ifndef NODE_HPP_
    #define NODE_HPP_

    #include "IShape.hpp"
    #include "../Scene.hpp"
    #include <algorithm>

    #define random_int(min, max) static_cast<int>(random_double_mm(min, max+1))


    namespace raytracer {
        class Node : public IShape {
            public:
                Node() {};
                Node(const Scene &scene, double time0, double time1)
                    : Node(scene.getObjects(), 0, scene.getObjects().size(), time0, time1) {}
                Node(const std::vector<std::shared_ptr<IShape>>& objects, size_t start, size_t end, double time0, double time1);

                virtual bool hit(const Ray &r, double min, double max, HitRecord &rec) const override
                {
                    if (!box.hit(r, min, max))
                        return false;
                    bool hit_left = left->hit(r, min, max, rec);
                    bool hit_right = right->hit(r, min, hit_left ? rec.getT() : max, rec);
                    return hit_left || hit_right;
                }

                virtual bool bounding_box(UNUSED double time0, UNUSED double time1, raytracer::AABB& output_box) const override
                {
                    output_box = box;
                    return true;
                }

                virtual double densityValue(UNUSED const Math::Vector3D &o, UNUSED const Math::Vector3D &v) const override {return 0;};
                virtual Math::Vector3D random(UNUSED const Math::Vector3D & o) const override {return Math::Vector3D(1, 0, 0);};

            protected:
            private:
                std::shared_ptr<IShape> left;
                std::shared_ptr<IShape> right;
                AABB box;
        };

        inline bool box_x_compare(const std::shared_ptr<IShape> a, const std::shared_ptr<IShape> b)
        {
            AABB box_left, box_right;
            if (!a->bounding_box(0, 0, box_left) || !b->bounding_box(0, 0, box_right))
                std::cerr << "No bounding box in bvh_node constructor.\n";
            return box_left.min().getX() < box_right.min().getX();
        }

        inline bool box_y_compare(const std::shared_ptr<IShape> a, const std::shared_ptr<IShape> b)
        {
            AABB box_left, box_right;
            if (!a->bounding_box(0, 0, box_left) || !b->bounding_box(0, 0, box_right))
                std::cerr << "No bounding box in bvh_node constructor.\n";
            return box_left.min().getY() < box_right.min().getY();
        }

        inline bool box_z_compare(const std::shared_ptr<IShape> a, const std::shared_ptr<IShape> b)
        {
            AABB box_left, box_right;
            if (!a->bounding_box(0, 0, box_left) || !b->bounding_box(0, 0, box_right))
                std::cerr << "No bounding box in bvh_node constructor.\n";
            return box_left.min().getZ() < box_right.min().getZ();
        }

        Node::Node(const std::vector<std::shared_ptr<IShape>>& objects, size_t start, size_t end, double time0, double time1)
        {
            auto obj = objects;

            int axis = random_int(0, 2);
            auto comparator = (axis == 0) ? box_x_compare
                            : (axis == 1) ? box_y_compare
                            : box_z_compare;

            size_t span = end - start;

            if (span == 1)
                left = right = obj[start];
            else if (span == 2) {
                if (comparator(obj[start], obj[start + 1])) {
                    left = obj[start];
                    right = obj[start + 1];
                } else {
                    left = obj[start + 1];
                    right = obj[start];
                }
            } else {
                std::sort(obj.begin() + start, obj.begin() + end, comparator);
                auto mid = start + span / 2;
                left = std::make_shared<Node>(obj, start, mid, time0, time1);
                right = std::make_shared<Node>(obj, mid, end, time0, time1);
            }

            AABB box_left, box_right;
            if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
                std::cerr << "No bounding box in Node constructor.\n";
            box = box_left.surrounding_box(box_right);
        }
    }

#endif /* !NODE_HPP_ */
