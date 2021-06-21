#include "Hat.h"
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//control points
static long long nCr(int n, int r) {
    if(r > n / 2) r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for(i = 1; i <= r; i++) {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
static void BezierCurve ( double t,  float xy[2]) {
    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0; i<=L; i++) {
        int ncr=nCr(L,i);
        double oneMinusTpow=pow(1-t,double(L-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints[i][0];
        y+=coef*ctrlpoints[i][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}

static void setNormal(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3) {
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

    glNormal3f(-Nx,-Ny,-Nz);
}

static void matColor(GLfloat r, GLfloat g, GLfloat b, GLfloat shininess) {
    GLfloat mat_amb[] = {r / 255.0, g / 255.0, b / 255.0, 1};
    GLfloat mat_diff[] = {r / 255.0, g / 255.0, b / 255.0, 1};
    GLfloat mat_spec[] = {1, 1, 1, 1};
    GLfloat mat_sh[] = {shininess};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_sh);
}

Hat::Hat() {
    lx = 0, ly = 12.75, lz = 0;
    r = 155, g = 155, b = 155;
    radius = 2;
}

Hat::Hat(GLfloat _lx, GLfloat _ly, GLfloat _lz, GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _radius) {
    lx = _lx, ly = _ly, lz = _lz;
    r = _r, g = _g, b = _b;
    radius = _radius;
}

void Hat::showControlPoints() {
    glPointSize(3.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    for (int i = 0; i <=L; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
}

void Hat::draw() {
    glPushMatrix();
        glTranslated(lx, ly, lz);
        glRotated(90, 0, 0, 1);
        glScaled(radius / 1.5, radius, radius);
        glPushMatrix();
            matColor(r, g, b, 50);
            int i, j;
            float x, y, z, r;				//current coordinates
            float x1, y1, z1, r1;			//next coordinates
            float theta;

            const float startx = 0, endx = ctrlpoints[L][0];
            //number of angular slices
            const float dx = (endx - startx) / nt;	//x step size
            const float dtheta = 2*PI / ntheta;		//angular step size

            float t=0;
            float dt=1.0/nt;
            float xy[2];
            BezierCurve( t,  xy);
            x = xy[0];
            r = xy[1];
            //rotate about z-axis
            float p1x,p1y,p1z,p2x,p2y,p2z;
            for ( i = 0; i < nt; ++i ) { //step through x
                theta = 0;
                t+=dt;
                BezierCurve( t,  xy);
                x1 = xy[0];
                r1 = xy[1];

                //draw the surface composed of quadrilaterals by sweeping theta
                glBegin( GL_QUAD_STRIP );
                for ( j = 0; j <= ntheta; ++j ) {
                    //if(j >= 13 && j <= 14) matColor(0, 0, 0, 50);
                    //else matColor(r, g, b, 50);
                    theta += dtheta;
                    double cosa = cos( theta );
                    double sina = sin ( theta );
                    y = r * cosa;
                    y1 = r1 * cosa;	//current and next y
                    z = r * sina;
                    z1 = r1 * sina;	//current and next z

                    //edge from point at x to point at next x
                    glVertex3f (x, y, z);

                    if(j>0) {
                        setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
                    }
                    else {
                        p1x=x;
                        p1y=y;
                        p1z=z;
                        p2x=x1;
                        p2y=y1;
                        p2z=z1;

                    }
                    glVertex3f (x1, y1, z1);

                    //forms quad with next pair of points with incremented theta value
                }
                glEnd();
                x = x1;
                r = r1;
            }
        glPopMatrix();
    glPopMatrix();
}
