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

    namespace raytracer {
        class Image : public ITexture {
            public:
                const static int bytes_pixel = 3;

                Image() : data(nullptr), width(0), height(0), bytes_scan(0) {}
                Image(const char *filename) {
                    auto components_pixel = bytes_pixel;

                    data = load_img(filename, &width, &height, &components_pixel);

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

                unsigned char* load_img(const char* filename, int* width, int* height, int* comp)
                {
                    FILE* fp = fopen(filename, "rb");
                    if (!fp) {
                        return nullptr;
                    }
                    unsigned char header[54];
                    if (fread(header, sizeof(unsigned char), 54, fp) != 54) {
                        fclose(fp);
                        return nullptr;
                    }
                    *width = *(int*)&header[18];
                    *height = *(int*)&header[22];
                    int bpp = *(int*)&header[28];
                    *comp = bpp / 8;

                    unsigned char* img_data = new unsigned char[*width * *height * *comp];
                    size_t row_size = (*width * bpp + 31) / 32 * 4;
                    unsigned char* row = new unsigned char[row_size];
                    for (int y = 0; y < *height; y++) {
                        if (fread(row, sizeof(unsigned char), row_size, fp) != row_size) {
                            delete[] img_data;
                            delete[] row;
                            fclose(fp);
                            return nullptr;
                        }
                        for (int x = 0; x < *width; x++) {
                            for (int c = 0; c < *comp; c++) {
                                img_data[(y * *width + x) * *comp + c] = row[x * *comp + *comp - c - 1];
                            }
                        }
                    }
                    delete[] row;
                    fclose(fp);
                    return img_data;
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
