#ifndef PPM_WRITER
#define PPM_WRITER

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include "vec3.h"

class PPMWriter {
    private:
        unsigned int screen_width;
        unsigned int screen_height;
        unsigned long next_byte = 0;
        std::ofstream PPMFile;
        void write_color(std::ostream& out, const color& pixel_color);
        

    public:
        // Constructor for PPMWriter, default file size of 500 by 500
        PPMWriter(std::string filename, unsigned int width, unsigned int height);
        ~PPMWriter();

        // Starts at the first pixel, and increments the next value to write after being called.
        void write_next_pixel(color nextColor);

        //Returns the position of the next byte to be written when write_next_byte is called
        unsigned long get_next_pixel();

        //Close the file manually if the user is kind enough to do so.
        void close_file();
};

#endif