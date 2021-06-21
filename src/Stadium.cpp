#include "Stadium.h"
#include "Cylinder.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

Stadium::Stadium() {
    r = 255;
    g = 255;
    b = 255;
    radius = 10;
    level = 10;
}

Stadium::Stadium(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _radius, int _level) {
    r = _r;
    g = _g;
    b = _b;
    radius = _radius;
    level = _level;
}

void Stadium::draw(GLuint ID) {
    glPushMatrix();
        //glTranslated(0, -radius + 30, 0);
        glPushMatrix();
            for(int i = 0; i < level; i++) {
                //Cylinder c(r, g, b, 0, radius + (i * 5), radius);
                Cylinder c(r, g, b, radius, radius + 20, 35);
                c.drawTex(ID);
            }
        glPopMatrix();
    glPopMatrix();
}
