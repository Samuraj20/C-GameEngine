#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

inline const std::string gResPath{ "./resources/" };

inline const std::string IMG_PLAYER{ gResPath + "images/Player.png" };
inline const std::string IMG_ENEMY{ gResPath + "images/Enemy.png" };
inline const std::string IMG_BULLET{ gResPath + "images/Bullet.png" };

inline const std::string FONT_UI{ gResPath + "fonts/PressStart2P-Regular.ttf" };

inline constexpr int WINDOW_W = 960;
inline constexpr int WINDOW_H = 540;

inline constexpr float PLAYER_SPEED = 260.0f;  
inline constexpr float BULLET_SPEED = 520.0f;
inline constexpr float ENEMY_SPEED = 120.0f;

#endif // CONSTANTS_H