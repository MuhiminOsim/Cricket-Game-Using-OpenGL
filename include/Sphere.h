#ifndef SPHERE_H
#define SPHERE_H
#include <GL/gl.h>
#include <GL/glu.h>


class Sphere {
    GLfloat r, g, b, radius;
    int isLight;
    public:
        Sphere();
        Sphere(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _radius, int _isLight = 0);
        void draw(int isOn = 0);
        void drawTex(GLuint ID);
};

#endif // SPHERE_H
