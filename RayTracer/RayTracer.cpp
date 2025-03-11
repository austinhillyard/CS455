#include "RayTracer.h"
#include "ppmWriter.h"
#include <cmath>

//Uses the screen width, height, field of view and camera position to calculate pixel sizes and builds a 2d vector of rays.
void RayTracer::buildScreenAndRays() {
    double y_extent = tan(fov / 4.0) * camera_z_position;
    double x_extent = tan(fov / 4.0) * camera_z_position;

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
            color pixelColor = renderRayColor(shapes, rays[i][j], light_dir, light_color, ambient_color, background);
            writer.write_next_pixel(pixelColor);
        }
    }

    writer.close_file();
}

color RayTracer::renderRayColor(std::vector<Shape*> shapes, Ray* cur_ray, vec3 light_dir, color light_color, color ambient_color, color background, int ray_depth) {
    //Find closest ray interesection
    double min_t = -1;
    Shape* closest_shape = NULL;
    findRayFirstIntersection(shapes, cur_ray, min_t, closest_shape);

    //After earliest contact point is found, calculate color
    //Or draw background color if no closest shape
    if (closest_shape == NULL) {
        return background;
    }
    //Calculate intersection point via t
    point3 intersection = cur_ray->at(min_t);
    vec3 closest_shape_normal = closest_shape->returnNormal(intersection);
    //Move a tiny bit away from the object to avoid shadow ray hitting the same object.
    point3 slightIntersectionOffset = intersection + closest_shape_normal * .01;

    //Reflection Ray
    //Only calculate reflection if object is reflective, and current ray is not a secondary ray.
    //Default reflection of nothing
    color reflectionColor = color(0, 0, 0);
    if (closest_shape->matt.reflection > 0.0 && ray_depth < 2) {
        Ray reflection = Ray(slightIntersectionOffset, cur_ray->direction() - 2*closest_shape_normal * dot(cur_ray->direction(), closest_shape_normal));
        //Overwrite reflection color
        reflectionColor = renderRayColor(shapes, &reflection, light_dir, light_color, ambient_color, background, true);
    } else {
        //Shadow Ray, only calculate if not reflective surface
        Ray shadowRay = Ray(slightIntersectionOffset, light_dir);
        min_t = -1;
        Shape* closest_shape_from_shadow = NULL;
        //Find first intersection for shadow ray
        findRayFirstIntersection(shapes, &shadowRay, min_t, closest_shape_from_shadow);
        //If no intersection, not in shadow, continue.
        //Otherwise, in shadow, draw black.
        if (closest_shape_from_shadow != NULL) {
            //return color(0, 0, 0) + ambient_color * closest_shape->matt.Ka;
            light_color = color(0,0,0);
        }
    }
    
    

    //Calculate color
    color ray_color = closest_shape->illuminationEquation(closest_shape_normal, light_dir, cur_ray->direction(), light_color, ambient_color);

    //Write color out to output image
    //Weight intersection color by opposite of reflection level and add reflection value
    color final_color = ray_color * (1 - closest_shape->matt.reflection) + closest_shape->matt.reflection * reflectionColor;
    return final_color;
}

//Iterate though shapes to see which has the earliest contact point.
void RayTracer::findRayFirstIntersection(std::vector<Shape*> shapes, Ray* cur_ray, double& min_t, Shape*& closest_shape) {
    for (long unsigned int k = 0; k < shapes.size(); k++) {
        double t = shapes[k]->findRayCollision(cur_ray->origin(), cur_ray->direction());
        //If t is less than zero, continue immediately.
        if (t < 0) {
            continue;
        }
        //Otherwise, check if new t is closer than previous t, or if there is no minimum yet, set it t.
        else if (min_t == -1 || min_t > t) {
            min_t = t;
            closest_shape = shapes[k];
        }
    }
}


//Might use this function later
color RayTracer::calculateColor(Shape& shape, vec3 light_dir, color light_color, point3 intersection) {
    
    return color();
}