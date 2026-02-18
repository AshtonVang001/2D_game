#include "_Scene.h"
#include <windows.h>
#include <math.h>

_Scene::_Scene() {
    myTime->startTime = clock();
}

_Scene::~_Scene() {}

void _Scene::reSizeScene(int width, int height) {
    const float aspectRatio = (float)width / (float)height;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-aspectRatio, aspectRatio, -1.0, 1.0, 2.0, 100.0);


    // ---- Orthographic projection ----

    float size = 5.0f; // zoom level

    if (aspectRatio >= 1.0f)
    {
        glOrtho(
            -size * aspectRatio, size * aspectRatio,
            -size, size,
            -100.0f, 100.0f
        );
    }
    else
    {
        glOrtho(
            -size, size,
            -size / aspectRatio, size / aspectRatio,
            -100.0f, 100.0f
        );
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    this->width = width;
    this->height = height;
}

void _Scene::initGL() {
    glShadeModel(GL_SMOOTH);
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //---- Room Light ----
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    0.1f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.02f);

    //---- Room Light Material ----
    const GLfloat room_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat room_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat room_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat room_position[] = { 0.0f, 0.0f, 5.0f, 0.0f };

    //---- Room Light Parameters ----
    glLightfv(GL_LIGHT0, GL_AMBIENT,  room_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  room_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, room_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, room_position);


    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };


    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    myTex->loadTexture("images/map Layer 1.png");
    myTex2->loadTexture("images/map Layer 2.png");
    mySprite->spriteInit("images/knightAnimations2.png", 6, 8);

    myCollider->loadFromTexture(
        myTex2->image,
        myTex2->width,
        myTex2->height,
        myTex2->channels
    );

    SOIL_free_image_data(myTex2->image);
    myTex2->image = nullptr;

    menu->init(width, height);
    help->init(width, height, "images/prlx.jpg");
    settings->init(width, height, "images/tex2.jpg");

    myCam->camInit();
}

void _Scene::drawScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    myTime->updateDeltaTime();
    //ShowCursor(FALSE);

    if (currentScene == MENU_SCENE)
    {
        // ---- DRAW MENU ----
        ShowCursor(TRUE);
        glDisable(GL_DEPTH_TEST);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, width, height, 0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        menu->update();
        menu->draw();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);
    }
    else if (currentScene == HELP_SCENE){
        ShowCursor(TRUE);
        glDisable(GL_DEPTH_TEST);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, width, height, 0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        help->draw();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);

        glEnable(GL_DEPTH_TEST);
    }
    else if (currentScene == SETTINGS_SCENE){
        ShowCursor(TRUE);
        glDisable(GL_DEPTH_TEST);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, width, height, 0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        settings->draw();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);

        glEnable(GL_DEPTH_TEST);
    }


    else if (currentScene == GAME_SCENE)
    {
    // ---- DRAW GAME ----
    ShowCursor(FALSE);
    static float smoothDT = 0.16f;
    smoothDT = (smoothDT * 0.9f) + (myTime->deltaTime * 0.1f);

    myInput->keyPressed(mySprite, smoothDT, myCollider);
    myInput->keyPressed(myCam, smoothDT);
    myCam->setUpCamera();


    // ---- World Textures ----
    // ---- Layer 1 (floor) ----
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        myTex->bindTexture();
        glColor3f(1,1,1);
        glScalef(3,-3,1);
        glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(0,0); glVertex3f(-8, -3.2, -8);
            glTexCoord2f(1,0); glVertex3f( 8, -3.2, -8);
            glTexCoord2f(1,1); glVertex3f( 8,  3.2, -8);
            glTexCoord2f(0,1); glVertex3f(-8,  3.2, -8);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // ---- Layer 2 (walls) ----
    glPushMatrix();
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.5f);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);

        myTex2->bindTexture();
        glColor3f(1,1,1);
        glScalef(1,-1,1);
        glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(0,0); glVertex3f(-8, -3.2, -7.99);
            glTexCoord2f(1,0); glVertex3f( 8, -3.2, -7.99);
            glTexCoord2f(1,1); glVertex3f( 8,  3.2, -7.99);
            glTexCoord2f(0,1); glVertex3f(-8,  3.2, -7.99);
        glEnd();

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_ALPHA_TEST);
    glPopMatrix();


    // ---- Player ----
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        mySprite->drawSprite(mySprite->pos.x, mySprite->pos.y, -3);
        if (myInput->isMoving && myTime->getTicks() > 60) {
            mySprite->spriteActions();
            myTime->reset();
        }
        else if (myTime->getTicks() > 100) {
            mySprite->spriteActions();
            myTime->reset();
        }

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    }

    // ---- Draw Game Text ----
    if (currentScene == GAME_SCENE) {
        glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        gluOrtho2D(0, width, 0, height);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);

        // ---- Color & Position ----
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2i(20, height - 40);

        // ---- Draw Text ----
        const char* text = "TEST";
        for (const char* c = text; *c; ++c)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        }

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPopAttrib();
    }
}

int _Scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_KEYDOWN:
        {
            // ---- GLOBAL ESC HANDLER ----
        if (wParam == VK_ESCAPE)
        {
            if (currentScene != MENU_SCENE)
            {
                ShowCursor(TRUE);   // make sure cursor returns
                currentScene = MENU_SCENE;
                return 0;           // stop further processing
            }
            else if(currentScene == MENU_SCENE){
                //PostQuitMessage(0);
            }
        }

        // ---- Only send input to game when in game scene ----
        if (currentScene == GAME_SCENE)
        {
            myInput->wParam = wParam;
            myInput->keys[wParam] = true;
        }
        }
        break;
    case WM_KEYUP:
        myInput->wParam = wParam;
        myInput->keys[wParam] = false;
        break;
    case WM_LBUTTONDOWN:
        {
        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);

        ButtonAction action = menu->mouseClick(mouseX, mouseY);

        if (action == ACTION_PLAY)
        {
            currentScene = GAME_SCENE;   // switch to parallax scene
        }
        else if (action == ACTION_HELP)
        {
            currentScene = HELP_SCENE;   // switch to help scene
        }
        else if (action == ACTION_SETTINGS)
        {
            currentScene = SETTINGS_SCENE;  //switch to settings
        }
        else if (action == ACTION_QUIT)
        {
            PostQuitMessage(0);
        }
        }
        break;
    case WM_MOUSEMOVE:
        {
        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);

        menu->mouseMove(mouseX, mouseY);
        }
        break;
    }
    return 0;
}
