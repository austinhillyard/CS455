#include "ppmWriter.h"
#include "RayTracer.h"

int main(int argc, char** argv) {
    
    RayTracer myTracer(500, 500, 90, 1);

    Sphere* purpleSphere = new Sphere(0.7, .2, .1, color(1, 0, 1), color(1, 1, 1), 16, vec3(0,0,0), .4);
    std::vector<Shape*> shapes;
    shapes.push_back(purpleSphere);
    myTracer.renderScene(shapes, vec3(0, 1, 0), color(1, 1, 1), color(0.0, 0.0, 0.0), color(.2, .2, .2), "purpleSphere");
    
    for (Shape* shape: shapes) {
        delete shape;
    }

    return 0;
}