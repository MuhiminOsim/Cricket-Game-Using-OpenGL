#ifndef STADIUM_H
#define STADIUM_H
#include <GL/gl.h>

class Stadium
{
    GLfloat r, g, b, radius;
    int level;
    public:
        Stadium();
        Stadium(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _radius, int _level);
        void draw(GLuint ID);
};

#endif // STADIUM_H
