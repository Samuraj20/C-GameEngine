#include "game/Player.h"
#include "game/Bullet.h"
#include "engine/World.h"
#include "Constants.h"

Player::Player(const std::string& imagePath, float x, float y)
    : engine::Sprite(imagePath, x, y, 50.0f, 50.0f)
{
}

void Player::onEvent(const engine::InputEvent& e, engine::World& world) {
    using Type = engine::InputEvent::Type;
    using Key = engine::Key;

    if (e.type == Type::KeyDown) {
        if (e.key == Key::W) m_up = true;
        if (e.key == Key::S) m_down = true;
        if (e.key == Key::A) m_left = true;
        if (e.key == Key::D) m_right = true;

        if (e.key == Key::Space && m_shootCooldown <= 0.0f) {
            m_shootCooldown = 0.18f;

            world.spawn(std::make_unique<Bullet>(
                IMG_BULLET,
                x() + w() * 0.5f - 5.0f,
                y() - 10.0f
            ));
        }
    }
    else if (e.type == Type::KeyUp) {
        if (e.key == Key::W) m_up = false;
        if (e.key == Key::S) m_down = false;
        if (e.key == Key::A) m_left = false;
        if (e.key == Key::D) m_right = false;
    }
}

void Player::tick(float dt, engine::World& world) {
    if (m_shootCooldown > 0.0f) m_shootCooldown -= dt;

    float dx = 0.0f, dy = 0.0f;
    if (m_up)    dy -= m_speed * dt;
    if (m_down)  dy += m_speed * dt;
    if (m_left)  dx -= m_speed * dt;
    if (m_right) dx += m_speed * dt;

    move(dx, dy);

    if (x() < 0) setPos(0, y());
    if (y() < 0) setPos(x(), 0);
    if (x() + w() > world.width())  setPos(world.width() - w(), y());
    if (y() + h() > world.height()) setPos(x(), world.height() - h());
}