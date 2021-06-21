#ifndef STUMP_H
#define STUMP_H
#include <GL/gl.h>

class Stump {
    public:
        GLfloat r, g, b, lx, lz;
        GLint fStump, isOut;
        Stump();
        Stump(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _lx, GLfloat _lz, GLint _fStump);
        void draw();
        void drawStand(GLfloat x, GLfloat z, int sl);
        void drawBell(GLfloat x, GLfloat z);
};

#endif // STUMP_H
