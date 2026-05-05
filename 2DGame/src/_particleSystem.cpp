#include "_particleSystem.h"
#include <GL/glut.h>
#include <math.h>

_particleSystem::_particleSystem() {}

_particleSystem::~_particleSystem() {}

void _particleSystem::init(int maxParticles, float playerX, float playerY)
{
    maxCount = maxParticles;
    particles.clear();

    for(int i = 0; i < maxCount; i++)
    {
        Particle p;

        p.x = ((rand() % 200) / 100.0f - 1.0f) * 20.0f;
        p.y = ((rand() % 200) / 100.0f - 1.0f) * 20.0f;

        p.vx = 0.3f + (rand() % 100) / 300.0f;
        p.vy = -0.6f - (rand() % 100) / 300.0f;

        float speedScale = 0.5f + (rand() % 100) / 100.0f;
        p.vx *= speedScale;
        p.vy *= speedScale;

        p.life = (rand() % 100) / 100.0f;
        p.size = 0.02f + (rand() % 100) / 5000.0f;

        particles.push_back(p);
    }
}

void _particleSystem::respawn(Particle &p, float playerX, float playerY)
{
    p.x = playerX + ((rand() % 200) / 100.0f - 1.0f) * 20.0f;
    p.y = playerY + 6.0f + (rand() % 100) / 40.0f;

    p.vx = 0.3f + (rand() % 100) / 300.0f;
    p.vy = -0.6f - (rand() % 100) / 300.0f;

    p.life = (rand() % 100) / 100.0f;
    p.size = 0.02f + (rand() % 100) / 5000.0f;

    float speedScale = 0.5f + (rand() % 100) / 100.0f;
    p.vx *= speedScale;
    p.vy *= speedScale;
}

void _particleSystem::update(float dt, float playerX, float playerY)
{
        timeAccumulator += dt;

    for(auto &p : particles)
    {
        gravity = 2.0f;
        p.x += p.vx * dt * gravity;
        p.y += p.vy * dt * gravity;

        p.life -= dt * 0.2f;
        if(p.life < 0.0f)
            p.life = 1.0f; // just loop fade

        float wind = 0.3f + sin(timeAccumulator * 1.5f) * 0.1f;
        p.x += wind * dt;

        if(p.y < playerY - 6.0f)
            respawn(p, playerX, playerY);
    }
}

void _particleSystem::draw()
{
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    glBegin(GL_QUADS);

    for(auto &p : particles)
    {
        float alpha = p.life;

        glColor4f(0.85f, 0.85f, 0.85f, alpha * 0.3f);

        float s = p.size;

        glVertex3f(p.x - s, p.y - s, -0.5f);
        glVertex3f(p.x + s, p.y - s, -0.5f);
        glVertex3f(p.x + s, p.y + s, -0.5f);
        glVertex3f(p.x - s, p.y + s, -0.5f);
    }

    glEnd();

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void _particleSystem::drawBoss()
{
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    glBegin(GL_QUADS);

    for(auto &p : particles)
    {
        float alpha = p.life;

        glColor4f(1.0f, 0.482f, 0.0f, alpha * 0.3f);

        float s = p.size;

        glVertex3f(p.x - s, p.y - s, -0.5f);
        glVertex3f(p.x + s, p.y - s, -0.5f);
        glVertex3f(p.x + s, p.y + s, -0.5f);
        glVertex3f(p.x - s, p.y + s, -0.5f);
    }

    glEnd();

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}
