#include "Pitch.h"
#include "Cube.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

Pitch::Pitch() {
    r = 255;
    g = 255;
    b = 255;
    length = 20;
    width = 10;
}

Pitch::Pitch(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _length, GLfloat _width) {
    r = _r;
    g = _g;
    b = _b;
    length = _length;
    width = _width;
}

void Pitch::draw(GLuint ID) {
    glPushMatrix();
        glTranslated(0, -0.95, 0);
        glScaled(width, 1, length);
        Cube c(r, g, b);
        c.drawTex(ID);
    glPopMatrix();
}
