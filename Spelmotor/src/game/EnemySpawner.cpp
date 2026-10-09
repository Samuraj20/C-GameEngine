#include "game/EnemySpawner.h"
#include "game/Enemy.h"
#include "engine/World.h"
#include "Constants.h"

#include <cstdlib>
#include <ctime>

EnemySpawner::EnemySpawner(float spawnIntervalSeconds, int maxEnemiesOnScreen)
    : engine::Sprite("" /*ingen bild*/, 0, 0, 0, 0),
      m_interval(spawnIntervalSeconds),
      m_maxEnemies(maxEnemiesOnScreen)
{
}

void EnemySpawner::tick(float dt, engine::World& world) {

    if (!m_rngSeeded) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        m_rngSeeded = true;
    }

    int enemiesNow = 0;
    for (auto* s : world.allSprites()) {
        if (dynamic_cast<Enemy*>(s)) enemiesNow++;
    }

    if (enemiesNow >= m_maxEnemies) return;

    m_timer += dt;
    if (m_timer < m_interval) return;
    m_timer = 0.0f;

    const float enemyW = 40.0f;
    float x = static_cast<float>(std::rand() % (world.width() - static_cast<int>(enemyW)));
    float y = -50.0f;

    world.spawn(std::make_unique<Enemy>(IMG_ENEMY, x, y));
}