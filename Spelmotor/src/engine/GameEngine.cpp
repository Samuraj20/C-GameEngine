#include "GameEngine.h"
#include "Sprite.h"
#include "World.h"
#include "Renderer.h"
#include "InputEvent.h"
#include "Rect.h"
#include "Constants.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <unordered_set>
#include <cstring>

namespace engine {

    static Key mapScancode(SDL_Scancode sc) {
        switch (sc) {
        case SDL_SCANCODE_W:      return Key::W;
        case SDL_SCANCODE_A:      return Key::A;
        case SDL_SCANCODE_S:      return Key::S;
        case SDL_SCANCODE_D:      return Key::D;

        case SDL_SCANCODE_UP:     return Key::Up;
        case SDL_SCANCODE_DOWN:   return Key::Down;
        case SDL_SCANCODE_LEFT:   return Key::Left;
        case SDL_SCANCODE_RIGHT:  return Key::Right;

        case SDL_SCANCODE_SPACE:  return Key::Space;
        case SDL_SCANCODE_ESCAPE: return Key::Escape;
        default:                  return Key::Unknown;
        }
    }

    static bool translateEvent(const SDL_Event& e, InputEvent& out) {
        switch (e.type) {
        case SDL_EVENT_QUIT:
            out.type = InputEvent::Type::Quit;
            return true;

        case SDL_EVENT_KEY_DOWN:
            out.type = InputEvent::Type::KeyDown;
            out.key = mapScancode(e.key.scancode);
            return true;

        case SDL_EVENT_KEY_UP:
            out.type = InputEvent::Type::KeyUp;
            out.key = mapScancode(e.key.scancode);
            return true;

        case SDL_EVENT_MOUSE_MOTION:
            out.type = InputEvent::Type::MouseMove;
            out.mouseX = static_cast<int>(e.motion.x);
            out.mouseY = static_cast<int>(e.motion.y);
            return true;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            out.type = InputEvent::Type::MouseDown;
            out.mouseX = static_cast<int>(e.button.x);
            out.mouseY = static_cast<int>(e.button.y);
            out.mouseButton =
                (e.button.button == SDL_BUTTON_LEFT) ? MouseButton::Left :
                (e.button.button == SDL_BUTTON_RIGHT) ? MouseButton::Right :
                (e.button.button == SDL_BUTTON_MIDDLE) ? MouseButton::Middle :
                MouseButton::Unknown;
            return true;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            out.type = InputEvent::Type::MouseUp;
            out.mouseX = static_cast<int>(e.button.x);
            out.mouseY = static_cast<int>(e.button.y);
            out.mouseButton =
                (e.button.button == SDL_BUTTON_LEFT) ? MouseButton::Left :
                (e.button.button == SDL_BUTTON_RIGHT) ? MouseButton::Right :
                (e.button.button == SDL_BUTTON_MIDDLE) ? MouseButton::Middle :
                MouseButton::Unknown;
            return true;

        default:
            return false; 
        }
    }

    struct GameEngine::Impl {
        SDL_Window* window{ nullptr };
        SDL_Renderer* sdlRenderer{ nullptr };

        Renderer renderer;

        std::vector<std::unique_ptr<Sprite>> sprites;
        std::vector<std::unique_ptr<Sprite>> toSpawn;
        std::unordered_set<Sprite::Id>       toDestroy;

        bool running{ true };
        int  w{ 0 }, h{ 0 };
        std::uint64_t nextId{ 1 };

        World world;

        Impl(GameEngine& engine, int width, int height)
            : w(width), h(height), world(engine) {
        }

        bool gameOver{ false };
        TTF_Font* font{ nullptr };
    };

    void World::spawn(std::unique_ptr<Sprite> s) { m_engine.spawnInternal(std::move(s)); }
    void World::destroy(Sprite::Id id) { m_engine.destroyInternal(id); }
    int  World::width() const { return m_engine.width(); }
    int  World::height() const { return m_engine.height(); }

    std::vector<Sprite*> World::queryIntersections(const Sprite& me) {
        std::vector<Sprite*> hits;
        const Rect a = me.bounds();

        for (auto& up : m_engine.m->sprites) {
            Sprite* other = up.get();
            if (!other) continue;
            if (other->id() == me.id()) continue;

            if (intersects(a, other->bounds())) {
                hits.push_back(other);
            }
        }
        return hits;
    }

    std::vector<Sprite*> World::allSprites() {
        std::vector<Sprite*> out;
        out.reserve(m_engine.m->sprites.size());
        for (auto& up : m_engine.m->sprites) {
            if (up) out.push_back(up.get());
        }
        return out;
    } 
    
    void GameEngine::stop() {
        m->running = false;
    }

    void World::stop() {
        m_engine.stop();
    }

    bool GameEngine::isGameOver() const {
        return m->gameOver;
    }

    void GameEngine::setGameOver() {
        m->gameOver = true;
    }

    void World::gameOver() {
        m_engine.setGameOver();
    }

    GameEngine::GameEngine(std::string title, int width, int height)
        : m(std::make_unique<Impl>(*this, width, height)) {

        if (!SDL_Init(SDL_INIT_VIDEO)) {

        }

        m->window = SDL_CreateWindow(title.c_str(), width, height, 0);
        if (!m->window) {
            throw std::runtime_error(std::string("SDL_CreateWindow failed: ") + SDL_GetError());
        }

        m->sdlRenderer = SDL_CreateRenderer(m->window, nullptr);
        if (!m->sdlRenderer) {
            throw std::runtime_error(std::string("SDL_CreateRenderer failed: ") + SDL_GetError());
        }

        m->renderer.setNativeRenderer(static_cast<void*>(m->sdlRenderer));

        if (!TTF_Init()) {
            throw std::runtime_error(std::string("TTF_Init failed: ") + SDL_GetError());
        }

        m->font = TTF_OpenFont(FONT_UI.c_str(), 64);
        if (!m->font) {
            throw std::runtime_error(std::string("TTF_OpenFont failed: ") + SDL_GetError());
        }
    }

    GameEngine::~GameEngine() {
        if (m) {
            if (m->sdlRenderer) SDL_DestroyRenderer(m->sdlRenderer);
            if (m->window) SDL_DestroyWindow(m->window);
            SDL_Quit();
        }

        if (m->font) TTF_CloseFont(m->font);
            TTF_Quit();
    }

    int GameEngine::width() const { return m->w; }
    int GameEngine::height() const { return m->h; }

    void GameEngine::addSprite(std::unique_ptr<Sprite> s) {
        spawnInternal(std::move(s));
    }

    void GameEngine::spawnInternal(std::unique_ptr<Sprite> s) {
        if (!s) return;
        m->toSpawn.push_back(std::move(s));
    }

    void GameEngine::destroyInternal(std::uint64_t id) {
        m->toDestroy.insert(id);
    }

    void GameEngine::run() {
        std::uint64_t last = SDL_GetTicks();

        while (m->running) {
            std::uint64_t now = SDL_GetTicks();
            float dt = static_cast<float>(now - last) / 1000.0f;
            last = now;

            SDL_Event ev;
            while (SDL_PollEvent(&ev)) {
                InputEvent ie;
                if (!translateEvent(ev, ie)) continue;

                if (ie.type == InputEvent::Type::Quit) {
                    m->running = false;
                    break;
                }

                for (auto& sp : m->sprites) {
                    sp->onEvent(ie, m->world);
                }
            }

            if (!m->gameOver) {
                for (auto& sp : m->sprites) {
                    sp->tick(dt, m->world);
                }
            }

            for (auto& s : m->toSpawn) {
                s->setId(static_cast<Sprite::Id>(m->nextId++)); 
                m->sprites.push_back(std::move(s));
            }
            m->toSpawn.clear();

            if (!m->toDestroy.empty()) {
                m->sprites.erase(
                    std::remove_if(m->sprites.begin(), m->sprites.end(),
                        [&](const std::unique_ptr<Sprite>& sp) {
                            return sp && (m->toDestroy.count(sp->id()) > 0);
                        }),
                    m->sprites.end()
                );
                m->toDestroy.clear();
            }

            SDL_SetRenderDrawColor(m->sdlRenderer, 0, 0, 0, 255);
            SDL_RenderClear(m->sdlRenderer);

            for (auto& sp : m->sprites) {
                sp->render(m->renderer);
            }

            if (m->gameOver) {

                SDL_SetRenderDrawColor(m->sdlRenderer, 255, 0, 0, 255);

                SDL_FRect rect{
                    m->w / 2.0f - 150.0f,
                    m->h / 2.0f - 40.0f,
                    300.0f,
                    80.0f
                };

                SDL_RenderFillRect(m->sdlRenderer, &rect);
            }

            if (m->gameOver) {
                SDL_Color white{255, 255, 255, 255};
                const char* msg = "GAME OVER";

                SDL_Surface* surf = TTF_RenderText_Solid(m->font, msg, std::strlen(msg), white);
                if (surf) {
                    SDL_Texture* tex = SDL_CreateTextureFromSurface(m->sdlRenderer, surf);
                    SDL_DestroySurface(surf);

                    if (tex) {
                        float tw = 0.0f, th = 0.0f;
                        SDL_GetTextureSize(tex, &tw, &th);

                        SDL_FRect dst{
                            (m->w - tw) * 0.5f,
                            (m->h - th) * 0.5f,
                            tw,
                            th
                        };

                        SDL_RenderTexture(m->sdlRenderer, tex, nullptr, &dst);
                        SDL_DestroyTexture(tex);
                    }
                }
            }

            SDL_RenderPresent(m->sdlRenderer);
        }
    }

} 