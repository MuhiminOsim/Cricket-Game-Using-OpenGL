#include "Cylinder.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>

Cylinder::Cylinder(){
    r = 255;
    g = 255;
    b = 255;
    r1 = 0;
    r2 = 2.0;
}

Cylinder::Cylinder(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _r1, GLfloat _r2, GLfloat _height) {
    r = _r;
    g = _g;
    b = _b;
    r1 = _r1;
    r2 = _r2;
    height = _height;
}

void Cylinder::draw() {
    glPushMatrix();
        GLfloat mat_no[] = {0, 0, 0, 1.0};
        GLfloat mat_amb[] = {r / 255.0, g / 255.0, b / 255.0, 1};
        GLfloat mat_diff[] = {r / 255.0, g / 255.0, b / 255.0, 1};
        GLfloat mat_spec[] = {1, 1, 1, 1};
        GLfloat mat_sh[] = {40};

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_sh);

        glRotated(270, 1, 0, 0);
        gluCylinder(gluNewQuadric(), r1, r2, height, 100, 100);
    glPopMatrix();
}

void Cylinder::drawTex(GLuint ID) {
    glPushMatrix();
        GLfloat mat_no[] = {0, 0, 0, 1.0};
        GLfloat mat_amb[] = {0.8, 0.8, 0.8, 1};
        GLfloat mat_diff[] = {1, 1, 1, 1};
        GLfloat mat_spec[] = {1, 1, 1, 1};
        GLfloat mat_sh[] = {80};

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_sh);

        glRotated(270, 1, 0, 0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ID);
        GLUquadric *quad;
        quad = gluNewQuadric();
        gluQuadricTexture(quad, TRUE);
        gluCylinder(quad, r1, r2, height, 50, 50);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

