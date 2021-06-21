#ifndef FLOODLIGHT_H
#define FLOODLIGHT_H
#include <GL/gl.h>

class FloodLight {
    public:
        GLfloat r, g, b, lx, lz;
        FloodLight();
        FloodLight(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _lx, GLfloat _lz);
        void draw(int isOn = 0);
        void drawStand(GLfloat x, GLfloat z, int isOn = 0);
};

#endif // FLOODLIGHT_H
