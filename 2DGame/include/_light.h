#ifndef _LIGHT_H
#define _LIGHT_H
#include <_common.h>
#include <_timer.h>


class _light
{
    public:
        _light();
        virtual ~_light();

        _timer* myTime = new _timer();

        void drawLight(float cx, float cy);

        // Torch colors
        float torchColors[3][3] =
        {
            {1.0f, 0.8f, 0.4f},
            {1.0f, 0.9f, 0.5f}
        };

        float flickerTimer = 0.0f;
        int currentColor = 0;
        int nextColor = 1;

    protected:

    private:
};

#endif // _LIGHT_H
