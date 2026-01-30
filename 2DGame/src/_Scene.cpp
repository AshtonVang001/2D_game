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

    myTex->loadTexture("images/map.png");
    mySprite->spriteInit("images/CharacterRotate.png", 7, 4);

    myCam->camInit();
}

void _Scene::drawScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    myTime->updateDeltaTime();


    static float smoothDT = 0.16f;
    smoothDT = (smoothDT * 0.9f) + (myTime->deltaTime * 0.1f);

    myInput->keyPressed(mySprite, smoothDT);
    myInput->keyPressed(myCam, smoothDT);
    myCam->setUpCamera();


    // --- Textured background quad ---
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        myTex->bindTexture();
        glColor3f(1,1,1);
        glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(0,0); glVertex3f(-8, -3.2, -8);
            glTexCoord2f(1,0); glVertex3f( 8, -3.2, -8);
            glTexCoord2f(1,1); glVertex3f( 8,  3.2, -8);
            glTexCoord2f(0,1); glVertex3f(-8,  3.2, -8);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        mySprite->drawSprite(mySprite->pos.x, mySprite->pos.y, -3);
        if (myTime->getTicks() > 100) {
            mySprite->spriteActions();
            myTime->reset();
        }

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

int _Scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_KEYDOWN:
        myInput->wParam = wParam;
        myInput->keys[wParam] = true;
        break;
    case WM_KEYUP:
        myInput->wParam = wParam;
        myInput->keys[wParam] = false;
        break;
    }
    return 0;
}
