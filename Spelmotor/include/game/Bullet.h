#ifndef GAME_BULLET_H
#define GAME_BULLET_H

#include "Sprite.h"

class Bullet : public engine::Sprite {
public:
    Bullet(const std::string& imagePath, float x, float y);

    void tick(float dt, engine::World& world) override;

private:
    float m_speed = 520.0f;
};

#endif
