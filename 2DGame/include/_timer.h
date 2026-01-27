#ifndef _TIMER_H
#define _TIMER_H

#include <_common.h>

class _timer
{
    public:
        _timer();
        virtual ~_timer();

        clock_t startTime;              //get current time
        clock_t getTicks();             //timer counter

        void reset();                   //reset start time
        void pauseTime();               //for you to implement
        void resumeTime();

    protected:

    private:
};

#endif // _TIMER_H
