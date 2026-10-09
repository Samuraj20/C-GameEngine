#include "Constants.h"
#include "engine/GameEngine.h"
#include "game/EnemySpawner.h"

#include "game/Player.h"
#include "game/Enemy.h"

#include <memory>

int main() {
    engine::GameEngine engine("Top Down Shooter", WINDOW_W, WINDOW_H);

    engine.addSprite(std::make_unique<Player>(
        IMG_PLAYER,
        WINDOW_W * 0.5f - 25.0f,
        WINDOW_H - 80.0f
    ));

    engine.addSprite(std::make_unique<EnemySpawner>(0.7f, 15));

    engine.run();
    return 0;
}
