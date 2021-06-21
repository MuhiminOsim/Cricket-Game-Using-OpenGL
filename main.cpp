#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <string>
#include "Cricketer.h"
#include "Cylinder.h"
#include "Cube.h"
#include "Sphere.h"
#include "Ground.h"
#include "Pitch.h"
#include "Stadium.h"
#include "Stump.h"
#include "BmpLoader.h"
#include "FloodLight.h"
#include "Hat.h"
#include "DotMatrixDisplay.h"
using namespace std;

const double pi = acos(-1.0);

GLuint texID[50], texIdx = 0;
int isBowl = 0, isBat = 0, isBall = 0, isDropped = 0, isRandom = 0, isEnded = 0;
int isHit = 0, nrun = 0, totalRuns = 0, wickets = 0, target = 0, showCP = 0;
int shot = 6, innings = 1, isHelp = 1, isRestarted = 0, isBirdView = 0;

Sphere ball(255, 255, 255, 0.5);
Cricketer bowler(-5, 70, 2, 12);
Cricketer batsman(1.5, -15, 1, 12);
Stump s2(152, 152, 152, 0, -21, 1);

double sx[] = {-2.5, -2.25, -1.5, -0.25};
double sy[] = {4, 4, 4, 3};

double ballHeight = 10;
double ddx, ddy, ddz = 2;
double bline = -1, blength = -5;
double angle = 0;
double bx = -4.5, by = 11, bz = 23;
double lx = 0, ly = 30, lz = 120, rx = 0, ry = 80, rz = -30, ux = 0, uy = 1, uz = 0;
double maxBack = 250, maxFront = -250;
double dx, dy, dz, bigger, increase = 1;
double windowHeight = 1000, windowWidth = 1500;
double aspect_ratio = windowHeight / windowWidth;
GLboolean light[] = {false, true, true, false, true, false};
GLboolean amb = true, dif = true, spec = true;
GLboolean batDirection = true, wired = false;

void ownTranslatef(GLfloat dx, GLfloat dy, GLfloat dz) {

	GLfloat m[16];

	m[0] = 1;	m[4] = 0;  	 m[8] = 0;   	m[12] = dx;
	m[1] = 0; 	m[5] = 1; 	 m[9] = 0;   	m[13] = dy;
	m[2] = 0; 	m[6] = 0;	 m[10] = 1; 	m[14] = dz;
	m[3] = 0; 	m[7] = 0; 	 m[11] = 0; 	m[15] = 1;

	glMatrixMode(GL_MODELVIEW);
	glMultMatrixf(m);
}

void showAxes() {
    glPushMatrix();
    glScaled(10, 1, 1);
    Cube c1(255, 0, 0);
    c1.draw();
    glPopMatrix();

    glPushMatrix();
    glScaled(1, 10, 1);
    Cube c2(0, 255, 0);
    c2.draw();
    glPopMatrix();

    glPushMatrix();
    glScaled(1, 1, 10);
    Cube c3(0, 0, 255);
    c3.draw();
    glPopMatrix();
}

void light1() {
    //light
    GLfloat light_no[] = {0, 0, 0, 1.0};
    GLfloat light_amb[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_dif[] = {1, 1, 1, 1};
    GLfloat light_spec[] = {1, 1, 1, 1};
    GLfloat light_pos[] = {100, 64, -100, 1.0};

    glEnable(GL_LIGHT0);

    if(light[1] && amb) glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
    else glLightfv(GL_LIGHT0, GL_AMBIENT, light_no);
    if(light[1] && dif) glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
    else glLightfv(GL_LIGHT0, GL_DIFFUSE, light_no);
    if(light[1] && spec) glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);
    else glLightfv(GL_LIGHT0, GL_SPECULAR, light_no);

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void light2() {
    //light
    GLfloat light_no[] = {0, 0, 0, 1.0};
    GLfloat light_amb[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_dif[] = {.8, .8, .8, 1};
    GLfloat light_spec[] = {1, 1, 1, 1};
    GLfloat light_pos[] = {-150, 64, -150, 1.0};

    glEnable(GL_LIGHT1);

    if(light[2] && amb) glLightfv(GL_LIGHT1, GL_AMBIENT, light_amb);
    else glLightfv(GL_LIGHT1, GL_AMBIENT, light_no);
    if(light[2] && dif) glLightfv(GL_LIGHT1, GL_DIFFUSE, light_dif);
    else glLightfv(GL_LIGHT1, GL_DIFFUSE, light_no);
    if(light[2] && spec) glLightfv(GL_LIGHT1, GL_SPECULAR, light_spec);
    else glLightfv(GL_LIGHT1, GL_SPECULAR, light_no);

    glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
}

void light3() {
    GLfloat light_no[] = {0, 0, 0, 1.0};
    GLfloat light_amb[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_dif[] = {1, 1, 1, 1};
    GLfloat light_spec[] = {1, 1, 1, 1};
    GLfloat light_pos[] = {150, 64, 150, 1.0};

    glEnable(GL_LIGHT3);

    if(light[3] && amb) glLightfv(GL_LIGHT3, GL_AMBIENT, light_amb);
    else glLightfv(GL_LIGHT3, GL_AMBIENT, light_no);
    if(light[3] && dif) glLightfv(GL_LIGHT3, GL_DIFFUSE, light_dif);
    else glLightfv(GL_LIGHT3, GL_DIFFUSE, light_no);
    if(light[3] && spec) glLightfv(GL_LIGHT3, GL_SPECULAR, light_spec);
    else glLightfv(GL_LIGHT3, GL_SPECULAR, light_no);

    glLightfv(GL_LIGHT3, GL_POSITION, light_pos);
}

void light4() {
    GLfloat light_no[] = {0, 0, 0, 1.0};
    GLfloat light_amb[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_dif[] = {.8, .8, .8, 1};
    GLfloat light_spec[] = {1, 1, 1, 1};
    GLfloat light_pos[] = {-150, 64, 150, 1.0};

    glEnable(GL_LIGHT4);

    if(light[4] && amb) glLightfv(GL_LIGHT4, GL_AMBIENT, light_amb);
    else glLightfv(GL_LIGHT4, GL_AMBIENT, light_no);
    if(light[4] && dif) glLightfv(GL_LIGHT4, GL_DIFFUSE, light_dif);
    else glLightfv(GL_LIGHT4, GL_DIFFUSE, light_no);
    if(light[4] && spec) glLightfv(GL_LIGHT4, GL_SPECULAR, light_spec);
    else glLightfv(GL_LIGHT4, GL_SPECULAR, light_no);

    glLightfv(GL_LIGHT4, GL_POSITION, light_pos);
}

void spotlight() {
    //light
    GLfloat light_no[] = {0, 0, 0, 1.0};
    GLfloat light_amb[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_dif[] = {0.8, 0.8, 0.8, 1};
    GLfloat light_spec[] = {.8, .8, .8, 1};
    GLfloat light_pos[] = {0, 50, 0, 1.0};

    glEnable(GL_LIGHT5);

    if(light[5] && amb) glLightfv(GL_LIGHT5, GL_AMBIENT, light_amb);
    else glLightfv(GL_LIGHT5, GL_AMBIENT, light_no);
    if(light[5] && dif) glLightfv(GL_LIGHT5, GL_DIFFUSE, light_dif);
    else glLightfv(GL_LIGHT5, GL_DIFFUSE, light_no);
    if(light[5] && spec) glLightfv(GL_LIGHT5, GL_SPECULAR, light_spec);
    else glLightfv(GL_LIGHT5, GL_SPECULAR, light_no);

    glLightfv(GL_LIGHT5, GL_POSITION, light_pos);

     GLfloat light_spot[] = {0, -1, 0, 1};
     GLfloat spot_cutoff[] = {45};
     glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, light_spot);
     glLightfv(GL_LIGHT5, GL_SPOT_CUTOFF, spot_cutoff);
}

void controlBall() {
    if(!isBall) return;
    glPushMatrix();
        glTranslated(bx, by, bz);
        ball.draw();
    glPopMatrix();
}

void deployFielder() {
    Cricketer f1(-5, -50, 3, 12);
    f1.draw(texID[3]);

    Cricketer f2(-45, -45, 3, 12);
    f2.faceAngle = 30;
    f2.draw(texID[3]);
    Cricketer f3(40, -120, 3, 12);
    f3.faceAngle = -30;
    f3.draw(texID[3]);

    Cricketer f4(80, -20, 3, 12);
    f4.faceAngle = -90;
    f4.draw(texID[3]);

    Cricketer f5(-40, 40, 3, 12);
    f5.faceAngle = 150;
    f5.draw(texID[3]);

    Cricketer f6(80, 80, 3, 12);
    f6.faceAngle = 150;
    f6.draw(texID[3]);
}

void drawCross() {
    glPushMatrix();
        glScaled(3, 0.6, 0.6);
        Cube c1(255, 0, 0);
        c1.draw();
    glPopMatrix();
    glPushMatrix();
        glScaled(0.6, 0.6, 3);
        Cube c2(255, 0, 0);
        c2.draw();
    glPopMatrix();
}

string to_string(int x) {
    if(x == 0) return "0";
    string ret = "";
    while(x) {
        ret += (char)('0' + (x % 10));
        x /= 10;
    }
    for(int i = 0, j = ret.size() - 1; i < j; i++, j--) {
        char ch = ret[i];
        ret[i] = ret[j];
        ret[j] = ch;
    }
    return ret;
}

string dynamicBar;

void drawScoreCard() {
    glPushMatrix();
        glTranslated(0, 0, -160);
        glScaled(80, 40, 1);
        Cube card(0, 0, 0);
        card.draw();
    glPopMatrix();

    DotMatrixDisplay dotMatrixDisplay(2);
    dotMatrixDisplay.setScale(1);
    string curRuns = "RUNS - " + to_string(totalRuns);
    string curWickets = "WICKETS - " + to_string(wickets);
    string curInnings = "INNINGS-1ST";

    glPushMatrix();
        glTranslatef(-10, 35, -159.5);
        glScalef(0.5, 0.5, 0.5);
        dotMatrixDisplay.drawMessage(curRuns, 0, 255, 0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-20, 25, -159);
        glScalef(0.5, 0.5, 0.5);
        dotMatrixDisplay.drawMessage(curWickets, 255, 0, 0);
    glPopMatrix();

    if(innings == 1) {
        glPushMatrix();
            glTranslatef(-27, 15, -159.5);
            glScalef(0.5, 0.5, 0.5);
            dotMatrixDisplay.drawMessage(curInnings, 255, 255, 255);
        glPopMatrix();
    }
    else {
        glPushMatrix();
            glTranslatef(-27, 15, -159.5);
            glScalef(0.5, 0.5, 0.5);
            dotMatrixDisplay.drawMessage(dynamicBar, 255, 255, 255);
        glPopMatrix();
    }
}

static void resize(int windowWidth, int windowHeight) {
    glViewport(0, 0, windowWidth, windowWidth / aspect_ratio);
}

void showHelps();

void drawGroundMarking() {
    glPushMatrix();
        Cylinder boundary(255, 255, 255, 135, 135, 0.3);
        boundary.draw();

        Cylinder thirtyLine(255, 255, 255, 70, 70, 0.5);
        thirtyLine.draw();

        glPushMatrix();
            //glTranslated(0, 5, 0);
            Cylinder ad(255, 255, 255, 150, 150, 4.5);
            ad.drawTex(texID[6]);
        glPopMatrix();

        glPushMatrix();
            glTranslated(0, -0.4, -15);
            glScaled(30, 0.5, 0.5);
            Cube c1(255, 255, 255);
            c1.draw();
        glPopMatrix();

        glPushMatrix();
            glTranslated(0, -0.4, 15);
            glScaled(30, 0.5, 0.5);
            Cube c2(255, 255, 255);
            c2.draw();
        glPopMatrix();

        glPushMatrix();
            glTranslated(-9, -0.4, -20);
            glScaled(0.5, 0.5, 10);
            Cube c3(255, 255, 255);
            c3.draw();
        glPopMatrix();

        glPushMatrix();
            glTranslated(9, -0.4, -20);
            glScaled(0.5, 0.5, 10);
            Cube c4(255, 255, 255);
            c4.draw();
        glPopMatrix();

        glPushMatrix();
            glTranslated(-9, -0.4, 20);
            glScaled(0.5, 0.5, 10);
            Cube c5(255, 255, 255);
            c5.draw();
        glPopMatrix();

        glPushMatrix();
            glTranslated(9, -0.4, 20);
            glScaled(0.5, 0.5, 10);
            Cube c6(255, 255, 255);
            c6.draw();
        glPopMatrix();

        glPushMatrix();
            glTranslated(0, -0.4, -21);
            glScaled(18, 0.5, 0.5);
            Cube c7(255, 255, 255);
            c7.draw();
        glPopMatrix();

        glPushMatrix();
            glTranslated(0, -0.4, 21);
            glScaled(18, 0.5, 0.5);
            Cube c8(255, 255, 255);
            c8.draw();
        glPopMatrix();

        glPushMatrix();
            glTranslated(bline, -0.2, blength);
            drawCross();
        glPopMatrix();
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    if(wired) {
        glPolygonMode( GL_FRONT, GL_LINE ) ;
        glPolygonMode( GL_BACK, GL_LINE ) ;

    }
    else {
        glPolygonMode( GL_FRONT,GL_FILL ) ;
        glPolygonMode( GL_BACK, GL_FILL ) ;
    }

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-3, 3, -3, 3, 2, 500);
    gluPerspective(115, aspect_ratio, 0.1, 600);
    //glOrtho(-5,5,-5,5, 4, 50);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(lx, ly, lz, rx, ry, rz, ux, uy, uz);

    spotlight();
    light1();
    light2();
    light3();
    light4();

    if(isHelp) {
        showHelps();
    }
    else {
        glRotated(angle, 0, 1, 0);

        //showAxes();
        Stadium stadium(255, 255, 255, 160, 1);
        stadium.draw(texID[2]);

        drawGroundMarking();

        drawScoreCard();

        Cricketer umpire(0, 35, 4, 12);
        umpire.draw(texID[5]);
        if(showCP) umpire.h.showControlPoints();

        FloodLight f1(200, 200, 200, 150, -150);
        f1.draw(light[1]);

        FloodLight f2(200, 200, 200, -150, -150);
        f2.draw(light[2]);

        FloodLight f3(200, 200, 200, 150, 150);
        f3.draw(light[3]);

        FloodLight f4(200, 200, 200, -150, 150);
        f4.draw(light[4]);


        Ground ground(76, 176, 80, 150);
        ground.draw(texID[0]);

        Pitch pitch(236, 186, 136, 42, 20);
        pitch.draw(texID[1]);

        Stump s1(152, 152, 152, 0, 21, 0);
        s1.draw();
        s2.draw();

        controlBall();

        bowler.draw(texID[3]);
        batsman.draw(texID[4]);

        deployFielder();
    }

    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y ) {
    switch ( key )
    {
    case 'h':
        if(isHelp) isHelp = 0;
        else isHelp = 1;
        break;
    case '[':
        if((batsman.lx - 0.4) >= -10) batsman.lx -= 0.4;
        break;
    case ']':
        if((batsman.lx + 0.4) <= 10) batsman.lx += 0.4;
        break;
    case 'm':
        if(isRandom) isRandom = false;
        else isRandom = true;
        break;
    case 'j':
        if(!isRandom && bowler.lz > 30 && (blength + 1) <= 3) blength += 1;
        break;
    case 'k':
        if(!isRandom && bowler.lz > 30 && (blength - 1) >= -25) blength -= 1;
        break;
    case 'o':
        if(!isRandom && bowler.lz > 30 && (bline - 1) >= -7) bline -= 1;
        break;
    case 'p':
        if(!isRandom && bowler.lz > 30 && (bline + 1) <= 7) bline += 1;
        break;
    case 'z':
        angle -= 4;
        if(angle < 0) angle += 360;
        break;
    case 'x':
        angle += 4;
        if(angle > 360) angle -= 360;
        break;
    case 'b':
        isBowl = 1;
        s2.isOut = 0;
        rx = 0, ry = 80, rz = -30;
        if(isRestarted) {
            totalRuns = 0;
            wickets = 0;
            innings = 1;
            isRestarted = 0;
        }
        break;
    case 'c':
        if(!showCP) showCP = 1;
        else showCP = 0;
        break;
    case 'v':
        if(!isBirdView) {
            isBirdView = 1;
            ly = 150;
            rz = -400;
        }
        else {
            isBirdView = 0;
            ly = 30;
            rz = -30;
        }
        break;
    case 'l':
        if(lx - increase >= maxFront) lx -= increase;
        break;
    case 'r':
        if(lx + increase <= maxBack) lx += increase;
        break;
    case 'F':
        if(lz - increase >= maxFront) lz -= increase;
        break;
    case 'B':
        if(lz + increase <= maxBack) lz += increase;
        break;
    case 'u':
        if(ly + increase <= maxBack) ly += increase;
        break;
    case 'g':
        if(ly - increase >= maxFront) ly -= increase;
        break;
    case 'L':
        rx -= increase;
        break;
    case 'R':
        rx += increase;
        break;
    case 'U':
        ry += increase;
        break;
    case 'D':
        ry -= increase;
        break;
    case '+':
        dx = lx - rx;
        dy = ly - ry;
        dz = lz - rz;
        bigger = max(dx, max(dy, dz));
        dx /= bigger;
        dy /= bigger;
        dz /= bigger;
        lx -= dx * 2;
        ly -= dy * 2;
        lz -= dz * 2;
        break;

    case '-':
        dx = lx - rx;
        dy = ly - ry;
        dz = lz - rz;
        bigger = max(dx, max(dy, dz));
        dx /= bigger;
        dy /= bigger;
        dz /= bigger;
        lx += dx * 2;
        ly += dy * 2;
        lz += dz * 2;
        break;
    case '0':
        totalRuns = 0;
        innings = 1;
        wickets = 0;
        break;
    case '1':
        if(!light[1]) light[1] = true;
        else light[1] = false;
        break;
    case '2':
        if(!light[2]) light[2] = true;
        else light[2] = false;
        break;
    case '3':
        if(!light[3]) light[3] = true;
        else light[3] = false;
        break;
    case '4':
        if(!light[4]) light[4] = true;
        else light[4] = false;
        break;
    case '5':
        if(!light[5]) light[5] = true;
        else light[5] = false;
        break;
    case '6':
        shot = 6;
        break;
    case '7':
        shot = 7;
        break;
    case '8':
        shot = 8;
        break;
    case '9':
        shot = 9;
        break;
    case 'a':
        if(!amb) amb = true;
        else amb = false;
        break;
    case 'd':
        if(!dif) dif = true;
        else dif = false;
        break;
    case 's':
        if(!spec) spec = true;
        else spec = false;
        break;
    case 'w':
        if(!wired) wired = true;
        else wired = false;
        break;
    case 27:	// Escape key
        exit(1);
    }
}

void animate() {
    if(!isRestarted) dynamicBar = "TARGET - " + to_string(target);
    if(isHit) { /// moving the ball if hit by the bat
        rx = bx, ry = by + 42, rz = bz;
        bx += ddx;
        bz += ddz;
        if(isDropped) {
            if((by - ddy) >= 0.5) {
                by -= ddy;
            }
            else {
                isDropped = 0;
                ballHeight -= 1;
            }
        }
        else {
            if((by + ddy) <= ballHeight) {
                by += ddy;
            }
            else {
                isDropped = 1;
            }
        }
        double dist = sqrtl(bx*bx + bz*bz);
        if((isHit == 1 && dist > 180) || (isHit == 2 && dist > 40)) {
            isEnded = 1, isHit = 0;
            totalRuns += nrun;
            if(innings == 2 && totalRuns > target) {
                dynamicBar = "2nd Team Wins!";
                isRestarted = 1;
            }
        }
    }
    if(isBat) {
        if(bowler.lz >= 65) { /// batting initialization
            if(isRandom) {
                int x = rand() % 29;
                blength = x - 25;
                x = rand() % 14;
                bline = -7 + x;
            }
            batsman.faceAngle = 270;
            batsman.bodyAngle = 45;
            batsman.rhlAngle = batsman.lhlAngle = -45;
            batsman.rhuAngle = batsman.lhuAngle = 45;
            batsman.rhAngle = -45;
            batsman.lhAngle = 0;
            batsman.batAngle = -30;
            batsman.slhAngle = 60;
            batsman.srhAngle = 0;
        }
        else if(bowler.lz >= 30) { /// moving bat and measuring ball's translation factor
            double step = (23.0 - blength) / fabs(ddz);
            ddy = 10.5 / step;
            ddy -= 0.05 * (step / 2);
            ddx = (bline + 4.5) / step;
            if(batDirection) {
                batsman.batAngle -= 4;
                if(batsman.batAngle <= -80) {
                    batDirection = 0;
                }
            }
            else {
                batsman.batAngle += 4;
                if(batsman.batAngle >= -30) {
                    batDirection = 1;
                }
            }
        }
        else if(bowler.lz >= 18) { /// executing the shot
            batsman.slhAngle -= 2;
            batsman.srhAngle -= 2;
            if(bowler.lz <= 23) {
                if(!isDropped) {
                    bx += ddx, by = max(by - ddy, 0.5), bz -= ddz;
                    ddy += 0.05;
                    if(by <= 0.6) isDropped = 1, ddy -= 0.3;
                }
                else {
                    bx += ddx, by += ddy, bz -= ddz;
                    ddy -= 0.05;
                }
            }
            ///shot direction
            if(shot == 6) batsman.faceAngle -= 1;
            if(shot == 8) batsman.faceAngle += 1.5;
            if(shot == 9) batsman.faceAngle += 5;
            batsman.lllAngle += 3;
            batsman.rllAngle += 3;
            batsman.lluAngle -= 3;
            batsman.rluAngle -= 3;
            batsman.llAngle += 3;
        }
        else { /// final movement of the batsman and measuring if the ball is hit or not and in which direction
            if(bz == -15 && !isHit) {
                double curx = batsman.lx + sx[shot - 6];
                if(fabs(curx - bx) <= 0.5 && (fabs(by - sy[shot - 6]) <= 2 || by <= sy[shot -6])) {
                    isHit = 1;
                    isDropped = 0;
                    double lev;
                    if(fabs(curx - bx) <= 0.3 && fabs(by - sy[shot - 6]) <= 1.25) {
                        nrun = 6;
                        lev = (curx - bx + 0.3) * (5.0 / 3.0);
                        ddy = 1;
                        ballHeight = 40;
                    }
                    else {
                        nrun = 4;
                        lev = (curx - bx + 0.5);
                        ddy = 0.25;
                        ballHeight = 5;
                        isDropped = 1;
                    }
                    if(shot == 6) {
                        double theta = (pi * lev / 2.0);
                        ddx = -cos(theta);
                        ddz = -sin(theta);
                    }
                    else if(shot == 7) {
                        double theta = (pi * lev / 2.0);
                        ddx = -cos(theta);
                        ddz = sin(theta);
                    }
                    else if(shot == 8) {
                        double theta = (pi * lev / 2.0);
                        ddx = sin(theta);
                        ddz = cos(theta);
                    }
                    else {
                        double theta = (pi * lev / 2.0);
                        ddx = sin(theta);
                        ddz = -cos(theta);
                    }
                    if(nrun == 4) ddx *= 2.5, ddz *= 2.5;
                    else ddx *= 3, ddz *= 3;
                }
                else {
                    nrun = 0;
                    if(by <= 5) {
                        if(bx >= (batsman.lx - 1) && bx <= (batsman.lx + 1)) {
                            isHit = 2;
                        }
                    }
                    else if(by <= 10) {
                        if(bx >= (batsman.lx - 2) && bx <= (batsman.lx + 2)) {
                            isHit = 2;
                        }
                    }
                    else if(by <= 13) {
                        if(bx >= (batsman.lx - 1) && bx <= (batsman.lx + 1)) {
                            isHit = 2;
                        }
                    }
                    if(isHit == 2) {
                        isDropped = 1;
                        ballHeight = 3;
                        ddz = 1;
                        ddy = 1;
                        ddx = (batsman.lx - bline) / 2;
                    }
                }
            }
            if(!isHit) {
                if(bz <= -21 && bx >= -0.95 && bx <= 0.95 && by <= 4.8) {
                    s2.isOut = 1;
                }
                if(!isDropped) {
                    bx += ddx, by = max(by - ddy, 0.5), bz -= ddz;
                    if(by <= 0.6) isDropped = 1, ddy -= 0.3;
                    ddy += 0.05;
                }
                else {
                    bx += ddx, by += ddy, bz -= ddz;
                    ddy -= 0.05;
                }
            }
            batsman.lhlAngle = batsman.rhlAngle = -45;
            batsman.lhuAngle = batsman.rhuAngle = 45;
            batsman.batAngle += 2;
            batsman.rhlAngle -= 2;
            batsman.slhAngle += 10;
            batsman.srhAngle += 11;
            if(batsman.srhAngle >= 150) {
                isBat = 0;
                batsman.bodyAngle = 0;
                batsman.rhlAngle = batsman.lhlAngle = 0;
                batsman.rhuAngle = batsman.lhuAngle = 0;
                batsman.rhAngle = 0;
                batsman.lhAngle = 0;
                batsman.batAngle = 0;
                batsman.slhAngle = 0;
                batsman.srhAngle = 0;
                batsman.lllAngle = batsman.rllAngle = 0;
                batsman.lluAngle = batsman.rluAngle = 0;
                batsman.llAngle = 0;
                batsman.rlAngle = 0;
                batsman.faceAngle = 270;
                if(s2.isOut) {
                    wickets++;
                    if(wickets == 3) {
                        if(innings == 1) {
                            target = totalRuns;
                            wickets = 0;
                            innings = 2;
                            totalRuns = 0;
                        }
                        else if(innings == 2) {
                            if(totalRuns == target) dynamicBar = "DRAW!";
                            else dynamicBar = "1st Team Wins!";
                            isRestarted = 1;
                        }
                    }
                }
                if(!isHit) isEnded = 1, isBall = 0;
            }
        }
    }
    if(isBowl) {
        if(bowler.lz == 70) { /// bowler initialization
            isBat = 1;
            isBall = isHit = isDropped = isEnded = nrun = 0;
            ddz = 2;
            bx = -4.5, by = 11, bz = 23;
            bowler.isRunning = 1;
            bowler.lllAngle = bowler.rllAngle = 45;
            bowler.lluAngle = bowler.rluAngle = -45;
            bowler.llAngle = -45;
            bowler.rlAngle = 90;
            bowler.lhlAngle = bowler.rhlAngle = -45;
            bowler.lhuAngle = bowler.rhuAngle = 45;
            bowler.lhAngle = 45;
            bowler.rhAngle = -90;
            bowler.bodyAngle = 5;
            bowler.sideAngle = 0;
            ly = 30, lz = 120, ry = 80;
        }
        else if(bowler.lz < 30) { /// bowler's running movement
            bowler.sideAngle -= 1;
            bowler.bodyAngle += 1;
            bowler.rhlAngle += 3.6;
            bowler.rhuAngle -= 3.6;
            bowler.rhAngle += 9.6;
            bowler.lhlAngle = 0;
            bowler.lhuAngle = 0;
            if(bowler.lz <= 23.0) {
                bowler.isRunning = 0;
                isBall = 1;
            }
            if(((int)bowler.lz % 10) <= 4) {
                isDropped = 0;
                bowler.llAngle -= 21.6;
                bowler.rlAngle += 21.6;
                bowler.lhAngle += 21.6;
            }
            else {
                bowler.llAngle += 21.6;
                bowler.rlAngle -= 32.4;
                bowler.lhAngle += 10.8;
            }
            lz -= 0.8;
            ly -= 0.1;
            ry -= 0.25;
        }
        else if(((int)bowler.lz % 10) <= 4) { /// bowler's bowling motion
            bowler.llAngle -= 21.6;
            bowler.rlAngle += 21.6;
            bowler.lhAngle += 21.6;
            bowler.rhAngle -= 21.6;
            lz -= 0.8;
            ly -= 0.1;
            ry -= 0.25;
        }
        else {
            bowler.llAngle += 21.6;
            bowler.rlAngle -= 21.6;
            bowler.lhAngle -= 21.6;
            bowler.rhAngle += 21.6;
            lz -= 0.8;
            ly -= 0.1;
            ry -= 0.25;
        }
        bowler.lz -= 0.8;
    }

    if(bowler.lz <= 18) { /// resetting
        isBowl = 0;
        bowler.bodyAngle = bowler.lhuAngle = bowler.lhlAngle = bowler.lhAngle = bowler.rhuAngle = bowler.rhlAngle = bowler.rhAngle = 0.0;
        bowler.sideAngle = bowler.lluAngle = bowler.lllAngle = bowler.llAngle = bowler.rluAngle = bowler.rllAngle = bowler.rlAngle = 0.0;
        if(isEnded) {
            ly = 30, lz = 120;
            rx = 0, ry = 80, rz = -30;
            bowler.lz = 70;
        }
    }

    glutPostRedisplay();

}

void LoadTexture(const char*filename) {
    glGenTextures(1, &texID[texIdx]);
    glBindTexture(GL_TEXTURE_2D, texID[texIdx]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, texID[texIdx++]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void renderBitmap(float x, float y, void *font, char *str) {
    char *c;
    glRasterPos2i(x, y);
    for(c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void showHelps() {
    char buf[200] = {0};
    sprintf(buf, "----------------------------------------------------------------------------------\n");
    renderBitmap(-90, 40, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "                                                      Please Read the Instructions\n");
    renderBitmap(-75, 36, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "----------------------------------------------------------------------------------\n");
    renderBitmap(-88, 32, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "----------------------------------------------------------------------------------\n\n");
    renderBitmap(-87, 28, GLUT_BITMAP_TIMES_ROMAN_24, buf);

    sprintf(buf, "Change camera position by pressing: l (left), r (right), F (forward), B (backward) u (up) g (down/ ground)\n");
    renderBitmap(-86, 24, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "Change reference point position by pressing: L (left), R (right), U (up), D (down)\n");
    renderBitmap(-85, 20, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "press 'x' and 'z' to rotate the camera view\n");
    renderBitmap(-84, 16, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "----------------------------------------------------------------------------------\n");
    renderBitmap(-83, 12, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "press '+' to zoom in\n");
    renderBitmap(-82, 8, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "press '-' to zoom out\n");
    renderBitmap(-81, 4, GLUT_BITMAP_TIMES_ROMAN_24, buf);

    sprintf(buf, "----------------------------------------------------------------------------------\n");
    renderBitmap(-80, 0, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "press '1', '2', '3' and '4' to turn on/off the light 1, 2, 3 and 4 respectively\n");
    renderBitmap(-79, -4, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "press '5' to turn on/off the spotlight\n");
    renderBitmap(-78, -8, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "----------------------------------------------------------------------------------\n");
    renderBitmap(-77, -12, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "press 'a' to on/off the ambient light feature\n");
    renderBitmap(-76, -16, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "press 'd' to on/off the diffuse light feature\n");
    renderBitmap(-75, -20, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "press 's' to on/off the specular light feature\n");
    renderBitmap(-74, -24, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "----------------------------------------------------------------------------------\n");
    renderBitmap(-73, -28, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "press '0' to restart the match\n");
    renderBitmap(-72, -32, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "press 'm' to make the ball random\n");
    renderBitmap(-71, -36, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "press '[' and ']' to adjust the batsman position\n");
    renderBitmap(-70, -40, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "press '6'(upper-left quadrant), '7'(down-left quadrant), '8'(upper-right quadrant), '9'(down-right quadrant) to change the shot\n");
    renderBitmap(-69, -44, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "press 'o' and 'p' to adjust the ball line\n");
    renderBitmap(-68, -48, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "press 'j' and 'k' to adjust the ball length\n");
    renderBitmap(-67, -52, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "----------------------------------------------------------------------------------\n");
    renderBitmap(-66, -56, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "Developed By - Md. Muhiminul Islam (1607087)\n");
    renderBitmap(-30, -60, GLUT_BITMAP_TIMES_ROMAN_24, buf);
    sprintf(buf, "Press 'h' for help or to continue\n");
    renderBitmap(-18, -64, GLUT_BITMAP_TIMES_ROMAN_24, buf);
}

int main (int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(300,20);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Cricket Game - 1607087");

    LoadTexture("F:\\1607087_Cricket Game\\ground2.bmp");
    LoadTexture("F:\\1607087_Cricket Game\\pitch.bmp");
    LoadTexture("F:\\1607087_Cricket Game\\stadium4.bmp");
    LoadTexture("F:\\1607087_Cricket Game\\bdjersey2.bmp");
    LoadTexture("F:\\1607087_Cricket Game\\indiajersey2.bmp");
    LoadTexture("F:\\1607087_Cricket Game\\umpirejersey.bmp");
    LoadTexture("F:\\1607087_Cricket Game\\ad.bmp");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);

    glClearColor(0,0,0,1);

    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);

    glutReshapeFunc(resize);
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
