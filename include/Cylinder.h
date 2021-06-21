#ifndef Cylinder_H
#define Cylinder_H
#include <GL/gl.h>

class Cylinder {
    GLfloat r, g, b, r1, r2, height;
    public:
        Cylinder();
        Cylinder(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _r1, GLfloat _r2, GLfloat _height);
        void draw();
        void drawTex(GLuint ID);
};

#endif // Cylinder_H
