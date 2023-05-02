/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Parser
*/

#include "Parser.hpp"

namespace Parser {
    Parser::Parser(std::string path)
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

    raytracer::Camera Parser::parseCamera(void)
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

    Math::Vector3D Parser::parseVector3D(const libconfig::Setting &setting)
    {
        double x, y, z;

        if (setting.getLength() != 3)
            throw libconfig::SettingTypeException(setting, "Vector3D must have 3 values");
        x = setting[0];
        y = setting[1];
        z = setting[2];
        return Math::Vector3D(x, y, z);
    }

    raytracer::Scene Parser::parseScene(void)
    {
        raytracer::Scene scene;
        return scene;
    }

    int Parser::getImageHeight(void)
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

    int Parser::getSamplesPerPixel(void)
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

    int Parser::getMaxDepth(void)
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
