#ifndef _PARTICLESYSTEM_H
#define _PARTICLESYSTEM_H

#include <vector>
#include <stdlib.h>
#include <_sprite.h>

struct Particle
{
    float x, y;
    float vx, vy;
    float life;
    float size;
};

class _particleSystem
{
public:
    _particleSystem();
    ~_particleSystem();

    _sprite* mySprite = new _sprite();

    void init(int maxParticles, float playerX, float playerY);
    void update(float dt, float playerX, float playerY);
    void draw();
    void drawBoss();

    std::vector<Particle> particles;
    int maxCount;
    void respawn(Particle &p, float playerX, float playerY);

    float timeAccumulator = 0.0;
    float gravity = 5.0f;

private:
};

#endif
