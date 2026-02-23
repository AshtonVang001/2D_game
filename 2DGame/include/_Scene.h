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
#include <_collisionCheck.h>
#include <_menu.h>
#include <_page.h>
#include <_sounds.h>

enum SceneState
{
    MENU_SCENE,
    GAME_SCENE,
    HELP_SCENE,
    SETTINGS_SCENE
};
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
        _camera *myCam = new _camera();
        _collisionCheck *myCollider = new _collisionCheck();
        _menu *menu = new _menu();
        _page *help = new _page();
        _page *settings = new _page();
        _sounds *theSound = new _sounds();

        void reSizeScene(int width, int height);
        void initGL();
        void drawScene();
        int winMsg(HWND, UINT, WPARAM, LPARAM);

        int width, height;

        // GLUT demo variables
        int slices = 64;
        int stacks = 64;
        _textureLoader *myTex = new _textureLoader();
        _textureLoader *myTex2 = new _textureLoader();

        SceneState currentScene;

    private:
};

#endif // _SCENE_H
