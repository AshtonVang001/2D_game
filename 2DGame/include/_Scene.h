#ifndef _SCENE_H
#define _SCENE_H

#include <GL/glew.h>
#include <_common.h>
#include <_light.h>
#include <_inputs.h>
#include <_textureLoader.h>
#include <_parallax.h>
#include <_skyBox.h>
#include <_sprite.h>
#include <_timer.h>
#include <_shader.h>
#include <GL/glut.h>
#include <math.h>

class _Scene
{
    public:
        _Scene();
        virtual ~_Scene();

        _light *myLight = new _light();
        _inputs *myInput = new _inputs();
        _textureLoader *myTexture = new _textureLoader();
        _parallax *myPrlx = new _parallax();
        _skyBox *mySkyBox = new _skyBox();
        _sprite *mySprite = new _sprite();
        _timer *myTime = new _timer();

        void reSizeScene(int width, int height);
        void initGL();
        void drawScene();
        int winMsg(HWND, UINT, WPARAM, LPARAM);

        int width, height;

        // GLUT demo variables
        int slices = 64;
        int stacks = 64;
        _textureLoader *myTex = new _textureLoader();

    private:
};

#endif // _SCENE_H
