#include "_Scene.h"
#include <windows.h>
#include <math.h>

_Scene::_Scene() {
    myTime->startTime = clock();
    myWorldTime->startTime = clock();
}

_Scene::~_Scene() {}

void _Scene::reSizeScene(int width, int height) {
    const float aspectRatio = (float)width / (float)height;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


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


    myTex->loadTexture("images/map Layer 1 ALT.png");
    myTex2->loadTexture("images/map Layer 2 ALT.png");

    mySprite->spriteInit("images/knightAnimations3.png", 6, 12);
    enemySprite->spriteInit("images/characterRotate.png", 7,4);

    myTorch->spriteInit("images/torchDemo.png", 4, 1);


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
    theSound->playSound("sounds/untitled.mp3");

    pausePanel.loadTexture("images/tex.jpg");

    pauseButton.setButton(
        width - 70,   // top right corner
        20,
        50,
        50,
        "images/pause.png",
        ACTION_PAUSE
    );

    resumeButton.setButton(
        width/2 - 100,
        height/2 - 40,
        200,
        60,
        "images/tex2.jpg",
        ACTION_RESUME
    );

    quitPauseButton.setButton(
        width/2 - 100,
        height/2 + 40,
        200,
        60,
        "images/tex2.jpg",
        ACTION_QUIT
    );


    enemySprite->pos.x = 0.0f;
    enemySprite->pos.y = 5.0f;
    enemySprite->collisionMap = myCollider;

    myCam->camInit();
    currentScene = MENU_SCENE;
}

void _Scene::drawScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    // ---- HARD RESET STATE ----
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


    myTime->updateDeltaTime();
    myWorldTime->updateDeltaTime();
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

        menu->update(myTime->deltaTime);
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
    //ShowCursor(FALSE);
    static float smoothDT = 0.16f;
    smoothDT = (smoothDT * 0.9f) + (myTime->deltaTime * 0.1f);

    flickerTimer += myTime->deltaTime * 5.5f;   // speed of flicker

    if (flickerTimer >= 1.0f)
    {
        flickerTimer = 0.0f;
        currentColor = nextColor;
        nextColor = rand() % 2;
    }

    if(!paused)
{
    myInput->keyPressed(mySprite, smoothDT, myCollider);
    myInput->keyPressed(myCam, smoothDT);
    myCam->setUpCamera();

    enemySprite->enemyMovement(mySprite->pos, smoothDT);
    enemySprite->updateDamage(smoothDT);
}


    //===========================================================================
    // ---- World Textures ----
    //===========================================================================
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


    // ---- Layer 3 (torch sprites) ----
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glScalef(0.6f, 0.6f, 1);
        myTorch->drawSprite(0.45, 1.2, -1);

        if (myWorldTime->getTicks() > 100)
        {
            myTorch->spriteActions();
            myWorldTime->reset();
        }

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // ---- Layer 3 (torch sprites) ----
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glScalef(-0.6f, 0.6f, 1);
        myTorch->drawSprite(8.0, -3.5, -1);

        if (myWorldTime->getTicks() > 100)
        {
            myTorch->spriteActions();
            myWorldTime->reset();
        }

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //===========================================================================
    //===========================================================================
    //===========================================================================


    //===========================================================================
    // ---- Player ----
    //===========================================================================
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_FALSE);

        mySprite->drawSprite(mySprite->pos.x, mySprite->pos.y, 0);
        if (enemySprite->health > 0) {
            enemySprite->drawSprite(enemySprite->pos.x, enemySprite->pos.y, 0);
        }
        enemySprite->drawDamageText();


        // ---- Player Attack Trigger ----
        // ---- Trigger Logic ----
        float fx = 0.0f;
        float fy = 0.0f;

        switch (mySprite->actionTrigger)
        {
            case mySprite->IDLE_F:
            case mySprite->WALK_F:
            case mySprite->DASH_F:  fy = -1.0f; break;

            case mySprite->IDLE_B:
            case mySprite->WALK_B:
            case mySprite->DASH_B:  fy =  1.0f; break;

            case mySprite->IDLE_L:
            case mySprite->WALK_L:
            case mySprite->DASH_L:  fx = -1.0f; break;

            case mySprite->IDLE_R:
            case mySprite->WALK_R:
            case mySprite->DASH_R:  fx =  1.0f; break;
        }

        float dx = enemySprite->pos.x - mySprite->pos.x;
        float dy = enemySprite->pos.y - mySprite->pos.y;

        float distSq = dx*dx + dy*dy;
        bool insideRadius = distSq <= (radius * radius);
        float baseAngle = atan2(fy, fx);
        float length = sqrt(distSq);

        float normalizedDot = 0.0f;
        if (length > 0.0001f)
        {
            normalizedDot = (dx * fx + dy * fy) / length;
        }

        bool inFront = normalizedDot > -0.34f; //cos(angle / 2)

        currentlyInside = insideRadius && inFront;
        enemyInside = currentlyInside;
        // --------


        // ---- Dash Trigger Logic ----
        currentlyInsideDash =
            (
                (enemySprite->pos.x - mySprite->pos.x) *
                (enemySprite->pos.x - mySprite->pos.x)
              +
                (enemySprite->pos.y - mySprite->pos.y) *
                (enemySprite->pos.y - mySprite->pos.y)
            ) <= (radius * 0.4);

        enemyInside = currentlyInsideDash;
        //--------


        // ---- Draw Debug Triggers ----
        if (myInput->showHitboxes) {
            // ---- Draw Attack Trigger
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glDepthMask(GL_FALSE);

            radius = 1.2f;
            float arcHalfAngle = 110.0f * 3.14159f / 180.0f;
            glColor4f(1.0f, 1.0f, 1.0f, 0.35f);

            glBegin(GL_TRIANGLE_FAN);
            glVertex3f(mySprite->pos.x, mySprite->pos.y, -0.01f);

            for (int i = -35; i <= 35; i++)  // controls smoothness
            {
                float t = (float)i / 35.0f;  // -1 to 1
                float angle = baseAngle + t * arcHalfAngle;

                float x = mySprite->pos.x + cos(angle) * radius;
                float y = mySprite->pos.y + sin(angle) * radius;

                glVertex3f(x, y, -0.01f);
            }

            glEnd();
            glDepthMask(GL_TRUE);
            // --------


            // ---- Draw Dash Trigger ----
            glPushMatrix();
            glColor4f(0.0, 1.0, 0.0, 0.35);
            if (myInput->isDashing) {
                glBegin(GL_TRIANGLE_FAN);
                glVertex3f(mySprite->pos.x, mySprite->pos.y, -0.01f);

                for(int i = 0; i <= 360; i++)
                {
                    float angle = i * 3.14159f / 180.0f;

                    glVertex3f(
                        mySprite->pos.x + cos(angle) * 0.4f,
                        mySprite->pos.y + sin(angle) * 0.4f,
                        -0.01f
                    );
                }
                glEnd();
                //--------
            }
        }

        if (!myInput->isDashing)
            currentlyInsideDash = false;

        glPopMatrix();
        //--------


        // ---- Enemy / Player Collision ----
        float colDx = enemySprite->pos.x - mySprite->pos.x;
        float colDy = enemySprite->pos.y - mySprite->pos.y;
        float distanceSq = colDx * colDx + colDy * colDy;
        float enemyRadius  = enemySprite->radius;
        float combinedRadius = playerRadius + enemyRadius;

        if (distanceSq < combinedRadius * combinedRadius)
        {
            float distance = sqrt(distanceSq);

            if (distance > 0.0001f)
            {
                float overlap = combinedRadius - distance;

                // normalize
                colDx /= distance;
                colDy /= distance;

                // push enemy away
                enemySprite->pos.x += colDx * overlap;
                enemySprite->pos.y += colDy * overlap;
            }
        }


        // ---- Animation timing ----
        int tickLimit = 100;

        if (myInput->isDashing)
        {
            tickLimit = 40;
        }
        else if (myInput->isMoving)
        {
            tickLimit = 60;
        }

        if (myTime->getTicks() > tickLimit)
        {
            mySprite->spriteActions();
            enemySprite->spriteActions();
            myTime->reset();
        }

        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //===========================================================================
    //===========================================================================
    //===========================================================================


    // ---- ROUGH ATTACK SYSTEM ----
    if (myInput->attackPressed && currentlyInside) {
        enemySprite->takeDamage(10);
    }
    if (myInput->dashAttack && currentlyInsideDash) {
        enemySprite->takeDamage(30);
    }
    // --------




    //===========================================================================
    // ---- Torch Lighting Pipeline ----
    //===========================================================================
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


    // ---- Darken Screen ----
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_TEXTURE_2D);
    glColor4f(0.0f, 0.0f, 0.0f, 0.20f);

    glBegin(GL_QUADS);
        glVertex3f(-20, -20, 0);
        glVertex3f( 20, -20, 0);
        glVertex3f( 20,  20, 0);
        glVertex3f(-20,  20, 0);
    glEnd();


    // ---- Torch Parameters ----
    float r = torchColors[currentColor][0] * (1.0f - flickerTimer) + torchColors[nextColor][0] * flickerTimer;
    float g = torchColors[currentColor][1] * (1.0f - flickerTimer) + torchColors[nextColor][1] * flickerTimer;
    float b = torchColors[currentColor][2] * (1.0f - flickerTimer) + torchColors[nextColor][2] * flickerTimer;

    flickerTime += myTime->deltaTime * flickerSpeed;

    float flicker =
        sin(flickerTime * 2.0f) * 0.10f +
        sin(flickerTime * 5.0f) * 0.05f;

    float radiusFlicker = 1.3f + flicker;
    float alphaFlicker  = 0.5f + flicker * 0.4f;


    //---- light circle ----
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    radius = 2.0f;
    cx = 0.30f;
    cy = 0.9f;

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(r, g, b, alphaFlicker);
    glVertex3f(cx, cy, 0);

    for(int i = 0; i <= 360; i++)
    {
        angle = i * 3.14159f / 180.0f;
        x = cx + cos(angle) * radiusFlicker;
        y = cy + sin(angle) * radiusFlicker;

        glColor4f(r, g * 0.5f, b * 0.3f, 0.0f);
        glVertex3f(x, y, 0);
    }
    glEnd();


    // ---- Second Light ----
    cx = -4.85f;
    cy = -2.0f;

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(r, g, b, alphaFlicker);
    glVertex3f(cx, cy, 0);

    for(int i = 0; i <= 360; i++)
    {
        angle = i * 3.14159f / 180.0f;
        x = cx + cos(angle) * radiusFlicker;
        y = cy + sin(angle) * radiusFlicker;

        glColor4f(r, g * 0.5f, b * 0.3f, 0.0f);
        glVertex3f(x, y, 0);
    }
    glEnd();


    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    //===========================================================================
    //===========================================================================
    //===========================================================================





    //===========================================================================
    // ---- Text ----
    //===========================================================================
    float fps = 0.0f;

    if (myTime->deltaTime > 0.0f)
    {
        fps = 1.0f / myTime->deltaTime;
    }

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
    char text[64];
    sprintf(text, "FPS: %.0f", fps);
    for (const char* c = text; *c; ++c)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }

    if (myInput->showHitboxes) {
        char boolText[64];
        sprintf(boolText, "Can Attack: %s", currentlyInside ? "true" : "false");
        glRasterPos2i(20, height - 70);  // lower Y value = lower on screen
        for (const char* c = boolText; *c; ++c)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        }

        char boolText2[64];
        sprintf(boolText2, "Dash Attack: %s", currentlyInsideDash ? "true" : "false");
        glRasterPos2i(20, height - 100);  // lower Y value = lower on screen
        for (const char* c = boolText2; *c; ++c)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        }
    }

    // ---- UI Projection (top-left origin like Windows mouse) ----
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);

    // ---- Pause Button ----
    pauseButton.update();
    pauseButton.draw();

    if(paused)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // gray overlay
        glDisable(GL_TEXTURE_2D);
        glColor4f(0,0,0,0.6f);

        glBegin(GL_QUADS);
            glVertex2f(0,0);
            glVertex2f(width,0);
            glVertex2f(width,height);
            glVertex2f(0,height);
        glEnd();

        // pause panel
        glEnable(GL_TEXTURE_2D);
        pausePanel.bindTexture();

        float w = 400;
        float h = 300;

        float cx = width/2 - w/2;
        float cy = height/2 - h/2;

        glColor4f(1,1,1,1);

        glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex2f(cx,cy);
            glTexCoord2f(1,0); glVertex2f(cx+w,cy);
            glTexCoord2f(1,1); glVertex2f(cx+w,cy+h);
            glTexCoord2f(0,1); glVertex2f(cx,cy+h);
        glEnd();

        resumeButton.update();
        resumeButton.draw();

        quitPauseButton.update();
        quitPauseButton.draw();
    }

    // ---- Restore matrices ----
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();


    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();

    //===========================================================================
    //===========================================================================
    //===========================================================================
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
                PostQuitMessage(0);
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
            if(currentScene == GAME_SCENE)
            {
                int mouseX = LOWORD(lParam);
                int mouseY = HIWORD(lParam);

                if(!paused)
                {
                    if(pauseButton.checkClick(mouseX, mouseY))
                    {
                        paused = true;
                        ShowCursor(TRUE);
                    }
                }
                else
                {
                    if(resumeButton.checkClick(mouseX, mouseY))
                    {
                        paused = false;
                        ShowCursor(FALSE);
                    }

                    if(quitPauseButton.checkClick(mouseX, mouseY))
                    {
                        paused = false;
                        currentScene = MENU_SCENE;
                        ShowCursor(TRUE);
                    }
                }
            }
        if (currentScene == MENU_SCENE)
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
        }
        break;
    case WM_MOUSEMOVE:
        {
            if(currentScene == GAME_SCENE)
            {
                int mouseX = LOWORD(lParam);
                int mouseY = HIWORD(lParam);

                pauseButton.checkHover(mouseX, mouseY);

                if(paused)
                {
                    resumeButton.checkHover(mouseX, mouseY);
                    quitPauseButton.checkHover(mouseX, mouseY);
                }
            }
        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);

        menu->mouseMove(mouseX, mouseY);
        }
        break;
    }
    return 0;
}
