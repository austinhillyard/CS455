#include "RayTracer.h"

Screen::Screen(unsigned int screen_width, unsigned int screen_height) {
    screen_width = screen_width;
    screen_height = screen_height;
}

RayTracer::RayTracer(unsigned int screen_width, unsigned int screen_height, unsigned int camera_z_position) {
    screen = Screen(screen_width, screen_height);
}