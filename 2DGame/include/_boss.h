#pragma once
#include "_enemies.h"
#include <_sprite.h>
#include <_common.h>

class _boss : public _enemies
{
public:
    _boss();
    void update(float dt, vec3 playerPos);
    void bossBehavior(float dt, vec3 playerPos);
};
