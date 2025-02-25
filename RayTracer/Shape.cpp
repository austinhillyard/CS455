#include "Shape.h"
#include <cmath>

double Sphere::findRayCollision(double x0, double y0, double z0, double xd, double yd, double zd) {
    // Calculate the B term of the quadratic equation
    double B = 2.0 * (xd * x0 - xd * center_x + yd * y0 - yd * center_y + zd * z0 - zd * center_z);
    // Calculate the C term of the quadratic equation
    double C = pow(x0, 2.0) - 2.0 * x0 * center_x + pow(center_x, 2.0) + pow(y0, 2.0) - 2.0 * y0 * center_y + pow(center_y, 2.0) + pow(z0, 2.0) - 2.0 * z0 * center_z + pow(center_z, 2.0) - pow(radius, 2.0);
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
    double t1 = (-B - square_root) / 2.0;
    return t1;
}

// Returns the normal vector given a point on the circle.
Ray Sphere::returnNormal(double x, double y, double z) {
    Ray normal = Ray((x-center_x)/radius, (y-center_y)/radius, (z-center_z)/radius);
    return normal;
}