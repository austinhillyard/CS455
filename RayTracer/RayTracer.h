#include <vector>
#include "Shape.h"
#include <string>

struct Pixel {
    double x;
    double y;
    Pixel(double x, double y): x(x), y(y) {}
};

class RayTracer {

    std::vector<std::vector<struct ParametricRay*>> rays;

    private:
        unsigned int screen_width;
        unsigned int screen_height;
        double fov;
        double camera_z_position;

        void buildScreenAndRays();

    public:
        // Takes in a screen size, and the camera position on the z axis. 
        // Camera is assumed to be on the z axis looking toward the origin, with the screen on the x-y plane
        RayTracer(unsigned int screen_width, unsigned int screen_height, double fov, double camera_z_position);
        void renderScene(std::vector<Shape> shapes, double light_x, double light_y, double light_z, Color light_color, Color background, std::string filename="output");

};