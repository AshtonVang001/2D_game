#ifndef _SPRITE_H
#define _SPRITE_H
#include <_common.h>
#include <_textureLoader.h>

class _sprite
{
    public:
        _sprite();
        virtual ~_sprite();

        _textureLoader *myTex = new _textureLoader;

        vec3 pos;
        vec3 rot;
        vec3 pSize;

        vec2 frames;
        vec3 vertX[4];

        float xMin, yMin, xMax, yMax;

        void spriteInit(char *, int, int);                  //filename, number of x and y frames
        void drawSprite(float, float, float);
        void spriteActions();
        float pivotOffsetY = 0.20f;

        int prevAction = -1;

        enum{WALK_L, WALK_R, WALK_F, WALK_B, IDLE_F, IDLE_B, IDLE_L, IDLE_R, DASH_F, DASH_B, DASH_L, DASH_R};

        int actionTrigger = IDLE_F;

        bool loop = true;
        bool animationFinished = false;
        int currentFrame = 0;


        void setLoop(bool shouldLoop) { loop = shouldLoop; }
        bool isFinished() const { return animationFinished; }
        void resetAnimation() { currentFrame = 0; animationFinished = false; }

    protected:

    private:
};

#endif // _SPRITE_H
