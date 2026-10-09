#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include <memory>
#include <string>

namespace engine {

    class Renderer {
    public:
        Renderer();         
        ~Renderer(); 

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;

        void drawImage(const std::string& filePath, float x, float y, float w, float h);

        void setNativeRenderer(void* nativeRenderer);

        void clear();
        void present();

    private:
        struct Impl;
        std::unique_ptr<Impl> m;
    };

} 

#endif
