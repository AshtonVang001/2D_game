#ifndef _INPUTS_H
#define _INPUTS_H

#include <_common.h>
#include <_parallax.h>
#include <_skyBox.h>
#include <_sprite.h>
#include <_camera.h>
#include <_timer.h>
#include <_collisionCheck.h>

class _inputs
{
    public:
        _inputs();
        virtual ~_inputs();

        bool keys[256] = {false};

        void keyUp();                                       //key released              (blank because not in use)

        void keyPressed(_parallax *);
        void keyPressed(_skyBox *);
        void keyPressed(_sprite *, float deltaTime, _collisionCheck *);
        void keyPressed(_camera *, float);

        void mouseEventUp();                                //mouse button released     (blank because not in use)

        void mouseMove(_camera *, double, double);

        double prev_MouseX;                                 //keep track of mouse X-position
        double prev_MouseY;                                 //keep track of mouse Y-position

        bool isRotationActive;                              //performing rotation
        bool isTranslationActive;                           //performing translation

        float moveSpeed;
        float dx;
        float dy;

        vec2 playerPos;
        float followSpeed;

        int lastDirection;
        bool isMoving = false;
        bool isDashing = false;
        float dashRemaining = 0.0f;
        float dashSpeed = 25.0f;
        vec2 dashDir;

        WPARAM wParam;
        LPARAM lParam;

    protected:

    private:
};

#endif // _INPUTS_H
