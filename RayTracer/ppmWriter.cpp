#include "ppmWriter.h"

void PPMWriter::write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

// Constructor for PPMWriter, default file size of 500 by 500
PPMWriter::PPMWriter(std::string filename = "default", unsigned int width = 500, unsigned int height = 500) {
    this->screen_width = width;
    this->screen_height = width;

    //Create an outfile
    PPMFile.open(filename.append(".ppm"), std::ios::out | std::ios::trunc);
    if (!PPMFile) {
        throw std::runtime_error("Failed to open file");
    }
    PPMFile << "P3\n" << 
        std::to_string(screen_width) << " " << std::to_string(screen_height) << "\n"<< 
        "255" << std::endl;
}

PPMWriter::~PPMWriter() {
    this->close_file();
}

// Starts at the first pixel, and increments the next value to write after being called.
void PPMWriter::write_next_pixel(color nextColor) {
    write_color(PPMFile, nextColor);
    next_byte += 1;
}

//Returns the position of the next byte to be written when write_next_byte is called
unsigned long PPMWriter::get_next_pixel() {
    return this->next_byte;
}

//Close the file manually if the user is kind enough to do so.
void PPMWriter::close_file() {
    if (PPMFile.is_open()) {
        PPMFile.flush();
        PPMFile.close();
    }
}