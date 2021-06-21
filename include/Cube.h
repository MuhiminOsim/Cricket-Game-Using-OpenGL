#ifndef CUBE_H
#define CUBE_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static GLfloat v_rectangle[8][3] =
{
    {-0.5, 0, -0.5},
    {-0.5, 0, 0.5},
    {-0.5, 1, -0.5},
    {-0.5, 1, 0.5},
    {0.5, 0, -0.5},
    {0.5, 0, 0.5},
    {0.5, 1, -0.5},
    {0.5, 1, 0.5}
};

static GLubyte quadIndices[6][4] =
{
    {0, 2, 6, 4},
    {1, 5, 7, 3},
    {0, 4, 5, 1},
    {2, 3, 7, 6},
    {0, 1, 3, 2},
    {4, 6, 7, 5}
};

static void getNormal3p(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3);

class Cube {
    GLfloat r, g, b, shininess;
    int isLight;
    public:
        Cube();
        Cube(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _shininess = 40, int _isLight = 0);
        void draw(int isOn = 0);
        void drawTex(GLuint ID, int isOn = 0);
        void setColor(GLfloat _r, GLfloat _g, GLfloat _b);
};

#endif // CUBE_H
