#include "ppmWriter.h"
#include "RayTracer.h"

int main(int argc, char** argv) {
    
    PPMWriter writer = PPMWriter("test", 255, 255);
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            writer.write_next_pixel(i, j, i*j);
        }
    }

    return 0;
}