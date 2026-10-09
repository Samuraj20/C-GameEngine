#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include "Sprite.h"

class Enemy : public engine::Sprite {
public:
    Enemy(const std::string& imagePath, float x, float y);

    void tick(float dt, engine::World& world) override;

private:
    float m_speed = 80.0f;
};

#endif
