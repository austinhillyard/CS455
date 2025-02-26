#ifndef SHAPE_H
#define SHAPE_H

#include "vec3.h"


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
        float Kd;
        float Ks;
        float Ka;
        color Od;
        color Os;
        float Kgls;

        Shape(float Kd, float Ks, float Ka, color Od, color Os, float Kgls): Kd(Kd), Ks(Ks), Ka(Ka), Od(Od), Os(Os), Kgls(Kgls) {}
        virtual ~Shape() = default;
        //TODO: maybe Change return type, Right now it returns t where the parametric function solves the equation shape.
        virtual double findRayCollision(const point3 origin, const vec3 direction) = 0;
        // Return the normal vector given an x, y, and z of intersection.
        virtual vec3 returnNormal(point3 intersection) = 0;
        color illuminationEquation(vec3 normal, vec3 light_dir, vec3 view_dir, color light_color, color ambient_color) {
            vec3 R = (2 * (dot(light_dir, normal) * normal)) - light_dir;
            color ambient_light = Ka*ambient_color*Od;
            color diffuse_light = Kd*light_color*Od*std::max(0.0, dot(normal, light_dir));
            color specular_light = Ks*light_color*Os* pow(std::max(0.0, dot(-view_dir, R)), Kgls);
            color output = ambient_light + diffuse_light + specular_light;
            return output;
        }
};

class Sphere: public Shape {
    public:
        vec3 center;

        float radius;
        Sphere(float Kd, float Ks, float Ka, color Od, color Os, float Kgls, vec3 center, float radius): Shape(Kd, Ks, Ka, Od, Os, Kgls), center(center), radius(radius) {}
        ~Sphere() override = default;
        double findRayCollision(const point3 origin, const vec3 direction) override;
        vec3 returnNormal(point3 intersection) override;
};

#endif