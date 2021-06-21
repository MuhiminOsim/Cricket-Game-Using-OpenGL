#include "Cricketer.h"
#include "Cube.h"
#include "Sphere.h"
#include "Hat.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

Cricketer::Cricketer() {
    lx = lz = 0;
    type = 2;
    faceAngle = 0;
    height = 8;
    isRunning = 0;
    bodyAngle = lhuAngle = lhlAngle = lhAngle = rhuAngle = rhlAngle = rhAngle = slhAngle = batAngle = 0.0;
    sideAngle = lluAngle = lllAngle = llAngle = rluAngle = rllAngle = rlAngle = srhAngle = 0.0;
}

Cricketer::Cricketer(double _lx, double _lz, int _type, double _height) {
    lx = _lx;
    lz = _lz;
    type = _type;
    height = _height;
    isRunning = 0;
    if(type == 1) {
        faceAngle = 270;
    }
    else if(type == 2) {
        faceAngle = 180;
    }
    else faceAngle = 0;
    bodyAngle = lhuAngle = lhlAngle = lhAngle = rhuAngle = rhlAngle = rhAngle = slhAngle = batAngle = 0.0;
    sideAngle = lluAngle = lllAngle = llAngle = rluAngle = rllAngle = rlAngle = srhAngle = 0.0;
}

void Cricketer::drawLLL() {
    glPushMatrix(); /// left leg lower
        glRotated(lllAngle, 1, 0, 0);
        glPushMatrix();
            glTranslated(-1, 0, 0);
            glPushMatrix();
                glScaled(1.25, 4, 1.25);
                for(int i = 0; i < 3; i++) {
                    glRotated(i * 60, 0, 1, 0);
                    if(type == 4) {
                        Cube lll(0, 0, 0);
                        lll.draw();
                    }
                    else {
                        Cube lll(73, 7, 36);
                        lll.draw();
                    }
                }
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Cricketer::drawLLU() {
    glPushMatrix(); /// left leg upper
        glTranslated(0, 5.5, 0);
        glRotated(lluAngle, 1, 0, 0);
        glTranslated(0, -5.5, 0);
        glPushMatrix();
            glTranslated(-1, 1, 0);
            glPushMatrix();
                glScaled(1.25, 4.5, 1.25);
                for(int i = 0; i < 3; i++) {
                    glRotated(i * 60, 0, 1, 0);
                    if(type == 4) {
                        Cube llu(0, 0, 0);
                        llu.draw();
                    }
                    else {
                        Cube llu(73, 7, 36);
                        llu.draw();
                    }
                }
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Cricketer::drawRLL() {
    glPushMatrix(); /// right leg lower
        glRotated(rllAngle, 1, 0, 0);
        glPushMatrix();
            glTranslated(1, 0, 0);
            glPushMatrix();
                glScaled(1.25, 4, 1.25);
                for(int i = 0; i < 3; i++) {
                    glRotated(i * 60, 0, 1, 0);
                    if(type == 4) {
                        Cube rll(0, 0, 0);
                        rll.draw();
                    }
                    else {
                        Cube rll(73, 7, 36);
                        rll.draw();
                    }
                }
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Cricketer::drawRLU() {
    glPushMatrix(); /// right leg upper
        glTranslated(0, 5.5, 0);
        glRotated(rluAngle, 1, 0, 0);
        glTranslated(0, -5.5, 0);
        glPushMatrix();
            glTranslated(1, 1, 0);
            glPushMatrix();
                glScaled(1.25, 4.5, 1.25);
                for(int i = 0; i < 3; i++) {
                    glRotated(i * 60, 0, 1, 0);
                    if(type == 4) {
                        Cube rlu(0, 0, 0);
                        rlu.draw();
                    }
                    else {
                        Cube rlu(73, 7, 36);
                        rlu.draw();
                    }
                }
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Cricketer::drawLHL() {
    glPushMatrix(); /// left hand lower
        glTranslated(0, 5, 0);
        glRotated(lhlAngle, 1, 0, 0);
        glTranslated(0, -5, 0);
        glPushMatrix();
            glTranslated(-2.75, 5, 0);
            glPushMatrix();
                glScaled(0.9, 3.5, 0.9);
                for(int i = 0; i < 3; i++) {
                    glRotated(i * 60, 0, 1, 0);
                    Cube lhl(197, 140, 133);
                    lhl.draw();
                }
            glPopMatrix();
        glPopMatrix();
        if(type == 2 && isRunning) {
            glPushMatrix();
                glTranslated(-2.75, 4, 0);
                Sphere ball(255, 255, 255, 0.5);
                ball.draw();
            glPopMatrix();
        }
    glPopMatrix();
}

void Cricketer::drawLHU() {
    glPushMatrix();
        glTranslated(0, 9.5, 0);
        glRotated(lhuAngle, 1, 0, 0);
        glTranslated(0, -9.5, 0);
        glPushMatrix(); /// left hand upper
            glTranslated(-2.75, 5.5, 0);
            glPushMatrix();
                glScaled(0.9, 4, 0.9);
                for(int i = 0; i < 3; i++) {
                    glRotated(i * 60, 0, 1, 0);
                    Cube lhu(197, 140, 133);
                    lhu.draw();
                }
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Cricketer::drawRHL() {
    glPushMatrix();
        glTranslated(0, 5, 0);
        glRotated(rhlAngle, 1, 0, 0);
        glTranslated(0, -5, 0);
        glPushMatrix(); /// right hand lower
            glTranslated(2.75, 5, 0);
            glPushMatrix();
                glScaled(0.9, 3.5, 0.9);
                for(int i = 0; i < 3; i++) {
                    glRotated(i * 60, 0, 1, 0);
                    Cube rhl(197, 140, 133);
                    rhl.draw();
                }
            glPopMatrix();
        glPopMatrix();
        if(type == 1) {
            glPushMatrix();
                glTranslated(0, 8.5, 0);
                glRotated(batAngle, 0, 0, 1);
                glTranslated(0, -8.5, 0);
                glPushMatrix();
                    glTranslated(2.75, 0, 0);
                    glScaled(0.5, 4.5, 1.75);
                    Cube bat(225, 234, 221);
                    bat.draw();
                glPopMatrix();
                glPushMatrix();
                    glTranslated(2.75, 4.5, 0);
                    Cube handle(225, 234, 221);
                    handle.draw();
                glPopMatrix();
            glPopMatrix();
        }
    glPopMatrix();
}

void Cricketer::drawRHU() {
    glPushMatrix();
        glTranslated(0, 9.5, 0);
        glRotated(rhuAngle, 1, 0, 0);
        glTranslated(0, -9.5, 0);
        glPushMatrix(); /// right hand upper
            glTranslated(2.75, 5.5, 0);
            glPushMatrix();
                glScaled(0.9, 4, 0.9);
                for(int i = 0; i < 3; i++) {
                    glRotated(i * 60, 0, 1, 0);
                    Cube rhu(197, 140, 133);
                    rhu.draw();
                }
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Cricketer::draw(GLuint id) {
    glPushMatrix();
        glTranslated(lx, 0, lz);
        glScaled((height * 7.0) / (15.5 * 15.5), height / 15.5, (height * 3.0) / (15.5 * 15.5));
        glRotated(faceAngle, 0, 1, 0);
        glPushMatrix();
            glTranslated(0, 6.5, 0);
            glRotated(llAngle, 1, 0, 0);
            glTranslated(0, -6.5, 0);
            drawLLL();
            drawLLU();
        glPopMatrix();
        glPushMatrix();
            glTranslated(0, 6.5, 0);
            glRotated(rlAngle, 1, 0, 0);
            glTranslated(0, -6.5, 0);
            drawRLL();
            drawRLU();
        glPopMatrix();
        glPushMatrix();
            glTranslated(0, 5, 0);
            glRotated(bodyAngle, 1, 0, 0);
            glRotated(sideAngle, 0, 0, 1);
            glTranslated(0, -5, 0);
            glPushMatrix(); /// body
                glTranslated(0, 5, 0);
                glScaled(4, 5, 4);
                Cube body(0, 255, 0);
                body.drawTex(id);
            glPopMatrix();
            glPushMatrix(); /// hand connector
                glTranslated(0, 9.25, 0);
                glScaled(7, 1.5, 4);
                Cube con(0, 255, 0);
                con.drawTex(id);
            glPopMatrix();
            glPushMatrix(); /// neck
                glTranslated(0, 10.5, 0);
                glPushMatrix();
                    glScaled(1, 2, 1);
                    for(int i = 0; i < 3; i++) {
                        glRotated(i * 60, 0, 1, 0);
                        Cube neck(197, 140, 133);
                        neck.draw();
                    }
                glPopMatrix();
            glPopMatrix();
            glPushMatrix(); /// head
                glTranslated(0, 12.5, 0.125);
                glScaled(1.4, 1.45, 1.4);
                Sphere head(197, 140, 133, 1);
                head.draw();
            glPopMatrix();
            glPushMatrix(); /// hat
                if(type == 4) {
                    h.draw();
                }
            glPopMatrix();
            glPushMatrix();
                glPushMatrix();
                    glTranslated(0, 10, 0);
                    glRotated(lhAngle, 1, 0, 0);glRotated(slhAngle, -1, 1, 1);
                    glTranslated(0, -10, 0);
                    drawLHL();
                    drawLHU();
                glPopMatrix();
            glPopMatrix();
            glPushMatrix();

                glPushMatrix();
                    glTranslated(0, 10, 0);
                    glRotated(rhAngle, 1, 0, 0);glRotated(srhAngle, -1, 1, 1);
                    glTranslated(0, -10, 0);
                    drawRHL();
                    drawRHU();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}
