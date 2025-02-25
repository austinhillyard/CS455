#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include <vector>
#include "Shape.h"
#include <string>

struct Pixel {
    double x;
    double y;
    Pixel(double x, double y): x(x), y(y) {}
};

class RayTracer {

    std::vector<std::vector<struct Ray*>> rays;

    private:
        unsigned int screen_width;
        unsigned int screen_height;
        double fov;
        double camera_z_position;

        void buildScreenAndRays();
        color calculateColor(Shape& shape, vec3 light_dir, color light_color, point3 intersection);

    public:
        // Takes in a screen size, and the camera position on the z axis. 
        // Camera is assumed to be on the z axis looking toward the origin, with the screen on the x-y plane
        RayTracer(unsigned int screen_width, unsigned int screen_height, double fov, double camera_z_position);
        ~RayTracer();
        void renderScene(std::vector<Shape*> shapes, vec3 light_dir, color light_color, color ambient_color, color background, std::string filename);


};

#endif