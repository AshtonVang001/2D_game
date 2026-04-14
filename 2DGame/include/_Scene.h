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
#include <_enemies.h>
#include <_timer.h>
#include <_shader.h>
#include <GL/glut.h>
#include <math.h>
#include <_collisionCheck.h>
#include <_menu.h>
#include <_page.h>
#include <_sounds.h>
#include "_particleSystem.h"
#include <_spawner.h>

#include <algorithm>

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
        _enemies *enemySprite = new _enemies();
        _timer *myTime = new _timer();
        _timer *myWorldTime = new _timer();
        _camera *myCam = new _camera();
        _collisionCheck *myCollider = new _collisionCheck();
        _menu *menu = new _menu();
        _page *help = new _page();
        _page *settings = new _page();
        _sounds *theSound = new _sounds();

        _sprite *myTorch = new _sprite();
        _textureLoader *myTex = new _textureLoader();
        _textureLoader *myTex2 = new _textureLoader();

        _particleSystem* ashes = new _particleSystem();

        SceneState currentScene;

        void reSizeScene(int width, int height);
        void initGL();
        void drawScene();
        int winMsg(HWND, UINT, WPARAM, LPARAM);

        int width, height;


        // ---- Torch Stuff ----
        float torchColors[2][3] =
        {
            {1.0f, 0.8f, 0.4f},
            {1.0f, 0.9f, 0.5f}
        };
        float flickerTime = 0.0f;
        float flickerTimer = 0.0f;
        int currentColor = 0;
        int nextColor = 1;
        float cx = 0.30f;
        float cy = 0.90f;
        float radius = 2.0f;
        float flickerSpeed = 5.0f;
        // --------

        float angle;
        float x;
        float y;

        // ---- Button Stuff ----
        float bgAlpha = 0.0f;
        float buttonAlpha = 0.0f;
        float fadeTimer = 0.0f;
        float bgFadeDuration = 2.0f;      // seconds
        float buttonFadeDelay = 1.0f;     // wait after bg starts
        float buttonFadeDuration = 1.5f;  // seconds
        bool fadeComplete = false;

        bool paused = false;

        _button pauseButton;
        _button resumeButton;
        _button quitPauseButton;

        _textureLoader pausePanel;

        // ---- Hitbox stuff ----
        bool enemyInside = false;
        bool currentlyInside = false;
        bool currentlyInsideDash = false;
        float playerRadius = 0.3f;

        HCURSOR gameCursor;
        HCURSOR menuCursor;
        HCURSOR attackCursor;

        HCURSOR currentCursor = nullptr;

        std::vector<_enemies*> enemies;
        std::vector<_spawner*> spawners;

        int currentWave = 0;

    private:
};

#endif // _SCENE_H
