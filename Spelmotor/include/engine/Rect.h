#ifndef ENGINE_RECT_H
#define ENGINE_RECT_H

namespace engine {

    struct Rect {
        float x{ 0 }, y{ 0 }, w{ 0 }, h{ 0 };
    };

    inline bool intersects(const Rect& a, const Rect& b) {
        return !(a.x + a.w <= b.x ||
            b.x + b.w <= a.x ||
            a.y + a.h <= b.y ||
            b.y + b.h <= a.y);
    }

} 

#endif