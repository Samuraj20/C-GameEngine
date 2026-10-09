#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Sprite.h"

class Player : public engine::Sprite {
public:
    Player(const std::string& imagePath, float x, float y);

    void onEvent(const engine::InputEvent& e, engine::World& world) override;
    void tick(float dt, engine::World& world) override;

private:
    float m_speed = 400.0f;

    bool m_up{ false }, m_down{ false }, m_left{ false }, m_right{ false };

    float m_shootCooldown = 0.0f;
};

#endif