#include "RayTracer.h"
#include "ppmWriter.h"
#include <cmath>

//Uses the screen width, height, field of view and camera position to calculate pixel sizes and builds a 2d vector of rays.
void RayTracer::buildScreenAndRays() {
    double y_extent = tan(fov / 2.0) * camera_z_position;
    double x_extent = tan(fov / 2.0) * camera_z_position;

    double pixel_size_y = (y_extent * 2) / screen_height;
    double pixel_size_x = (x_extent * 2) / screen_height;

    //Start at top left pixel center
    double top_left_pixel_center_x = -x_extent + pixel_size_x;
    Pixel cur_pixel = Pixel(-x_extent + pixel_size_x, y_extent);
    for (int i = 0; i < screen_height; i++) {
        for (int j = 0; j < screen_width; j++) {
            rays[i][j] = new ParametricRay(cur_pixel.x, cur_pixel.y, 0, 0, 0, camera_z_position);
            cur_pixel.x  += pixel_size_x;
        }
        cur_pixel.y += pixel_size_y;
        cur_pixel.x = top_left_pixel_center_x;
    }
}

//Simply constructor that sets up stuff and calls the build screen function
RayTracer::RayTracer(unsigned int screen_width, unsigned int screen_height, double fov, double camera_z_position) {
    screen_width = screen_width;
    screen_height = screen_height;
    fov = fov;
    camera_z_position = camera_z_position;

    //Build Screen
    rays = std::vector<std::vector<ParametricRay*>>(screen_height, std::vector<ParametricRay*>(screen_width, NULL));
    buildScreenAndRays();
}

RayTracer::~RayTracer() {
    for (int i = 0; i < screen_height; i++) {
        for (int j = 0; j < screen_width; j++) {
            delete rays[i][j];
        }
    }
}

//Render a scene given some shapes, a directional light vector,, the color of the light, color of the background, and an optional file name.
void RayTracer::renderScene(std::vector<Shape> shapes, double light_x, double light_y, double light_z, Color light_color, Color background, std::string filename="output") {
    //Get a PPMWriter for our output
    PPMWriter writer(filename, screen_width, screen_height);

    //iterate through rays
    for (int i = 0; i < screen_height; i++) {
        for (int j = 0; j < screen_width; j++) {
            //Iterate though shapes to see which has the earliest contact point.
            double min_t;
            int closest_shape = -1;
            for (int k = 0; k < shapes.size(); k++) {
                ParametricRay* cur_ray = rays[i][j];
                double t = shapes[k].findRayCollision(cur_ray->x0,  cur_ray->y0, cur_ray->z0, cur_ray->xd, cur_ray->yd, cur_ray->zd);
                //If t is less than zero, continue immediately.
                if (t < 0) {
                    continue;
                }
                //Else if the first shape, min_t is the first answer
                else if (k == 0) {
                    min_t = t;
                    closest_shape = k;
                }
                //Otherwise, check if new t is closer than previous t.
                else if (min_t > t) {
                    min_t = t;
                    closest_shape = k;
                }
            }

            //After earliest contact point is found, calculate color
            //Or draw background color if no closest shape
            if (closest_shape == -1) {
                writer.write_next_pixel(background.red, background.green, background.blue);
                continue;
            }
            //Calculate color
            // TODO
        }
    }
}