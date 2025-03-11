#include "ppmWriter.h"
#include "RayTracer.h"

void purpleSphere() {
    RayTracer myTracer(500, 500, 90, 1);

    Sphere* purpleSphere = new Sphere(MaterialProperties(0.7, .2, .1, color(1, 0, 1), color(1, 1, 1), 16), vec3(0,0,0), .4);
    std::vector<Shape*> shapes;
    shapes.push_back(purpleSphere);
    myTracer.renderScene(shapes, unit_vector(vec3(0, 1, 0)), color(1, 1, 1), color(0.0, 0.0, 0.0), color(.2, .2, .2), "purpleSphere");
    
    for (Shape* shape: shapes) {
        delete shape;
    }
}

void moreSpheres() {
    RayTracer myTracer(500, 500, 90, 1);
    std::vector<Shape*> shapes;

    shapes.push_back(new Sphere(MaterialProperties(.8, .1, .3, color(1.0, 1.0, 1.0), color(1.0, 1.0, 1.0), 4.0), vec3(.45, 0.0, -.15), .15));
    shapes.push_back(new Sphere(MaterialProperties(.6, .3, .1, color(1.0, 0, 0), color(1, 1, 1), 32.0), vec3(0, 0, -.1), .2));
    shapes.push_back(new Sphere(MaterialProperties(.7, .2, .1, color(0, 1, 0), color(.5, 1, .5), 64), vec3(-.6, 0, 0), .3));
    shapes.push_back(new Sphere(MaterialProperties(.9, 0, .1, color(0, 0, 1), color(1, 1, 1), 16), vec3(0, -10000.5, 0), 10000));

    myTracer.renderScene(shapes, unit_vector(vec3(1, 1, 1)), color(1, 1, 1), color(0.1, 0.1, 0.1), color(.2, .2, .2), "moreSpheres");

    for (Shape* shape: shapes) {
        delete shape;
    }
}

void MANYSPHERES() {
    RayTracer myTracer(1000, 1000, 90, 1);
    std::vector<Shape*> shapes;
    shapes.push_back(new Sphere(MaterialProperties(.5, .3, .4, color(226, 53, 229)/255, color(255, 0, 158)/255, 1.0), vec3(-.4, .6, -3), .5));
    shapes.push_back(new Sphere(MaterialProperties(.8, .1, 1, color(0, 255, 147)/255, color(1, 1, 1), 16.0), vec3(6, -.5, -25), 3));
    shapes.push_back(new Sphere(MaterialProperties(.8, .1, 0, color(0.01, 0.01, 0.01), color(1, 1, 1), 2.0), vec3(0, 1, -1), .3));
    shapes.push_back(new Sphere(MaterialProperties(.7, .1, .2, color(.5, 0.23, 0.10), color(.8, .9, 1), 24.0), vec3(-4, -30, -100), 10));
    shapes.push_back(new Sphere(MaterialProperties(.8, .3, .1, color(223, 77, 121)/255, color(255, 189, 209)/255, 4.0), vec3(10, 2, -50), 12));
    shapes.push_back(new Sphere(MaterialProperties(.8, .2, .1, color(1, 1, 1), color(0, 0, 0), 3.0), vec3(1, .5, -2), .5));

    myTracer.renderScene(shapes, unit_vector(vec3(1,1,1)), color(1, 1, 1), color(214, 23, 23)/255, color(.2, .2, .2), "ManySpheres");

    for (Shape* shape: shapes) {
        delete shape;
    }
}

void TRI_SCENE_1() {

    RayTracer myTracer(500, 500, 90, 1);
    std::vector<Shape*> shapes;
    shapes.push_back(new Sphere(MaterialProperties(0, .1, .1, color(.75, .75, .75), color(1, 1, 1), 10, .9), vec3(0, .3, -1.0), .25));
    shapes.push_back(new Triangle(MaterialProperties(.9, 1.0, .1, color(0.0, 0.0, 1.0), color(1, 1, 1), 4, 0.0), vec3(0.0, -.7, -.5), vec3(1.0, .4, -1.0), vec3(0.0, -.7, -1.5)));
    shapes.push_back(new Triangle(MaterialProperties(.9, 1.0, .1, color(1.0, 1.0, 0.0), color(1, 1, 1), 4, 0.0), vec3(0.0, -.7, -.5), vec3(0, -.7, -1.5), vec3(-1.0, .4, -1.0)));
    
    myTracer.renderScene(shapes, unit_vector(vec3(0,1,0)), color(1, 1, 1), color(0, 0, 0), color(.2, .2, .2), "TriScene1");

    for (Shape* shape: shapes) {
        delete shape;
    }
}

void TRI_SCENE_2() {
    RayTracer myTracer(500, 500, 90, 1);
    std::vector<Shape*> shapes;
    shapes.push_back(new Sphere(MaterialProperties(0.8, .1, .3, color(1, 1, 1), color(1, 1, 1), 4, 0), vec3(0.5, .0, -.15), .05));
    shapes.push_back(new Sphere(MaterialProperties(0.8, .8, .1, color(1, 0, 0), color(.5, 1, .5), 32, 0), vec3(0.3, .0, -.1), .08));
    shapes.push_back(new Sphere(MaterialProperties(0.7, .5, .1, color(0, 1, 0), color(.5, 1, .5), 64, 0), vec3(-0.6, .0, 0), .3));
    shapes.push_back(new Sphere(MaterialProperties(0.0, .1, .1, color(.75, .75, .75), color(1, 1, 1), 32, .9), vec3(.1, -0.55, .25), .3));
    shapes.push_back(new Triangle(MaterialProperties(.9, .9, .1, color(0.0, 0.0, 1.0), color(1, 1, 1), 32, 0.0), vec3(.3, -.3, -.4), vec3(0, .3, -.1), vec3(-.3, -.3, .2)));
    shapes.push_back(new Triangle(MaterialProperties(.9, .5, .1, color(1.0, 1.0, 0.0), color(1, 1, 1), 4, 0.0), vec3(-.2, .1, .1), vec3(-.2, -.5, .2), vec3(-.2, .1, -.3)));
    
    myTracer.renderScene(shapes, unit_vector(vec3(1,0,0)), color(1, 1, 1), color(0.1, 0.1, 0.1), color(.2, .2, .2), "TriScene2");

    for (Shape* shape: shapes) {
        delete shape;
    }
}

void MANYREFLECTIVESPHERES() {
    RayTracer myTracer(1000, 1000, 90, 1);
    std::vector<Shape*> shapes;
    shapes.push_back(new Sphere(MaterialProperties(.1, .3, .4, color(226, 53, 229)/255, color(255, 0, 158)/255, 1.0, .9), vec3(-.4, .6, -3), .5));
    shapes.push_back(new Sphere(MaterialProperties(.8, .1, 1, color(0, 255, 147)/255, color(1, 1, 1), 16.0, .5), vec3(6, -.5, -25), 3));
    shapes.push_back(new Sphere(MaterialProperties(.2, .1, 0, color(0.01, 0.01, 0.01), color(1, 1, 1), 2.0, .7), vec3(0, 1, -1), .3));
    shapes.push_back(new Sphere(MaterialProperties(.7, .1, .2, color(.5, 0.23, 0.10), color(.8, .9, 1), 24.0, .2), vec3(-4, -30, -100), 10));
    shapes.push_back(new Sphere(MaterialProperties(.8, .3, .1, color(223, 77, 121)/255, color(255, 189, 209)/255, 4.0, .1), vec3(10, 2, -50), 12));
    shapes.push_back(new Sphere(MaterialProperties(.8, .2, .1, color(1, 1, 1), color(0, 0, 0), 3.0, .1), vec3(1, .5, -2), .5));
    shapes.push_back(new Triangle(MaterialProperties(.9, 1.0, .1, color(1.0, 0.0, 1.0), color(1, 1, 1), 4, 0.0), vec3(0.0, -.7, -1.5), vec3(1.0, .4, -3.0), vec3(0.0, -.7, -2.5)));
    shapes.push_back(new Triangle(MaterialProperties(.9, 1.0, .1, color(1.0, 0, 0), color(1, 1, 1), 4, 0.0), vec3(0.0, -.7, -1.5), vec3(0, -.7, -3.5), vec3(-1.0, .4, -2.0)));

    myTracer.renderScene(shapes, unit_vector(vec3(.5,1,1)), color(1, 1, 1), color(214, 23, 23)/255, color(.2, .2, .2), "reflectiveSpheres");

    for (Shape* shape: shapes) {
        delete shape;
    }
}

int main(int argc, char** argv) {
    
    MANYREFLECTIVESPHERES();

    return 0;
}