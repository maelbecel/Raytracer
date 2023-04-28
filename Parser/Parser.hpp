/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <libconfig.h++>
#include <iostream>
#include "../Camera.hpp"
#include "../Maths/Vector3D.hpp"

namespace Parser {
    class Parser {
        public:
            Parser(std::string path);
            ~Parser() = default;

            raytracer::Camera parseCamera(void);
        protected:
        private:
            Math::Vector3D parseVector3D(const libconfig::Setting &setting);
            libconfig::Config _cfg;
    };
}

#endif /* !PARSER_HPP_ */
