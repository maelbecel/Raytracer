/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** GifCreator
*/

#ifndef GIFCREATOR_HPP_
    #define GIFCREATOR_HPP_

    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <sstream>
    #include <cstdio>

    namespace raytracer {
        class GifCreator {
            public:
                static void createGif(std::string filename, std::vector<std::string>& ppm_buffer_list, int fps)
                {
                    // Step 1: Create temporary PPM files from the buffers
                    std::vector<std::string> ppm_filenames;
                    for (size_t i = 0; i < ppm_buffer_list.size(); i++) {
                        std::stringstream ppm_filename;
                        ppm_filename << "temp_" << i << ".ppm";
                        std::ofstream ppm_file(ppm_filename.str().c_str());
                        ppm_file << ppm_buffer_list[i];
                        ppm_file.close();
                        ppm_filenames.push_back(ppm_filename.str());
                    }

                    // Step 2: Create the GIF using ImageMagick
                    std::stringstream convert_command;
                    convert_command << "convert -delay " << 100 / fps << " -loop 0 ";
                    for (size_t i = 0; i < ppm_filenames.size(); i++) {
                        convert_command << ppm_filenames[i] << " ";
                    }
                    convert_command << filename;

                    FILE* pipe = popen(convert_command.str().c_str(), "r");
                    if (!pipe) {
                        std::cerr << "Failed to create GIF: popen failed\n";
                        return;
                    }
                    pclose(pipe);

                    // Step 3: Delete the temporary PPM files
                    for (size_t i = 0; i < ppm_filenames.size(); i++) {
                        std::remove(ppm_filenames[i].c_str());
                    }
                }

            protected:
            private:
        };
    }

#endif /* !GIFCREATOR_HPP_ */
