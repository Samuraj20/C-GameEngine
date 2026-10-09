#ifndef ENGINE_SPRITE_H
#define ENGINE_SPRITE_H

#include <cstdint>
#include <string>
#include "Rect.h"
#include "InputEvent.h"
#include "Renderer.h"

namespace engine {

    class World;
    class Renderer;

    class Sprite {
    public:
        using Id = std::uint64_t;

        explicit Sprite(std::string imagePath, float x, float y, float w, float h)
            : m_imagePath(std::move(imagePath)), m_rect{ x, y, w, h } {
        }

        virtual ~Sprite() = default;

        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;
        Sprite(Sprite&&) = delete;
        Sprite& operator=(Sprite&&) = delete;

        virtual void onEvent(const InputEvent& e, World& world) { (void)e; (void)world; }
        virtual void tick(float dt, World& world) { (void)dt; (void)world; }

        virtual void render(Renderer& r);

        Rect bounds() const { return m_rect; }
        void setPos(float x, float y) { m_rect.x = x; m_rect.y = y; }
        void move(float dx, float dy) { m_rect.x += dx; m_rect.y += dy; }

        float x() const { return m_rect.x; }
        float y() const { return m_rect.y; }
        float w() const { return m_rect.w; }
        float h() const { return m_rect.h; }

        Id id() const { return m_id; }

    private:
        friend class World;
        friend class GameEngine;
        void setId(Id id) { m_id = id; }

        std::string m_imagePath;
        Rect m_rect;
        Id m_id{ 0 };
    };

    inline void Sprite::render(Renderer& r) {
        r.drawImage(m_imagePath, m_rect.x, m_rect.y, m_rect.w, m_rect.h);
    }

} 

#endif