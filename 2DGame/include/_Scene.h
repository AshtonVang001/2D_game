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
#include <_fadeInOut.h>
#include <_shop.h>

#include <algorithm>

enum SceneState
{
    MENU_SCENE,
    GAME_SCENE,
    HELP_SCENE,
    SETTINGS_SCENE,
    SHOP_SCENE
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
        _enemies *enemySprite = new _enemies();
        _timer *myTime = new _timer();
        _timer *myWorldTime = new _timer();
        _camera *myCam = new _camera();
        _menu *menu = new _menu();
        _page *help = new _page();
        _page *settings = new _page();
        _sounds *theSound = new _sounds();

        _sprite *mySprite = new _sprite();
        _sprite *myTorch = new _sprite();
        _sprite *myShopKeeper = new _sprite();

        _textureLoader *myTex = new _textureLoader();
        _textureLoader *myTex2 = new _textureLoader();
        _textureLoader *level2F = new _textureLoader();
        _textureLoader *level2W = new _textureLoader();
        _textureLoader *level3F = new _textureLoader();
        _textureLoader *level3W = new _textureLoader();
        _textureLoader *shopF = new _textureLoader();
        _textureLoader *shopW = new _textureLoader();

        _textureLoader *shopUI = new _textureLoader();
        _textureLoader *myArrowTexture = new _textureLoader();

        _collisionCheck *myCollider = new _collisionCheck();
        _collisionCheck *myCollider2 = new _collisionCheck();
        _collisionCheck *myCollider3 = new _collisionCheck();
        _collisionCheck *myCollider4 = new _collisionCheck();


        _textureLoader* texturesF[3] = {
            myTex,
            level2F,
            level3F
        };
        _textureLoader* texturesW[3] = {
            myTex2,
            level2W,
            level3W
        };

        _collisionCheck* colliders[3] = {
            myCollider,
            myCollider3,
            myCollider4
        };

        _particleSystem* ashes = new _particleSystem();
        _fadeInOut* myFade = new _fadeInOut();
        _shop* myShop = new _shop();

        SceneState currentScene;
        SceneState lastScene;

        void reSizeScene(int width, int height);
        void initGL();
        void drawScene();
        int winMsg(HWND, UINT, WPARAM, LPARAM);
        void drawGrid(float step, float range);
        void triggerLevelText();
        void resetLevel();

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
        HCURSOR shopCursor;

        HCURSOR currentCursor = nullptr;

        std::vector<_enemies*> enemies;
        std::vector<_spawner*> spawners;

        int currentWave = 0;
        bool levelComplete = false;

        float doorX = 0.0f;
        float doorY = 9.25f;
        float shopDoorX = 0.0f;
        float shopDoorY = 2.6f;
        float shopX = 2.25f;
        float shopY = -0.75f;

        float doorWidth = 1.0f;
        float doorHeight = 2.0f;

        bool doorTriggerActive = false;
        bool playerInsideDoor = false;
        bool doorActivated = false;
        bool shopDoorActivated = false;

        bool shopActivated = false;
        bool playerInsideShop = false;
        bool returnToGame = false;

        float arrowX = 0.0f;
        float arrowY = 0.0f;
        float arrowHeightOffset = 0.0f;

        //bool canMove = true;

        void drawPauseUI();
        bool isPauseAllowed();

        bool showLevelText = false;
        float levelTextTimer = 0.0f;
        float levelTextDuration = 2.0f;

    private:
};

#endif // _SCENE_H
