#ifndef CRICKETER_H
#define CRICKETER_H
#include <GL/gl.h>
#include "Hat.h"


class Cricketer {
    public:
        double lx, lz, faceAngle = 0.0, height;
        int type, isRunning;
        double bodyAngle, lhuAngle, lhlAngle, lhAngle, rhuAngle, rhlAngle, rhAngle;
        double sideAngle, lluAngle, lllAngle, llAngle, rluAngle, rllAngle, rlAngle;
        double slhAngle, srhAngle, batAngle;
        Hat h;
        Cricketer();
        Cricketer(double _lx, double _lz, int type, double _height);
        void draw(GLuint id);
        void drawLLL();
        void drawLLU();
        void drawRLL();
        void drawRLU();
        void drawLHL();
        void drawLHU();
        void drawRHL();
        void drawRHU();
};

#endif // CRICKETER_H
