#ifndef GAME_ENEMY_SPAWNER_H
#define GAME_ENEMY_SPAWNER_H

#include "engine/Sprite.h"

class EnemySpawner : public engine::Sprite {
public:
    EnemySpawner(float spawnIntervalSeconds, int maxEnemiesOnScreen);

    void tick(float dt, engine::World& world) override;

private:
    float m_interval;
    float m_timer{0.0f};
    int   m_maxEnemies;

    bool m_rngSeeded{false};
};

#endif