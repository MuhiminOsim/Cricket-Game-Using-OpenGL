#ifndef PITCH_H
#define PITCH_H
#include <GL/gl.h>

class Pitch {
    GLfloat r, g, b, length, width;
    public:
        Pitch();
        Pitch(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _length, GLfloat _width);
        void draw(GLuint ID);

};

#endif // PITCH_H
