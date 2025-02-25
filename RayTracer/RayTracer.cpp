#include "RayTracer.h"
#include "ppmWriter.h"
#include <cmath>

//Uses the screen width, height, field of view and camera position to calculate pixel sizes and builds a 2d vector of rays.
void RayTracer::buildScreenAndRays() {
    double y_extent = tan(fov / 2.0) * camera_z_position;
    double x_extent = tan(fov / 2.0) * camera_z_position;

    double pixel_size_y = (y_extent * 2) / screen_height;
    double pixel_size_x = (x_extent * 2) / screen_width;

    //Start at top left pixel center
    double top_left_pixel_center_x = -x_extent + pixel_size_x;
    Pixel cur_pixel = Pixel(-x_extent + pixel_size_x, y_extent);
    for (unsigned int i = 0; i < screen_height; i++) {
        for (unsigned int j = 0; j < screen_width; j++) {

            rays[i][j] = new Ray(point3(0, 0, camera_z_position), unit_vector(vec3(cur_pixel.x, cur_pixel.y, -camera_z_position)));
            cur_pixel.x  += pixel_size_x;
        }
        cur_pixel.y -= pixel_size_y;
        cur_pixel.x = top_left_pixel_center_x;
    }
}

//Simple constructor that sets up stuff and calls the build screen function
RayTracer::RayTracer(unsigned int screen_width, unsigned int screen_height, double fov, double camera_z_position): screen_width(screen_width), screen_height(screen_height), fov(fov), camera_z_position(camera_z_position) {

    //Build Screen
    rays = std::vector<std::vector<Ray*>>(screen_height, std::vector<Ray*>(screen_width, NULL));
    buildScreenAndRays();
}

RayTracer::~RayTracer() {
    for (unsigned int i = 0; i < screen_height; i++) {
        for (unsigned int j = 0; j < screen_width; j++) {
            delete rays[i][j];
        }
    }
}

//Render a scene given some shapes, a directional light vector,, the color of the light, color of the background, and an optional file name.
void RayTracer::renderScene(std::vector<Shape*> shapes, vec3 light_dir, color light_color, color ambient_color, color background, std::string filename="output") {
    //Get a PPMWriter for our output
    PPMWriter writer(filename, screen_width, screen_height);

    //iterate through rays
    for (unsigned int i = 0; i < screen_height; i++) {
        for (unsigned int j = 0; j < screen_width; j++) {

            //Need to make this its own function, will be easier via recursion, or some sort of branch and bound queue.
            //Iterate though shapes to see which has the earliest contact point.
            double min_t;
            int closest_shape = -1;
            Ray* cur_ray = rays[i][j];
            for (long unsigned int k = 0; k < shapes.size(); k++) {
                double t = shapes[k]->findRayCollision(cur_ray->origin(), cur_ray->direction());
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
                writer.write_next_pixel(background);
                continue;
            }
            //Calculate intersection point via t
            point3 intersection = cur_ray->at(min_t);

            //TODO: Implement some sort of queue where given the intersection we add a new ray to calculate for RayTracer_2
            //Calculate color
            vec3 normal = shapes[closest_shape]->returnNormal(intersection);
            color ray_color = shapes[closest_shape]->illuminationEquation(normal, light_dir, cur_ray->direction(), light_color, ambient_color);

            //Write color out to output image
            writer.write_next_pixel(ray_color);
        }
    }
}

//Might use this function later
color RayTracer::calculateColor(Shape& shape, vec3 light_dir, color light_color, point3 intersection) {
    
    return color();
}