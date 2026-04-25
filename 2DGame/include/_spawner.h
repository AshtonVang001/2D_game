#ifndef _SPAWNER_H
#define _SPAWNER_H

#include <vector>
#include <_enemies.h>
#include <_boss.h>

class _spawner
{
    public:
        _spawner();
        _spawner(int count, float delay, float x, float y, bool boss);
        virtual ~_spawner();

        void update(float dt, std::vector<_enemies*>& enemies, _collisionCheck* map);
        bool isFinished();

        int totalToSpawn;
        int spawned;

        float spawnDelay;
        float timer;

        float spawnX;
        float spawnY;

        int count;
        float delay;
        float x;
        float y;

        bool spawnBoss;


    protected:

    private:
};

#endif // _SPAWNER_H
