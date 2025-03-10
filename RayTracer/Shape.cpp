#include "Shape.h"
#include <cmath>

double Sphere::findRayCollision(const point3 ori, const vec3 dir) {
    // Calculate the B term of the quadratic equation
    double B = 2.0 * (dir.x() * ori.x() - dir.x() * center.x() + dir.y() * ori.y() - dir.y() * center.y() + dir.z() * ori.z() - dir.z() * center.z());
    // Calculate the C term of the quadratic equation
    double C = pow(ori.x(), 2.0) - 2.0 * ori.x() * center.x() + pow(center.x(), 2.0) + pow(ori.y(), 2.0) - 2.0 * ori.y() * center.y() + pow(center.y(), 2.0) + pow(ori.z(), 2.0) - 2.0 * ori.z() * center.z() + pow(center.z(), 2.0) - pow(radius, 2.0);
    // Calculate discriminate to determine culling
    double discriminant = pow(B, 2.0) - 4 * C;

    // Check cases
    // If discriminant is ~ 0
    if (fabs(discriminant) < 1e-5) {
        // One real solution
        return -B / 2.0;
    }

    // If discriminant is less than 0, return a negative number to show that there is not real solution.
    if (discriminant < 0) {
        return -1.0f;
    }

    // Compute the discriminant in the square root
    double square_root = sqrt(discriminant);
    // If the discriminant is greater than 0, find the first and smaller solution
    double t0 = (-B - square_root) / 2.0;

    if (t0 > 0.0) {
        return t0;
    }
    // And then the second if the first one isn't a positive number.
    double t1 = (-B + square_root) / 2.0;
    return t1;
}

// Returns the normal vector given a point on the circle.
vec3 Sphere::returnNormal(point3 point) {
    vec3 normal = point - center;
    normal /= radius;
    return normal;
}

double Triangle::findRayCollision(const point3 origin, const vec3 dir) {
    //Conduct Planar collision test first
    double pnrd = dot(normal, dir);
    // If equal to 0, ray is parallel to the plane and does not intersect
    if (fabs(pnrd) < 1e-5) {
        return -1.0f;
    }
    // If greater than 0, normal of plane is pointing away from the ray and the plane is culled
    else if (pnrd > 0) {
        return -1.0f;
    }
    // Otherwise solve for t
    double t = -(dot(normal, origin) + d) / pnrd;
    
    //Calculate intersection
    point3 p = origin + t * dir;
    // Check that the collision is in the convex polygon.
    double edge1 = dot(cross(p - vertex0, vertex1 - vertex0), normal);
    double edge2 = dot(cross(p - vertex1, vertex2 - vertex1), normal);
    double edge3 = dot(cross(p - vertex2, vertex0 - vertex2), normal);

    if (edge1 > 0 && edge2 > 0 && edge3 > 0) {
        return t;
    }
    return -1.0f;
}