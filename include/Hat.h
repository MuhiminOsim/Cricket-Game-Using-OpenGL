#ifndef HAT_H
#define HAT_H
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


const double PI = 3.14159265389;
const int L=24;
const int dgre=3;
static  int ncpt=L+1;
const int nt = 40;				//number of slices along x-direction
const int ntheta = 20;

static GLfloat ctrlpoints[L+1][3] =
{
    { 0.0, 0.0, 0.0}, { 0.0, 0.5, 0.0},
    { 0.0, 1.0, 0.0}, { 0.0, 2.0, 0.0},
    { 0.0, 3.0, 0.0}, { 0.0, 2.5, 0.0},
    { 0.05, 2.0, 0.0}, { 0.05, 1.5, 0.0},
    { 0.1, 1, 0.0}, { 0.1, 0.875, 0.0},
    { 0.15, 0.875, 0.0}, { 0.15, 0.75, 0.0},
    { 0.2, 0.75, 0.0}, { 0.25, 0.875, 0.0},
    { 0.4, 0.875, 0.0}, { 0.6, 0.875, 0.0},
    { 0.9, 0.875, 0.0}, { 1.0, 0.875, 0.0},
    { 1.1, 0.875, 0.0}, { 1.05, 0.75, 0.0},
    { 1.0, 0.6, 0.0}, { 0.95, 0.5, 0.0},
    { 0.95, 0.4, 0.0}, { 0.9, 0.2, 0.0},
    { 0.9, 0.0, 0.0}
};

static long long nCr(int n, int r);
static void BezierCurve ( double t,  float xy[2]);
static void setNormal(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3);
static void matColor(GLfloat r, GLfloat g, GLfloat b, GLfloat shininess);

class Hat {
    public:
        GLfloat lx, ly, lz, r, g, b, radius;
        Hat();
        Hat(GLfloat _lx, GLfloat _ly, GLfloat _lz, GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _radius);
        void draw();
        void showControlPoints();
};

#endif // HAT_H
