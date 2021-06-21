#include "Cube.h"
#include "Sphere.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

static void getNormal3p(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3) {
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

Cube::Cube() {
    r = 255;
    g = 255;
    b = 255;
    shininess = 40;
    isLight = 0;
}

Cube::Cube(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _shininess, int _isLight) {
    r = _r;
    g = _g;
    b = _b;
    shininess = _shininess;
    isLight = _isLight;
}

void Cube::draw(int isOn) {
    glPushMatrix();
        GLfloat mat_no[] = {0, 0, 0, 1.0};
        GLfloat mat_amb[] = {r / 255.0, g / 255.0, b / 255.0, 1};
        GLfloat mat_diff[] = {r / 255.0, g / 255.0, b / 255.0, 1};
        GLfloat mat_spec[] = {0.8, 0.8, 0.8, 1};
        GLfloat mat_sh[] = {shininess};
        GLfloat mat_em[] = {1, 1, 1, 1};

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_sh);

        if(isLight && isOn) glMaterialfv(GL_FRONT, GL_EMISSION, mat_em);
        else glMaterialfv(GL_FRONT, GL_EMISSION, mat_no);

        glBegin(GL_QUADS);
        for (GLint i = 0; i <6; i++) {
            getNormal3p(v_rectangle[quadIndices[i][0]][0], v_rectangle[quadIndices[i][0]][1], v_rectangle[quadIndices[i][0]][2],
                        v_rectangle[quadIndices[i][1]][0], v_rectangle[quadIndices[i][1]][1], v_rectangle[quadIndices[i][1]][2],
                        v_rectangle[quadIndices[i][2]][0], v_rectangle[quadIndices[i][2]][1], v_rectangle[quadIndices[i][2]][2]);
            glVertex3fv(&v_rectangle[quadIndices[i][0]][0]);
            glVertex3fv(&v_rectangle[quadIndices[i][1]][0]);
            glVertex3fv(&v_rectangle[quadIndices[i][2]][0]);
            glVertex3fv(&v_rectangle[quadIndices[i][3]][0]);
        }
        glEnd();
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_no);
    glPopMatrix();
}

void Cube::drawTex(GLuint ID, int isOn) {
    glPushMatrix();
        GLfloat mat_no[] = {0, 0, 0, 1.0};
        GLfloat mat_amb[] = {0.2, 0.2, 0.2, 1};
        GLfloat mat_diff[] = {1, 1, 1, 1};
        GLfloat mat_spec[] = {1, 1, 1, 1};
        GLfloat mat_sh[] = {shininess};
        GLfloat mat_em[] = {1, 1, 1, 1};

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_sh);

        if(isLight && isOn) glMaterialfv(GL_FRONT, GL_EMISSION, mat_em);
        else glMaterialfv(GL_FRONT, GL_EMISSION, mat_no);

        glBindTexture(GL_TEXTURE_2D, ID);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        for (GLint i = 0; i <6; i++) {
            getNormal3p(v_rectangle[quadIndices[i][0]][0], v_rectangle[quadIndices[i][0]][1], v_rectangle[quadIndices[i][0]][2],
                        v_rectangle[quadIndices[i][1]][0], v_rectangle[quadIndices[i][1]][1], v_rectangle[quadIndices[i][1]][2],
                        v_rectangle[quadIndices[i][2]][0], v_rectangle[quadIndices[i][2]][1], v_rectangle[quadIndices[i][2]][2]);
            glVertex3fv(&v_rectangle[quadIndices[i][0]][0]);glTexCoord2f(1,1);
            glVertex3fv(&v_rectangle[quadIndices[i][1]][0]);glTexCoord2f(1,0);
            glVertex3fv(&v_rectangle[quadIndices[i][2]][0]);glTexCoord2f(0,0);
            glVertex3fv(&v_rectangle[quadIndices[i][3]][0]);glTexCoord2f(0,1);
        }
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Cube::setColor(GLfloat _r, GLfloat _g, GLfloat _b) {
    r = _r;
    g = _g;
    b = _b;
}


