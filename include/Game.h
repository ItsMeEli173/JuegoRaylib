#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Geometry.h"
#include "raylib.h"
#include <vector>

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    Player* player;

    // Recursos gráficos
    Texture2D background;
    Texture2D spriteLateral;
    Texture2D spriteVertical;
    Texture2D spriteIdle;
    Texture2D spriteDescanso;
    Texture2D spriteMirarFlores;

    // Cámara
    Camera2D camera;

    // Audio
    Music backgroundMusic;

    // --- NUEVOS ELEMENTOS PARA DEBUG Y COLISIONES ---
    std::vector<Rectangle> collisionRects;
    std::vector<Triangle> walkableTriangles;
    bool showCollisionDebug = false;  // Toggle para mostrar/ocultar colisiones
};

#endif
