#include "Shape.h"
#include <cmath>

float Sphere::findRayCollision(float x0, float y0, float z0, float xd, float yd, float zd) {
    // Calculate the B term of the quadratic equation
    float B = 2 * (xd * x0 - xd * center_x + yd * y0 - yd * center_y + zd * z0 - zd * center_z);
    // Calculate the C term of the quadratic equation
    float C = pow(x0, 2) - 2 * x0 * center_x + pow(center_x, 2) + pow(y0, 2) - 2 * y0 * center_y + pow(center_y, 2) + pow(z0, 2) - 2 * z0 * center_z + pow(center_z, 2) - pow(radius, 2);
    // Calculate discriminate to determine culling
    float discriminant = pow(B, 2) - 4 * C;

    // Check cases
    // If discriminant is ~ 0
    if (fabs(discriminant) < 1e-5) {
        // One real solution
        return -B / 2;
    }

    // If discriminant is less than 0, return a negative number to show that there is not real solution.
    if (discriminant < 0) {
        return -1.0f;
    }
}