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

    phantomSpawned = 0;
    waveInitialized = false;
}
_spawner::_spawner(int count, float delay, float x, float y, bool boss, int level)
{
    totalToSpawn = count;
    spawnDelay = delay;
    spawnX = x;
    spawnY = y;
    spawnBoss = boss;

    spawned = 0;
    timer = 0.0f;
    localLevelModifier = level;
}
_spawner::~_spawner()
{
    //dtor
}

void _spawner::update(float dt, std::vector<_enemies*>& enemies, _collisionCheck* map)
{
    if (spawned >= totalToSpawn)
        return;

    phantomCount = (int)(localLevelModifier/2);

    timer += dt;

    if (timer < spawnDelay)
        return;

    timer = 0.0f;

    _enemies* e;

    // Spawn boss
    if (spawnBoss)
    {
        e = new _boss();
        e->scale = 3.0f;
        e->spriteInit("images/skeleton.png", 7, 8);
    }
    else
    {
        bool spawnPhantom = (phantomSpawned < phantomCount);

        if (spawnPhantom)
        {
            e = new _phantom();
            phantomSpawned++;
        }
        else
        {
            e = new _enemies();
            e->spriteInit("images/skeleton.png", 7, 8);
        }
    }

    e->collisionMap = map;

    // spawn position
    for (int tries = 0; tries < 10; tries++)
    {
        float x = spawnX + (rand() % 3 - 1);
        float y = spawnY + (rand() % 3 - 1);

        if (e->canMoveTo(x, y))
        {
            e->pos.x = x;
            e->pos.y = y;
            break;
        }
    }

    enemies.push_back(e);
    spawned++;
}

bool _spawner::isFinished()
{
    return spawned >= totalToSpawn;
}
