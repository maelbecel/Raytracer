/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Image
*/

#ifndef IMAGE_HPP_
    #define IMAGE_HPP_

    #include "ITexture.hpp"
    #include <iostream>
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.hpp"

    namespace raytracer {
        class Image : public ITexture {
            public:
                const static int bytes_pixel = 3;

                Image() : data(nullptr), width(0), height(0), bytes_scan(0) {}
                Image(const char *filename) {
                    auto components_pixel = bytes_pixel;

                    data = stbi_load(filename, &width, &height, &components_pixel, components_pixel);

                    if (!data) {
                        std::cerr << "Failed to load '" << filename << "'.\n";
                        width = 0;
                        height = 0;
                    }

                    bytes_scan = bytes_pixel * width;
                }

                ~Image() {
                    delete data;
                }

                virtual Math::Color value(double u, double v, UNUSED const Math::Vector3D &p) const override {
                    if (data == nullptr)
                        return Math::Color(0, 1, 1);

                    u = CLAMP(u, 0, 1);
                    v = 1 - CLAMP(v, 0, 1);

                    auto i = static_cast<int>(u * width);
                    auto j = static_cast<int>(v * height);

                    if (i >= width) i = width - 1;
                    if (j >= height) j = height - 1;

                    const auto color_scale = 1.0 / 255.0;
                    auto pixel = data + j * bytes_scan + i * bytes_pixel;

                    return Math::Color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
                }

            protected:
            private:
                unsigned char *data;
                int width, height;
                int bytes_scan;
        };
    }

#endif /* !IMAGE_HPP_ */
