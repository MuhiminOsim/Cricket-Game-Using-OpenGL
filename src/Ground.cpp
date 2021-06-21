#include "Ground.h"
#include "Cube.h"
#include "Sphere.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

Ground::Ground() {
    r = 255;
    g = 255;
    b = 255;
    radius = 10;
}

Ground::Ground(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _radius) {
    r = _r;
    g = _g;
    b = _b;
    radius = _radius;
}

void Ground::draw(GLuint ID) {
    glPushMatrix();
        glTranslated(0, -1, 0);
        glScaled(300, 1, 300);
        Cube c(r, g, b);
        c.drawTex(ID);
    glPopMatrix();
}
