#include "Enemy.h"
#include "World.h"

Enemy::Enemy(const std::string& imagePath, float x, float y)
    : engine::Sprite(imagePath, x, y, 40.0f, 40.0f)
{
}

void Enemy::tick(float dt, engine::World& world) {
    move(0.0f, m_speed * dt);

    if (y() + h() >= world.height()) {
        world.gameOver();
    }

}