//Parametric ray with an origin and a normalized direction vector that is calculated automatically.
struct ParametricRay {
    double xd;
    double yd;
    double zd;

    double x0;
    double y0;
    double z0;

    ParametricRay(double pixel_x, double pixel_y, double pixel_z, double x0, double y0, double z0): x0(x0), y0(y0), z0(z0) {
        xd = pixel_x - x0;
        yd = pixel_y - y0;
        zd = pixel_z - z0;
        double magnitude = sqrt(pow(xd, 2) + pow(yd, 2) + pow(zd, 2));
        xd /= magnitude;
        yd /= magnitude;
        zd /= magnitude;
    }
};

// Very basic ray/point struct with just x, y, and z
struct Ray {
    double x;
    double y;
    double z;
    Ray(double x, double y, double z): x(x), y(y), z(z) {}
};

class Color {
    public:
        float red;
        float green;
        float blue;

        Color(float red, float green, float blue) : red(red), green(green), blue(blue){}

        Color operator*(const Color& other) const {
            return Color(red * other.red, green * other.green, blue * other.blue);
        }

        Color operator*(float scalar) const {
            return Color(red * scalar, green * scalar, blue * scalar);
        }

        friend Color operator*(float scalar, const Color& color) {
            return color * scalar;
        }
};

class Shape {
    public:
        float Kd;
        float Ks;
        float Ka;
        Color Od;
        Color Os;
        float Kgls;

        Shape(float Kd, float Ks, float Ka, Color Od, Color Os, float Kgls): Kd(Kd), Ks(Ks), Ka(Ka), Od(Od), Os(Os), Kgls(Kgls) {}
        //TODO: maybe Change return type, Right now it returns t where the parametric function solves the equation shape.
        virtual double findRayCollision(double x0, double y0, double z0, double xd, double yd, double zd);
        // Return the normal vector given an x, y, and z of intersection.
        virtual Ray returnNormal(double x, double y, double z);
};

class Sphere: public Shape {
    public:
        float center_x;
        float center_y;
        float center_z;

        float radius;
        Sphere(float Kd, float Ks, float Ka, Color Od, Color Os, float Kgls, float center_x, float center_y, float center_z, float radius): Shape(Kd, Ks, Ka, Od, Os, Kgls), center_x(center_x), center_y(center_y), center_z(center_z), radius(radius) {}
        double findRayCollision(double x0, double y0, double z0, double xd, double yd, double zd) override;
        Ray returnNormal(double x, double y, double z) override;
};