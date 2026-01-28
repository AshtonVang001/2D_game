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
    glFrustum(-aspectRatio, aspectRatio, -1.0, 1.0, 2.0, 100.0);

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
    //glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHT2);

    //---- Room Light ----
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    0.1f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.02f);

    //---- Torch Light ----
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION,  0.6f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION,    0.15f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.05f);
    //white part
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION,  1.5f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION,    0.0f);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0f);


    //---- Room Light Material ----
    const GLfloat room_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat room_diffuse[]  = { 1.0f, 0.0f, 1.0f, 1.0f };
    const GLfloat room_specular[] = { 1.0f, 0.0f, 1.0f, 1.0f };
    const GLfloat room_position[] = { 0.0f, 0.0f, 5.0f, 0.0f };

    //---- Torch Light Material ----
    const GLfloat torch_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat torch_position[] = { 0.0f, -0.4f, -2.8f, 1.0f };
    const GLfloat torchWhiteDiffuse[] = {2,2,2,2};
    const GLfloat torchWhitePosition[] = { 0.0f, -0.4f, -2.8f, 1.0f };

    //---- Room Light Parameters ----
    glLightfv(GL_LIGHT0, GL_AMBIENT,  room_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  room_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, room_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, room_position);

    //---- Torch Light Parameters ----
    glLightfv(GL_LIGHT1, GL_AMBIENT,  torch_ambient);
    //glLightfv(GL_LIGHT1, GL_DIFFUSE,  torch_diffuse);
    //glLightfv(GL_LIGHT1, GL_SPECULAR, torch_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, torch_position);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, torchWhiteDiffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, torchWhitePosition);


    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };


    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    myTex->loadTexture("images/map.png");
    mySprite->spriteInit("images/Sprite-0001.png", 1, 3);
}

void _Scene::drawScene() {
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t * 90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    float flicker =
    1.2f +
    0.25f * sin(t*0.8 * 18.0) +
    0.10f * sin(t*0.8 * 37.0) +
    0.05f * sin(t*0.8 * 71.0);

    GLfloat flickerDiffuse[] = {
        5.0f * flicker,
        3.0f * flicker,
        2.0f * flicker,
        1.0f
    };

    GLfloat flickerSpecular[] = {
        3.0f * flicker,
        2.0f * flicker,
        1.0f * flicker,
        1.0f
    };

    glLightfv(GL_LIGHT1, GL_DIFFUSE,  flickerDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, flickerSpecular);

/*
    // --- Moving cube light ---
    const float light_radius = 3.0f;
    float cube_x = light_radius * cos(t);
    float cube_y = light_radius * sin(t);
    float cube_z = -5.0f;

    glPushMatrix();
        glTranslatef(cube_x, cube_y, cube_z);
        GLfloat light_pos[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

        GLfloat cube_emission[] = {1.0f, 0.0f, 1.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION, cube_emission);

        glutSolidCube(0.5f);

        GLfloat no_emission[] = {0,0,0,1};
        glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
    glPopMatrix();
*/

    // --- Textured background quad ---
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        myTex->bindTexture();
        glColor3f(1,1,1);
        glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(0,0); glVertex3f(-7, -5, -7);
            glTexCoord2f(1,0); glVertex3f( 7, -5, -7);
            glTexCoord2f(1,1); glVertex3f( 7,  5, -7);
            glTexCoord2f(0,1); glVertex3f(-7,  5, -7);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();


/*
    //---- Other shapes ----
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        myTex->bindTexture();
        glColor3f(1,1,1);
        glTranslatef(-2.4f, 1.2f, -5);
        glutSolidTeapot(0.5f);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0, 1.2, -6);
        glRotated(60, 1, 0, 0);
        glRotated(a, 0, 0, 1);
        glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4, 1.2, -6);
        glRotated(60, 1, 0, 0);
        glRotated(a, 0, 0, 1);
        glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireSphere(1, slices/2, stacks/2);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireCone(1,1,slices/2, stacks/2);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireTorus(0.2,0.8,slices/2,stacks/2);
    glPopMatrix();
*/




    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        mySprite->drawSprite(0, -0.4, -3);
        mySprite->actionTrigger = mySprite->IDLE;
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
    switch(uMsg) {
        default:
            break;
    }
    return 0;
}
