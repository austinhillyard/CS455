class RayTracer {

    private:
        double pixel_locations;


        void buildScreen();

    public:
        // Takes in a screen size, and the camera position on the z axis. 
        // Camera is assumed to be on the z axis looking toward the origin, with the screen on the x-y plane
        RayTracer(unsigned int screen_width, unsigned int screen_height, unsigned int camera_z_position);

    

};