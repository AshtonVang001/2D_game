#ifndef _INPUTS_H
#define _INPUTS_H

#include <_common.h>
#include <_parallax.h>
#include <_skyBox.h>
#include <_sprite.h>
#include <_camera.h>

class _inputs
{
    public:
        _inputs();
        virtual ~_inputs();

        void keyUp();                                       //key released              (blank because not in use)

        void keyPressed(_parallax *);
        void keyPressed(_skyBox *);
        void keyPressed(_sprite *);
        void keyPressed(_camera *);

        void keyUp(_sprite *);

        void mouseEventUp();                                //mouse button released     (blank because not in use)

        void mouseMove(_camera *, double, double);

        double prev_MouseX;                                 //keep track of mouse X-position
        double prev_MouseY;                                 //keep track of mouse Y-position

        bool isRotationActive;                              //performing rotation
        bool isTranslationActive;                           //performing translation

        WPARAM wParam;
        LPARAM lParam;

    protected:

    private:
};

#endif // _INPUTS_H
