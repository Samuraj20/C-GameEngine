#ifndef ENGINE_WORLD_H
#define ENGINE_WORLD_H

#include <memory>
#include <vector>
#include "Rect.h"

namespace engine {

    class Sprite;
    class GameEngine;

    class World {
    public:

        std::vector<Sprite*> allSprites();

        const std::vector<std::unique_ptr<Sprite>>& sprites() const;
        
        void spawn(std::unique_ptr<Sprite> s);

        void destroy(Sprite::Id id);

        std::vector<Sprite*> queryIntersections(const Sprite& me);

        void stop();
        void gameOver();

        int width() const;
        int height() const;

    private:
        friend class GameEngine;
        explicit World(GameEngine& engine) : m_engine(engine) {}

        GameEngine& m_engine;
    };

} 

#endif
