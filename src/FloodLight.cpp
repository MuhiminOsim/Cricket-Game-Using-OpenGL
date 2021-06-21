#include "FloodLight.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cylinder.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define pi acos(-1.0)

FloodLight::FloodLight(){
    r = 255, g = 255, b = 255;
    lx = 0, lz = 0;
}

FloodLight::FloodLight(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _lx, GLfloat _lz) {
    r = _r, g = _g, b = _b;
    lx = _lx, lz = _lz;
}

void FloodLight::drawStand(GLfloat x, GLfloat z, int isOn) {
    glPushMatrix();
        glPushMatrix();
            glTranslated(x, 0, z);
            glPushMatrix();
                Cylinder c(r, g, b, 1, 1, 50);
                c.draw();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glTranslated(x, 49, z);
            glRotated(45, 1, 0, 0);
            glPushMatrix();
                Cylinder c1(r, g, b, 0.75, 0.75, 20);
                c1.draw();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glTranslated(x, 49, z);
            glRotated(45, 1, 0, 0);
            glPushMatrix();
                for(int i = 0; i < 4; i++) {
                    glPushMatrix();
                        glTranslated(0, 19 - (i * 5), 0);
                        glScaled(12, 1, 1);
                        Cube c(r, g, b);
                        c.draw();
                    glPopMatrix();
                }
            glPopMatrix();
            glPushMatrix();
                for(int i = 0; i < 4; i++) {
                    for(int j = 0; j < 4; j++) {
                        glPushMatrix();
                            glTranslated(-5 + (j * 3), 19 - (i * 5), 1);
                            Sphere s(r, g, b, 1.5, 1);
                            s.draw(isOn);
                        glPopMatrix();
                    }
                }
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void FloodLight::draw(int isOn) {
    glPushMatrix();
        double theta = (atan2(lx, -lz) * 180) / pi;
        glTranslated(lx, 0, lz);
        glRotated(-theta, 0, 1, 0);
        glTranslated(-lx, 0, -lz);
        glPushMatrix();
            drawStand(lx, lz, isOn);
        glPopMatrix();
    glPopMatrix();
}
