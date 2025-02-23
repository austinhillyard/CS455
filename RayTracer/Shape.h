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
        virtual double findRayCollision(float x0, float y0, float z0, float xd, float yd, float zd);
};

class Sphere: public Shape {
    public:
        float center_x;
        float center_y;
        float center_z;

        float radius;
        Sphere(float Kd, float Ks, float Ka, Color Od, Color Os, float Kgls, float center_x, float center_y, float center_z, float radius): Shape(Kd, Ks, Ka, Od, Os, Kgls), center_x(center_x), center_y(center_y), center_z(center_z), radius(radius) {}
        double findRayCollision(float x0, float y0, float z0, float xd, float yd, float zd) override;
};