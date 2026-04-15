#ifndef _FADEINOUT_H
#define _FADEINOUT_H

#include<_common.h>


class _fadeInOut
{
    public:
        _fadeInOut();
        virtual ~_fadeInOut();

        void fadeIn(float deltaTime);
        void fadeOut(float deltaTime);
        void draw(int width, int height);

        float fadeTimer = 0.0f;
        float fadeDuration = 1.0f;
        bool fadeComplete = false;
        bool fadeInOnEnter = false;

    protected:

    private:
};

#endif // _FADEINOUT_H
