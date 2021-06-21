#include "Sphere.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

Sphere::Sphere(){
    r = 255;
    g = 255;
    b = 255;
    radius = 1.0;
    isLight = 0;
}

Sphere::Sphere(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _radius, int _isLight) {
    r = _r;
    g = _g;
    b = _b;
    radius = _radius;
    isLight = _isLight;
}

void Sphere::draw(int isOn) {
    glPushMatrix();
        GLfloat mat_no[] = {0, 0, 0, 1.0};
        GLfloat mat_amb[] = {r / 255.0, g / 255.0, b / 255.0, 1};
        GLfloat mat_diff[] = {r / 255.0, g / 255.0, b / 255.0, 1};
        GLfloat mat_spec[] = {1, 1, 1, 1};
        GLfloat mat_sh[] = {40};
        GLfloat mat_em[] = {1, 1, 1, 1};

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_sh);

        if(isLight && isOn) glMaterialfv(GL_FRONT, GL_EMISSION, mat_em);
        else glMaterialfv(GL_FRONT, GL_EMISSION, mat_no);

        glutSolidSphere(radius, 100, 100);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_no);
    glPopMatrix();
}

void Sphere::drawTex(GLuint ID) {
    glPushMatrix();
        GLfloat mat_no[] = {0, 0, 0, 1.0};
        GLfloat mat_amb[] = {0.2, 0.2, 0.2, 1};
        GLfloat mat_diff[] = {1, 1, 1, 1};
        GLfloat mat_spec[] = {1, 1, 1, 1};
        GLfloat mat_sh[] = {40};

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_sh);

        glBindTexture(GL_TEXTURE_2D, ID);
        glEnable(GL_TEXTURE_2D);
        GLUquadric *quad;
        quad = gluNewQuadric();
        gluQuadricTexture(quad, TRUE);
        gluSphere(quad,radius,100,20);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
