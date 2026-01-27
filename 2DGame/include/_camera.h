#ifndef _CAMERA_H
#define _CAMERA_H

#include <_common.h>

class _camera
{
    public:
        _camera();
        virtual ~_camera();

        vec3 eye;                   //eye position
        vec3 des;                   //where you are looking at
        vec3 up;                    //camera head orientation

        float step;                 //camera speed
        vec2 rotAngle;              //rotation of camera
        float distance;             //eye to source

        enum {FORWARD, BACKWARD, LEFT, RIGHT};

        void camInit();             //initialize camera
        void camReset();            //reset camera

        void rotateXY();            //rotate XY direction
        void rotateUp();            //rotate up & down

        void camMoveFdBd(int dir);  //move camera forward & backward
        void camMoveLtRt(int dir);  //move camera left & right

        void setUpCamera();         //set camera using glulookat

    protected:

    private:
};

#endif // _CAMERA_H
