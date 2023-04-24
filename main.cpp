/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** main
*/

#include "Camera.hpp"
#include "Sphere.hpp"
#include "Point3D.hpp"
#include <iostream>
#include <fstream>

int main ()
{
    std::ofstream file("image.ppm");
    RayTracer :: Camera cam ;
    RayTracer :: Sphere s ( Math :: Point3D (0 , 0, 1.5) , 0.2) ;
    file << "P3" << std::endl << "400 400" << std::endl << "255" << std::endl;
    for (double i = -200 ; i < 200 ; i += 1) {
        for (double j = -200 ; j < 200 ; j += 1) {
            double u = j / 400 ;
            double v = i / 400 ;
            RayTracer :: Ray r = cam . ray (u , v ) ;
            if ( s . hits ( r ) ) {
                file << "255 0 0" << std::endl;
            } else {
                file << "255 255 255" << std::endl;
            }
        }
    }
}
