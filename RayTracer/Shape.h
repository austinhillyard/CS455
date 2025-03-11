#ifndef SHAPE_H
#define SHAPE_H

#include "vec3.h"

struct MaterialProperties {
    float Kd;
    float Ks;
    float Ka;
    color Od;
    color Os;
    float Kgls;
    float reflection;
    
    MaterialProperties(float Kd, float Ks, float Ka, color Od, color Os, float Kgls, float reflection = 0.0f): Kd(Kd), Ks(Ks), Ka(Ka), Od(Od), Os(Os), Kgls(Kgls), reflection(reflection) {}
};

struct Ray {
    private:
        vec3 _origin;
        vec3 _direction;

    public:

        Ray() {}

        Ray(const point3&origin, const vec3& direction): _origin(origin), _direction(direction) {}

        const point3& origin() const {return _origin;}
        const vec3& direction() const {return _direction;}

        point3 at(double t) const {
            return _origin + t*_direction;
        }
};

class Shape {

    public:
        //Struct with all lighting and material properties
        MaterialProperties matt;

        Shape(MaterialProperties material): matt(material) {}
        virtual ~Shape() = default;
        //TODO: maybe Change return type, Right now it returns t where the parametric function solves the equation shape.
        virtual double findRayCollision(const point3 origin, const vec3 direction) = 0;
        // Return the normal vector given an x, y, and z of intersection.
        virtual vec3 returnNormal(point3 intersection) = 0;
        color illuminationEquation(vec3 normal, vec3 light_dir, vec3 view_dir, color light_color, color ambient_color) {
            vec3 R = (2 * (dot(light_dir, normal) * normal)) - light_dir;
            color ambient_light = matt.Ka*ambient_color*matt.Od;
            color diffuse_light = matt.Kd*light_color*matt.Od*std::max(0.0, dot(normal, light_dir));
            color specular_light = matt.Ks*light_color*matt.Os* pow(std::max(0.0, dot(-view_dir, R)), matt.Kgls);
            color output = ambient_light + diffuse_light + specular_light;
            return output;
        }
};

class Sphere: public Shape {
    public:
        vec3 center;

        float radius;
        Sphere(MaterialProperties material, vec3 center, float radius): Shape(material), center(center), radius(radius) {}
        ~Sphere() override = default;
        double findRayCollision(const point3 origin, const vec3 direction) override;
        vec3 returnNormal(point3 intersection) override;
};

class Triangle: public Shape {
    private:
        vec3 normal; 
        double d;

    public:
        vec3 vertex0;
        vec3 vertex1;
        vec3 vertex2;

        Triangle(MaterialProperties material, vec3 vertex0, vec3 vertex1, vec3 vertex2): Shape(material), vertex0(vertex0), vertex1(vertex1), vertex2(vertex2) {
            //Calculate normal once and save it to private variable since it's always the same.
            normal = unit_vector(cross((vertex1 - vertex0), (vertex2 - vertex1)));
            //Calculate d of Implicit plane equation as well
            d = -(normal.x() * vertex0.x() + normal.y() * vertex0.y() + normal.z() * vertex0.z());
        }
        ~Triangle() override = default;
        double findRayCollision(const point3 origin, const vec3 direction) override;
        vec3 returnNormal(point3 intersection) override {
            return normal;
        };
};

#endif