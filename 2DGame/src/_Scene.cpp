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

    gameCursor = LoadCursorFromFileA("cursors/GAME.cur");
    menuCursor = LoadCursorFromFileA("cursors/MENU.ani");
    attackCursor = LoadCursorFromFileA("cursors/ENEMY.cur");
    shopCursor = LoadCursorFromFileA("cursors/SHOP.ani");

    currentCursor = gameCursor;
    SetCursor(gameCursor);


    myTex->loadTexture("images/newFloor.png");
    myTex2->loadTexture("images/newWalls.png");
    level2F->loadTexture("images/map Layer 1.png");
    level2W->loadTexture("images/map Layer 2.png");
    level3F->loadTexture("images/newFloor.png");
    level3W->loadTexture("images/newWalls.png");
    shopF->loadTexture("images/shopFloor.png");
    shopW->loadTexture("images/shopWall.png");

    myShop->initShop();

    myArrowTexture->loadTexture("images/arrow.png");

    mySprite->spriteInit("images/knightAnimations3.png", 6, 12);

    myShopKeeper->spriteInit("images/shopKeeper.png", 8, 1);
    myShopKeeper->forceIdle = true;
    myShopKeeper->loop = true;
    myShopKeeper->animationFinished = false;
    myShopKeeper->currentFrame = 0;
    myShopKeeper->idleRow = 0;

    myTorch->spriteInit("images/torchDemo.png", 4, 1);


    myCollider->loadFromTexture(
        myTex2->image,
        myTex2->width,
        myTex2->height,
        myTex2->channels
    );

    myCollider2->loadFromTexture(
        shopW->image,
        shopW->width,
        shopW->height,
        shopW->channels
    );

    myCollider3->loadFromTexture(
        level2W->image,
        level2W->width,
        level2W->height,
        level2W->channels
    );

    myCollider4->loadFromTexture(
        level3W->image,
        level3W->width,
        level3W->height,
        level3W->channels
    );

    SOIL_free_image_data(myTex2->image);
    myTex2->image = nullptr;


    menu->init(width, height);
    help->init(width, height, "images/prlx.jpg");
    settings->init(width, height, "images/tex2.jpg");
    theSound->playSound("sounds/untitled.mp3");

    pausePanel.loadTexture("images/tex.jpg");

    pauseButton.setButton(
        width - 90,   // top right corner
        20,
        75,
        75,
        "images/pause2.png",
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

    ashes->init(150, mySprite->pos.x, mySprite->pos.y);

    spawners.push_back(new _spawner(5, 0.5f, 0.0f, 5.0f));   // wave 1
    spawners.push_back(new _spawner(8, 0.3f, 0.0f, -5.0f));  // wave 2

    myCam->camInit();
    currentScene = MENU_SCENE;
    lastScene = GAME_SCENE;
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
        //ShowCursor(TRUE);
        SetCursor(menuCursor);
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
        //ShowCursor(TRUE);
        SetCursor(menuCursor);
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
        //ShowCursor(TRUE);
        SetCursor(menuCursor);
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







    //===========================================================================
    // ---- SHOP SCENE ----
    //===========================================================================
    else if (currentScene == SHOP_SCENE) {
    SetCursor(gameCursor);
    static float smoothDT = 0.16f;
    smoothDT = (smoothDT * 0.9f) + (myTime->deltaTime * 0.1f);

    ashes->update(myTime->deltaTime, mySprite->pos.x, mySprite->pos.y);

    if(!paused){
    myInput->keyPressed(mySprite, smoothDT, myCollider2);
    myInput->keyPressed(myCam, smoothDT);
    }
    myCam->setUpCamera();

    if (myFade->fadeInOnEnter)
    {
        myFade->fadeIn(myTime->deltaTime);
    }

    //===========================================================================
    // ---- World Textures ----
    //===========================================================================
    // ---- Layer 1 (floor) ----
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        shopF->bindTexture();
        glColor3f(1,1,1);
        glScalef(worldScale,-worldScale,1);
        glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(0,0); glVertex3f(-8, -5.15, -8);
            glTexCoord2f(1,0); glVertex3f( 8, -5.15, -8);
            glTexCoord2f(1,1); glVertex3f( 8,  5.15, -8);
            glTexCoord2f(0,1); glVertex3f(-8,  5.15, -8);
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

        shopW->bindTexture();
        glColor3f(1,1,1);
        glScalef(worldScale,-worldScale,1);
        glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(0,0); glVertex3f(-8, -5.15, -7.99);
            glTexCoord2f(1,0); glVertex3f( 8, -5.15, -7.99);
            glTexCoord2f(1,1); glVertex3f( 8,  5.15, -7.99);
            glTexCoord2f(0,1); glVertex3f(-8,  5.15, -7.99);
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

        glPushMatrix();
            glTranslatef(1.85f, 1.5f, -1.0f);
            glScalef(0.65f, 0.65f, 1.0f);
            myTorch->drawSprite(0, 0, 0);
        glPopMatrix();

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

        glPushMatrix();
            glTranslatef(3.0f, -0.75f, 0.0f);
            glScalef(1.0f, 1.0f, 1.0f);
            myShopKeeper->drawSprite(0, 0, 0);
        glPopMatrix();


        for (auto& e : enemies)
        {
            if (e->health > 0)
            {
                e->drawSprite(e->pos.x, e->pos.y, 0);
                e->drawDamageText();
            }
        }

        ashes->draw();

        if (myInput->showHitboxes)
            drawGrid(0.5, 20);


        // ---- Animation timing ----
        int tickLimit = 100;
        static float keeperTime = 0;
        keeperTime += myTime->deltaTime * 1000;

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
            for (auto& e : enemies)
            {
                e->spriteActions();
            }
            myTime->reset();
        }

        if (keeperTime > 150)
        {
            myShopKeeper->spriteActions();
            keeperTime = 0;
        }

        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //===========================================================================
    //===========================================================================
    //===========================================================================


    //===========================================================================
    // ---- Triggers ----
    //===========================================================================
    // ---- DOOR TRIGGER ----
    float halfW = doorWidth * 0.5f;
    float halfH = doorHeight * 0.5f;

    bool inside =
        (mySprite->pos.x >= shopDoorX - halfW &&
         mySprite->pos.x <= shopDoorX + halfW &&
         mySprite->pos.y >= shopDoorY - halfH &&
         mySprite->pos.y <= shopDoorY + halfH);

    // enter event (only once per entry)
    if (inside && !playerInsideDoor)
    {
        shopDoorActivated = true;

        myFade->fadeDuration = 1.0;
        myFade->fadeTimer = 0.0;
        myFade->fadeComplete = false;
        myFade->fadeInOnEnter = false;

        returnToGame = false;
    }

    playerInsideDoor = inside;

    if (shopDoorActivated && currentScene == SHOP_SCENE)
    {
        myInput->canMove = false;


        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, width, height, 0);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glDisable(GL_DEPTH_TEST);

        myShop->drawExitPrompt(width, height);

        glEnable(GL_DEPTH_TEST);

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        glMatrixMode(GL_MODELVIEW);


        if (returnToGame) {
            myFade->fadeOut(myTime->deltaTime);

            if (myFade->fadeComplete) {
                doorActivated = false;
                doorTriggerActive = false;
                playerInsideDoor = false;
                shopDoorActivated = false;

                mySprite->pos.x = 0;
                mySprite->pos.y = -3;

                myFade->fadeTimer = 1.0;
                myFade->fadeInOnEnter = true;

                myInput->canMove = true;

                lastScene = SHOP_SCENE;
                currentScene = GAME_SCENE;

                levelModifier += 1;
            }
        }

    }

    // ---- SHOP TRIGGER ----
    float halfSize = 0.5f;

    bool shopInside =
        (mySprite->pos.x >= shopX - halfSize &&
         mySprite->pos.x <= shopX + halfSize &&
         mySprite->pos.y >= shopY - halfSize &&
         mySprite->pos.y <= shopY + halfSize);

    // enter event (fires once)
    if (shopInside && !playerInsideShop)
    {
        shopActivated = true;
        myInput->canMove = false;
    }

    playerInsideShop = shopInside;





    // ---- DRAW TRIGGERS ----
    if (myInput->showHitboxes) {
        // ---- DOOR TRIGGER DEBUG VISUAL ----
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(0.0f, 0.8f, 1.0f, 0.3f);

        glBegin(GL_QUADS);
            glVertex3f(shopDoorX - halfW, shopDoorY - halfH, -0.01f);
            glVertex3f(shopDoorX + halfW, shopDoorY - halfH, -0.01f);
            glVertex3f(shopDoorX + halfW, shopDoorY + halfH, -0.01f);
            glVertex3f(shopDoorX - halfW, shopDoorY + halfH, -0.01f);
        glEnd();

        glDisable(GL_BLEND);


        // ---- SHOP TRIGGER VISUAL ----
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(1.0f, 0.5f, 0.0f, 0.3f); // orange-ish

        glBegin(GL_QUADS);
            glVertex3f(shopX - halfSize, shopY - halfSize, -0.01f);
            glVertex3f(shopX + halfSize, shopY - halfSize, -0.01f);
            glVertex3f(shopX + halfSize, shopY + halfSize, -0.01f);
            glVertex3f(shopX - halfSize, shopY + halfSize, -0.01f);
        glEnd();

        glDisable(GL_BLEND);
    }
    //===========================================================================
    //===========================================================================
    //===========================================================================


    //===========================================================================
    // ---- Handle Shop Logic ----
    //===========================================================================
    if (shopActivated)
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, width, height, 0);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glDisable(GL_DEPTH_TEST);

        myShop->drawShopUI(width, height);

        glEnable(GL_DEPTH_TEST);

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        glMatrixMode(GL_MODELVIEW);
    }
    //===========================================================================
    //===========================================================================
    //===========================================================================



    //===========================================================================
    // ---- Torch Lighting Pipeline ----
    //===========================================================================
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


    // ---- Darken Screen ----
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_TEXTURE_2D);
    glColor4f(0.0f, 0.0f, 0.0f, 0.25f);

    glBegin(GL_QUADS);
        glVertex3f(-200, -200, 0);
        glVertex3f( 200, -200, 0);
        glVertex3f( 200,  200, 0);
        glVertex3f(-200,  200, 0);
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
    float offset = 0.1;


    cx = 1.85f;
    cy = 1.5f + offset;

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


    // ---- FURNACE LIGHT ----
    cx = 3.335;
    cy = 0.3;

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(r * 1.3f, g * 0.4f, b * 0.2f, alphaFlicker/3);
    glVertex3f(cx, cy, 0);

    for(int i = 0; i <= 360; i++)
    {
        angle = i * 3.14159f / 180.0f;
        x = cx + cos(angle) * radiusFlicker/3.5;
        y = cy + sin(angle) * radiusFlicker/3.5;

        glColor4f(r, g * 0.5f, b * 0.3f, 0.0f);
        glVertex3f(x, y, 0);
    }
    glEnd();
    //===========================================================================
    //===========================================================================
    //===========================================================================

    }
    //===========================================================================
    //===========================================================================
    //===========================================================================







    //===========================================================================
    // ---- GAME SCENE ----
    //===========================================================================
    else if (currentScene == GAME_SCENE)
    {

    // ---- DRAW GAME ----
    static float smoothDT = 0.16f;
    smoothDT = (smoothDT * 0.9f) + (myTime->deltaTime * 0.1f);
    flickerTimer += myTime->deltaTime * 5.5f;   // speed of flicker
    //SetCursor(gameCursor);
    ashes->update(myTime->deltaTime, mySprite->pos.x, mySprite->pos.y);

    if (myFade->fadeInOnEnter)
    {
        myFade->fadeIn(myTime->deltaTime);
    }


    if (flickerTimer >= 1.0f)
    {
        flickerTimer = 0.0f;
        currentColor = nextColor;
        nextColor = rand() % 2;
    }

    if(!paused)
    {
    SetCursor(gameCursor);

    if ((levelModifier-1) %3 >= 0)
        myInput->keyPressed(mySprite, smoothDT, colliders[(levelModifier-1) %3]);
    myInput->keyPressed(myCam, smoothDT);
    myCam->setUpCamera();

    for (auto& e : enemies)
    {
        e->enemyMovement(mySprite->pos, smoothDT);
        e->updateDamage(smoothDT);
        e->resolveCollision();
    }
    /*bool enemyInCursorRange = false;

    float cursorRange = 1.5f; // tweak later

    for (auto& e : enemies)
    {
        float dx = e->pos.x - mySprite->pos.x;
        float dy = e->pos.y - mySprite->pos.y;

        float distSq = dx*dx + dy*dy;

        if (distSq <= cursorRange * cursorRange)
        {
            enemyInCursorRange = true;
            break; // early exit = faster
        }
    }
    HCURSOR desiredCursor = enemyInCursorRange ? attackCursor : gameCursor;

    if (desiredCursor != currentCursor)
    {
        currentCursor = desiredCursor;
        SetCursor(currentCursor);
    }*/
    // ---- Enemy Separation ----
        float separationRadius = 0.8f;   // tweak this
        float separationForce  = 1.5f;   // tweak strength

        for (size_t i = 0; i < enemies.size(); i++)
        {
            for (size_t j = i + 1; j < enemies.size(); j++)
            {
                _enemies* a = enemies[i];
                _enemies* b = enemies[j];

                float dx = a->pos.x - b->pos.x;
                float dy = a->pos.y - b->pos.y;

                float distSq = dx*dx + dy*dy;

                if (distSq < separationRadius * separationRadius)
                {
                    float dist = sqrt(distSq);

                    if (dist > 0.0001f)
                    {
                        float overlap = separationRadius - dist;

                        dx /= dist;
                        dy /= dist;

                        // push both away from each other
                        float pushX = dx * overlap * separationForce * 0.5f;
                        float pushY = dy * overlap * separationForce * 0.5f;

                        // Try move A
                        float newAX = a->pos.x + pushX;
                        float newAY = a->pos.y + pushY;

                        if (a->canMoveTo(newAX, newAY))
                        {
                            a->pos.x = newAX;
                            a->pos.y = newAY;
                        }

                        // Try move B
                        float newBX = b->pos.x - pushX;
                        float newBY = b->pos.y - pushY;

                        if (b->canMoveTo(newBX, newBY))
                        {
                            b->pos.x = newBX;
                            b->pos.y = newBY;
                        }
                    }
                }
            }
        }
    }


    //===========================================================================
    // ---- World Textures ----
    //===========================================================================
    // ---- Layer 1 (floor) ----
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        if ((levelModifier-1) %3 >= 0)
        {
            texturesF[(levelModifier-1) %3]->bindTexture();
        }
        glColor3f(1,1,1);
        glScalef(worldScale,-worldScale,1);
        glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(0,0); glVertex3f(-8, -5.15, -8);
            glTexCoord2f(1,0); glVertex3f( 8, -5.15, -8);
            glTexCoord2f(1,1); glVertex3f( 8,  5.15, -8);
            glTexCoord2f(0,1); glVertex3f(-8,  5.15, -8);
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

        if ((levelModifier-1) %3 >= 0)
        {
            texturesW[(levelModifier-1) %3]->bindTexture();
        }
        glColor3f(1,1,1);
        glScalef(worldScale,-worldScale,1);
        glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(0,0); glVertex3f(-8, -5.15, -7.99);
            glTexCoord2f(1,0); glVertex3f( 8, -5.15, -7.99);
            glTexCoord2f(1,1); glVertex3f( 8,  5.15, -7.99);
            glTexCoord2f(0,1); glVertex3f(-8,  5.15, -7.99);
        glEnd();

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_ALPHA_TEST);
    glPopMatrix();


    // ---- Layer 3 (torch sprites) ----
    if (levelModifier%3 == 1) {
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glPushMatrix();
            glTranslatef(2.6f, 4.5f, -1.0f);
            glScalef(0.65f, 0.65f, 1.0f);
            myTorch->drawSprite(0, 0, 0);
        glPopMatrix();

        if (myWorldTime->getTicks() > 100)
        {
            myTorch->spriteActions();
            myWorldTime->reset();
        }

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // ---- Second Torch ----
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glPushMatrix();
            glTranslatef(-2.6f, 4.5f, -1.0f);
            glScalef(-0.65f, 0.65f, 1.0f);
            myTorch->drawSprite(0, 0, 0);
        glPopMatrix();

        if (myWorldTime->getTicks() > 100)
        {
            myTorch->spriteActions();
            myWorldTime->reset();
        }

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // ---- Third Torch ----
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glPushMatrix();
            glTranslatef(2.6f, -6.0f, -1.0f);
            glScalef(0.65f, 0.65f, 1.0f);
            myTorch->drawSprite(0, 0, 0);
        glPopMatrix();

        if (myWorldTime->getTicks() > 100)
        {
            myTorch->spriteActions();
            myWorldTime->reset();
        }

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // ---- Fourth Torch ----
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glPushMatrix();
            glTranslatef(-2.6f, -6.0f, -1.0f);
            glScalef(-0.65f, 0.65f, 1.0f);
            myTorch->drawSprite(0, 0, 0);
        glPopMatrix();

        if (myWorldTime->getTicks() > 100)
        {
            myTorch->spriteActions();
            myWorldTime->reset();
        }

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // ---- Fifth Torch ----
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glPushMatrix();
            glTranslatef(14.9f, -0.7f, -1.0f);
            glScalef(0.65f, 0.65f, 1.0f);
            myTorch->drawSprite(0, 0, 0);
        glPopMatrix();

        if (myWorldTime->getTicks() > 100)
        {
            myTorch->spriteActions();
            myWorldTime->reset();
        }

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // ---- Sixth Torch ----
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glPushMatrix();
            glTranslatef(-14.9f, -0.7f, -1.0f);
            glScalef(-0.65f, 0.65f, 1.0f);
            myTorch->drawSprite(0, 0, 0);
        glPopMatrix();

        if (myWorldTime->getTicks() > 100)
        {
            myTorch->spriteActions();
            myWorldTime->reset();
        }

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    }
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


        for (auto& e : enemies)
        {
            if (e->health > 0)
            {
                e->drawSprite(e->pos.x, e->pos.y, 0);
                e->drawDamageText();
            }
        }

        ashes->draw();


        // ---- Level Complete Arrow ----
        if (levelComplete)
        {
            float targetX = 0.0f;
            float targetY = 10.0f;

            float px = mySprite->pos.x;
            float py = mySprite->pos.y;

            float dx = targetX - px;
            float dy = targetY - py;

            float angle = atan2(dy, dx) * 180.0f / 3.14159f;

            float offsetY = arrowHeightOffset;

            glPushMatrix();
                glTranslatef(px, py + offsetY, -0.5f);
                glRotatef(angle, 0.0f, 0.0f, 1.0f);

                glEnable(GL_TEXTURE_2D);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                myArrowTexture->bindTexture();
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

                glScalef(0.6, 0.6, 1);

                float w = 1.5f;
                float h = 0.5f;

                glBegin(GL_QUADS);
                    glTexCoord2f(0,1); glVertex3f(-w, -h, 0);
                    glTexCoord2f(1,1); glVertex3f(-w,  h, 0);
                    glTexCoord2f(1,0); glVertex3f( w,  h, 0);
                    glTexCoord2f(0,0); glVertex3f( w, -h, 0);
                glEnd();

                glDisable(GL_TEXTURE_2D);
                glDisable(GL_BLEND);

            glPopMatrix();
        }


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

        float baseAngle = atan2(fy, fx);

        bool anyEnemyHit = false;

        for (auto& e : enemies)
        {
            float dx = e->pos.x - mySprite->pos.x;
            float dy = e->pos.y - mySprite->pos.y;

            float distSq = dx*dx + dy*dy;
            float length = sqrt(distSq);

            bool insideRadius = distSq <= (radius * radius);

            float normalizedDot = 0.0f;
            if (length > 0.0001f)
            {
                normalizedDot = (dx * fx + dy * fy) / length;
            }

            bool inFront = normalizedDot > -0.34f;

            bool hit = insideRadius && inFront;

            if (hit)
                anyEnemyHit = true;

            // APPLY DAMAGE HERE
            if (myInput->attackPressed && hit)
                e->takeDamage(10);

            if (myInput->dashAttack && distSq <= (radius * 0.4f))
                e->takeDamage(1);
        }

        currentlyInside = anyEnemyHit;
        enemyInside = anyEnemyHit;
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



        // ---- DOOR TRIGGER ----
        doorTriggerActive = levelComplete;
        if (doorTriggerActive)
        {
            float halfW = doorWidth * 0.5f;
            float halfH = doorHeight * 0.5f;

            bool inside =
                (mySprite->pos.x >= doorX - halfW &&
                 mySprite->pos.x <= doorX + halfW &&
                 mySprite->pos.y >= doorY - halfH &&
                 mySprite->pos.y <= doorY + halfH);

            // enter event (only once per entry)
            if (inside && !playerInsideDoor)
            {
                doorActivated = true;

                myFade->fadeDuration = 1.0;
                myFade->fadeTimer = 0.0;
                myFade->fadeComplete = false;
                myFade->fadeInOnEnter = false;
            }

            playerInsideDoor = inside;

        }

        else {
            playerInsideDoor = false;
        }

        if (doorActivated && currentScene == GAME_SCENE)
        {
            myInput->canMove = false;
            myFade->fadeOut(myTime->deltaTime);

            if (myFade->fadeComplete) {
                doorActivated = false;
                doorTriggerActive = false;
                playerInsideDoor = false;
                shopDoorActivated = false;

                myFade->fadeTimer = 1.0;
                myFade->fadeInOnEnter = true;

                mySprite->pos.x = 0;
                mySprite->pos.y = -3;

                myInput->canMove = true;

                lastScene = GAME_SCENE;
                currentScene = SHOP_SCENE;
            }
        }


        // ---- Draw Debug Triggers ----
        if (myInput->showHitboxes) {
            drawGrid(0.5, 20);

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


            // ---- DOOR TRIGGER DEBUG VISUAL ----
            float halfW = doorWidth * 0.5f;
            float halfH = doorHeight * 0.5f;

            glDisable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glColor4f(0.0f, 0.8f, 1.0f, 0.3f);

            glBegin(GL_QUADS);
                glVertex3f(doorX - halfW, doorY - halfH, -0.01f);
                glVertex3f(doorX + halfW, doorY - halfH, -0.01f);
                glVertex3f(doorX + halfW, doorY + halfH, -0.01f);
                glVertex3f(doorX - halfW, doorY + halfH, -0.01f);
            glEnd();

            glDisable(GL_BLEND);
        }

        if (!myInput->isDashing)
            currentlyInsideDash = false;

        glPopMatrix();
        //--------



        // ---- Enemy / Player Collision ----
        for (auto& e : enemies)
        {
            float colDx = e->pos.x - mySprite->pos.x;
            float colDy = e->pos.y - mySprite->pos.y;

            float distanceSq = colDx * colDx + colDy * colDy;
            float combinedRadius = playerRadius + e->radius;

            if (distanceSq < combinedRadius * combinedRadius)
            {
                float distance = sqrt(distanceSq);

                if (distance > 0.0001f)
                {
                    float overlap = combinedRadius - distance;

                    colDx /= distance;
                    colDy /= distance;

                    e->pos.x += colDx * overlap;
                    e->pos.y += colDy * overlap;
                }
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
            for (auto& e : enemies)
            {
                e->spriteActions();
            }
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
    //moved to loop
    // --------
    // ---- SPAWNER SYSTEM ----
    if (!levelComplete)
    {
        if (currentWave < spawners.size())
        {
            spawners[currentWave]->update(myTime->deltaTime, enemies, myCollider);

            bool allDead = true;

            for (auto& e : enemies)
            {
                if (e->health > 0)
                {
                    allDead = false;
                    break;
                }
            }

            if (spawners[currentWave]->isFinished() && allDead)
            {
                currentWave++;
            }
        }
        else
        {
            // All waves completed AND no more spawners left
            bool allDead = true;

            for (auto& e : enemies)
            {
                if (e->health > 0)
                {
                    allDead = false;
                    break;
                }
            }

            if (allDead)
            {
                levelComplete = true;
            }
        }
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
    glColor4f(0.0f, 0.0f, 0.0f, 0.25f);

    glBegin(GL_QUADS);
        glVertex3f(-200, -200, 0);
        glVertex3f( 200, -200, 0);
        glVertex3f( 200,  200, 0);
        glVertex3f(-200,  200, 0);
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


    if (levelModifier%3 == 1) {
    //---- light circle ----
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    float offset = 0.1;


    cx = 2.6f;
    cy = 4.5f + offset;

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
    cx = -2.6f;
    cy = 4.5f + offset;

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

    // ---- Third Light ----
    cx = 2.6f;
    cy = -6.0f + offset;

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

    // ---- Fourth Light ----
    cx = -2.6f;
    cy = -6.0f + offset;

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

    // ---- Fifth Light ----
    cx = 14.9f;
    cy = -0.7f + offset;

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

    // ---- Sixth Light ----
    cx = -14.9f;
    cy = -0.7f + offset;

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




    // ---- GARGOYLE LIGHTS ----
    cx = 1.18;
    cy = 10.15;

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(r, g, b, alphaFlicker/2);
    glVertex3f(cx, cy, 0);

    for(int i = 0; i <= 360; i++)
    {
        angle = i * 3.14159f / 180.0f;
        x = cx + cos(angle) * radiusFlicker/3;
        y = cy + sin(angle) * radiusFlicker/3;

        glColor4f(r, g * 0.5f, b * 0.3f, 0.0f);
        glVertex3f(x, y, 0);
    }
    glEnd();

    // ---- Second Gargoyle light ----
    cx = -1.18;
    cy = 10.15;

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(r, g, b, alphaFlicker/2);
    glVertex3f(cx, cy, 0);

    for(int i = 0; i <= 360; i++)
    {
        angle = i * 3.14159f / 180.0f;
        x = cx + cos(angle) * radiusFlicker/3;
        y = cy + sin(angle) * radiusFlicker/3;

        glColor4f(r, g * 0.5f, b * 0.3f, 0.0f);
        glVertex3f(x, y, 0);
    }
    glEnd();


    // ---- Third Gargoyle light ----
    cx = 8.3;
    cy = 3.63;

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(r, g, b, alphaFlicker/2);
    glVertex3f(cx, cy, 0);

    for(int i = 0; i <= 360; i++)
    {
        angle = i * 3.14159f / 180.0f;
        x = cx + cos(angle) * radiusFlicker/3;
        y = cy + sin(angle) * radiusFlicker/3;

        glColor4f(r, g * 0.5f, b * 0.3f, 0.0f);
        glVertex3f(x, y, 0);
    }
    glEnd();

    // ---- Fourth Gargoyle light ----
    cx = -8.3;
    cy = 3.63;

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(r, g, b, alphaFlicker/2);
    glVertex3f(cx, cy, 0);

    for(int i = 0; i <= 360; i++)
    {
        angle = i * 3.14159f / 180.0f;
        x = cx + cos(angle) * radiusFlicker/3;
        y = cy + sin(angle) * radiusFlicker/3;

        glColor4f(r, g * 0.5f, b * 0.3f, 0.0f);
        glVertex3f(x, y, 0);
    }
    glEnd();

    }


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
    if (myInput->showHitboxes) {
        char text[64];
        sprintf(text, "FPS: %.0f", fps);
        for (const char* c = text; *c; ++c)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        }

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

    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](_enemies* e) { return e->health <= 0; }),
        enemies.end()
    );

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
    // ---- END GAME SCENE ----
    //===========================================================================
    //===========================================================================
    //===========================================================================


    // ---- Fade after level ends ----
    myFade->draw(width, height);

    if (isPauseAllowed() && paused)
    {
        drawPauseUI();
    }
}

void _Scene::drawPauseUI()
{
    SetCursor(menuCursor);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ---- Dark overlay ----
    glDisable(GL_TEXTURE_2D);
    glColor4f(0,0,0,0.6f);

    glBegin(GL_QUADS);
        glVertex2f(0,0);
        glVertex2f(width,0);
        glVertex2f(width,height);
        glVertex2f(0,height);
    glEnd();

    // ---- Pause panel ----
    glEnable(GL_TEXTURE_2D);
    pausePanel.bindTexture();

    float w = 400;
    float h = 300;
    float x = width/2 - w/2;
    float y = height/2 - h/2;

    glColor4f(1,1,1,1);

    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(x,y);
        glTexCoord2f(1,0); glVertex2f(x+w,y);
        glTexCoord2f(1,1); glVertex2f(x+w,y+h);
        glTexCoord2f(0,1); glVertex2f(x,y+h);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1,1,1,1);

    // ---- Buttons ----
    resumeButton.update();
    resumeButton.draw();

    quitPauseButton.update();
    quitPauseButton.draw();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

bool _Scene::isPauseAllowed()
{
    return (currentScene == GAME_SCENE || currentScene == SHOP_SCENE);
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
            if (isPauseAllowed())
            {
                paused = !paused;
                ShowCursor(TRUE);
                return 0;
            }
            else if(currentScene == MENU_SCENE){
                PostQuitMessage(0);
            }
        }

        if (wParam == 'Y') {

            if (currentScene == SHOP_SCENE && shopDoorActivated) {
                myInput->canMove = true;
                returnToGame = true;
            }
        }

        if (wParam == 'N') {

            if (currentScene == SHOP_SCENE && shopDoorActivated) {
                myInput->canMove = true;
                returnToGame = false;
                shopDoorActivated = false;
            }
        }

        if (wParam == VK_TAB) {
            if (currentScene == SHOP_SCENE && shopActivated) {
                myInput->canMove = true;
                shopActivated = false;
            }
        }

        // ---- Only send input to game when in game scene ----
        if (currentScene == GAME_SCENE || currentScene == SHOP_SCENE)
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
            if(currentScene == GAME_SCENE || currentScene == SHOP_SCENE)
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
                currentScene = lastScene;   // switch to last scene
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


void _Scene::drawGrid(float step, float range)
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glLineWidth(1.0f);

    glBegin(GL_LINES);

    for (float x = -range; x <= range; x += step)
    {
        // X-axis (vertical lines)
        if (fabs(x) < 0.0001f)
            glColor4f(0.0f, 0.0f, 1.0f, 0.6f); // Y-axis line (blue when x=0)
        else
            glColor4f(1.0f, 1.0f, 1.0f, 0.15f);

        glVertex3f(x, -range, -0.02f);
        glVertex3f(x,  range, -0.02f);
    }

    for (float y = -range; y <= range; y += step)
    {
        // Y-axis (horizontal line)
        if (fabs(y) < 0.0001f)
            glColor4f(1.0f, 0.0f, 0.0f, 0.6f); // X-axis line (red when y=0)
        else
            glColor4f(1.0f, 1.0f, 1.0f, 0.15f);

        glVertex3f(-range, y, -0.02f);
        glVertex3f( range, y, -0.02f);
    }

    glEnd();
}
