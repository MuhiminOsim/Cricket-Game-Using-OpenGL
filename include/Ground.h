#ifndef GROUND_H
#define GROUND_H
#include <GL/gl.h>

class Ground {
    GLfloat r, g, b, radius;
    public:
        Ground();
        Ground(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _radius);
        void draw(GLuint ID);
};

#endif // GROUND_H
