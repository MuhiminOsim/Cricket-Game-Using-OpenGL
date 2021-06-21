#include "Stump.h"
#include "Cube.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

Stump::Stump(){
    r = 255, g = 255, b = 255;
    lx = 0, lz = 0;
    fStump = 0;
    isOut = 0;
}

Stump::Stump(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _lx, GLfloat _lz, GLint _fStump) {
    r = _r, g = _g, b = _b;
    lx = _lx, lz = _lz;
    fStump = _fStump;
    isOut = 0;
}

void Stump::drawStand(GLfloat x, GLfloat z, int sl) {
    glPushMatrix();
        glTranslated(x, 0, z);
        glPushMatrix();
        if(isOut && fStump) {
            glRotated(-15, 1, 0, 0);
            if(sl == 1) glRotated(15, 0, 0, 1);
            if(sl == 3) glRotated(-15, 0, 0, 1);
        }
        glPushMatrix();
            glScaled(0.25, 4.5, 0.25);
            for(int i = 0; i < 3; i++) {
                glRotated(i * 60, 0, 1, 0);
                Cube c(r, g, b);
                c.draw();
            }
        glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Stump::drawBell(GLfloat x, GLfloat z) {
    glPushMatrix();
        glTranslated(x, 4.5, z);
        if(!isOut || !fStump) {
            glPushMatrix();
                glScaled(0.8, 0.15, 0.15);
                for(int i = 0; i < 3; i++) {
                    glRotated(i * 60, 1, 0, 0);
                    Cube c(r, g, b);
                    c.draw();
                }
            glPopMatrix();
        }
    glPopMatrix();
}

void Stump::draw() {
    glPushMatrix();
        drawStand(lx, lz, 2);
        drawStand(lx - 0.7, lz, 1);
        drawStand(lx + 0.7, lz, 3);
        drawBell(lx - 0.45, lz);
        drawBell(lx + 0.45, lz);
    glPopMatrix();
}
