#include "_player.h"

_player::_player()
{
    //ctor
}

_player::~_player()
{
    //dtor
}

int _player::getTickLimit(bool isDashing, bool isMoving)
{
    if (isDashing) return 40;
    if (isMoving)  return 60;
    return 100;
}

void _player::takeDamage(int dmg, float deltaTime)
{
    if(damageCoolDown > 0.0f) return; //still invincible

    health -= dmg;

    damageCoolDown = damageCoolDownDuration;
}

void _player::updateCoolDown(float deltaTime) //cool down so the enemy does not attack every second
{
    if(damageCoolDown > 0.0f){
        damageCoolDown -= deltaTime;
    }
}

void _player::drawHealthBar(float currentHealth, float maxHealth, float x, float y, float width, float height)
{
    float healthPercentage = currentHealth / maxHealth;
    float filledWidth = width * healthPercentage;

    // Draw the background bar (e.g., black)
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // Draw the foreground bar (e.g., green/red gradient)
    // The color can be made proportional to health
    glColor3f(1.0f - healthPercentage, healthPercentage, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + filledWidth, y);
    glVertex2f(x + filledWidth, y + height);
    glVertex2f(x, y + height);
    glEnd();
}


