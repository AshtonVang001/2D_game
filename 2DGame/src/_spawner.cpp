#include "_spawner.h"

_spawner::_spawner()
{
    //ctor
    totalToSpawn = 0;
    spawnDelay = 1.0f;
    spawnX = 0.0f;
    spawnY = 0.0f;

    spawned = 0;
    timer = 0.0f;
}
_spawner::_spawner(int count, float delay, float x, float y)
{
    totalToSpawn = count;
    spawnDelay = delay;
    spawnX = x;
    spawnY = y;

    spawned = 0;
    timer = 0.0f;
}
_spawner::~_spawner()
{
    //dtor
}

void _spawner::update(float dt, std::vector<_enemies*>& enemies, _collisionCheck* map)
{
    if (spawned >= totalToSpawn)
        return;

    timer += dt;

    if (timer >= spawnDelay)
    {
        timer = 0.0f;

        _enemies* e = new _enemies();
        e->spriteInit("images/characterRotate.png", 7, 4);

        // small random spread so they don't stack
        e->pos.x = spawnX + (rand() % 3 - 1);
        e->pos.y = spawnY + (rand() % 3 - 1);

        e->collisionMap = map;

        enemies.push_back(e);
        spawned++;
    }
}

bool _spawner::isFinished()
{
    return spawned >= totalToSpawn;
}
