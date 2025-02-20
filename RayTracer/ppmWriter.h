#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

class PPMWriter {
    private:
        unsigned int screen_width;
        unsigned int screen_height;
        unsigned long next_byte = 0;
        std::ofstream PPMFile;
        

    public:
        // Constructor for PPMWriter, default file size of 500 by 500
        PPMWriter(std::string filename, unsigned int width, unsigned int height);
        ~PPMWriter();

        // Starts at the first pixel, and increments the next value to write after being called.
        void write_next_pixel(uint8_t red, uint8_t green, uint8_t blue);

        //Returns the position of the next byte to be written when write_next_byte is called
        unsigned long get_next_pixel();

        //Close the file manually if the user is kind enough to do so.
        void close_file();
};