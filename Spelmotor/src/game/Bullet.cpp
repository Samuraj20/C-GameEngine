#include "Bullet.h"
#include "Enemy.h"
#include "World.h"

Bullet::Bullet(const std::string& imagePath, float x, float y)
    : engine::Sprite(imagePath, x, y, 10.0f, 20.0f)
{}

void Bullet::tick(float dt, engine::World& world) {
    move(0.0f, -m_speed * dt);

    if (y() + h() < 0.0f) {
        world.destroy(id());
        return;
    }

    // kollision med andra sprites
    auto hits = world.queryIntersections(*this);
    for (auto* s : hits) {
        if (dynamic_cast<Enemy*>(s)) {
            world.destroy(s->id());  
            world.destroy(id());    
            return;
        }
    }
}