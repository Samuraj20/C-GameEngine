
#ifndef ENGINE_GAME_ENGINE_H
#define ENGINE_GAME_ENGINE_H


#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace engine {

    class Sprite;
    class Renderer;
    class World;

    class GameEngine {
    public:
        GameEngine(std::string title, int width, int height);
        ~GameEngine();

        GameEngine(const GameEngine&) = delete;
        GameEngine& operator=(const GameEngine&) = delete;

        void addSprite(std::unique_ptr<Sprite> s);

        void run();
        void stop();

        bool isGameOver() const;
        void setGameOver();

        int width() const;
        int height() const;

    private:
        friend class World;

        void spawnInternal(std::unique_ptr<Sprite> s);
        void destroyInternal(std::uint64_t id);

        struct Impl;
        std::unique_ptr<Impl> m;
    };

} 

#endif