#include "Renderer.h"

#include <stdexcept>
#include <unordered_map>


#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>


namespace engine {

    struct Renderer::Impl {
        SDL_Renderer* renderer{ nullptr };

        std::unordered_map<std::string, SDL_Texture*> textures;

        ~Impl() {
            for (auto& kv : textures) {
                if (kv.second) SDL_DestroyTexture(kv.second);
            }
            textures.clear();
        }

        SDL_Texture* getTexture(const std::string& path) {
            auto it = textures.find(path);
            if (it != textures.end()) return it->second;

            SDL_Surface* surf = IMG_Load(path.c_str());
            if (!surf) return nullptr;

            SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_DestroySurface(surf);

            textures[path] = tex;
            return tex;
        }
    };

    Renderer::Renderer() : m(std::make_unique<Impl>()) {}
    Renderer::~Renderer() = default;

    void Renderer::drawImage(const std::string& filePath, float x, float y, float w, float h) {
        SDL_Texture* tex = m->getTexture(filePath);
        if (!tex) return;

        SDL_FRect dst{ x, y, w, h };
        SDL_RenderTexture(m->renderer, tex, nullptr, &dst);
    }

    void Renderer::setNativeRenderer(void* nativeRenderer) {
        m->renderer = static_cast<SDL_Renderer*>(nativeRenderer);
    }

    void Renderer::clear() {
        SDL_RenderClear(m->renderer);
    }

    void Renderer::present() {
        SDL_RenderPresent(m->renderer);
    }

} 