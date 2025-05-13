#include "Game.h"
#include "raylib.h"
#include "CollisionZones.h"
#include <filesystem>

Game::Game() {
    InitWindow(800, 600, "Juego con Raylib");
    InitAudioDevice();
    SetTargetFPS(60);

    // Cargar música si existe
    if (std::filesystem::exists("assets/music/backgroundmusic.mp3")) {
        backgroundMusic = LoadMusicStream("assets/music/backgroundmusic.mp3");
        PlayMusicStream(backgroundMusic);
    }

    // Cargar imágenes
    background = LoadTexture("assets/images/background.png");
    spriteLateral = LoadTexture("assets/images/caminata_lateral.png");
    spriteVertical = LoadTexture("assets/images/caminata_vertical.png");
    spriteIdle = LoadTexture("assets/images/estado_de_espera.png");
    spriteDescanso = LoadTexture("assets/images/descanso.png");
    spriteMirarFlores = LoadTexture("assets/images/mirar_flores.png");

    // Cargar colisiones (debe ir ANTES del jugador)
    loadCollisionZones(collisionRects, walkableTriangles);
    // Crear jugador
    player = new Player(spriteLateral, spriteVertical, spriteIdle, spriteDescanso, spriteMirarFlores, { 512.0f, 768.0f }, collisionRects, walkableTriangles);

    camera.target = player->getPosition();
    camera.offset = { 400, 300 };
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;
    
}

Game::~Game() {
    delete player;

    // Unload recursos
    UnloadTexture(background);
    UnloadTexture(spriteLateral);
    UnloadTexture(spriteVertical);
    UnloadTexture(spriteIdle);
    UnloadTexture(spriteDescanso);
    UnloadTexture(spriteMirarFlores);

    if (IsMusicStreamPlaying(backgroundMusic)) {
        StopMusicStream(backgroundMusic);
        UnloadMusicStream(backgroundMusic);
    }

    CloseAudioDevice();
    CloseWindow();
}

void Game::run() {
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        if (IsMusicStreamPlaying(backgroundMusic)) {
            UpdateMusicStream(backgroundMusic);
        }

       // Toggle del modo debug con TAB
        if (IsKeyPressed(KEY_TAB)) {
            showCollisionDebug = !showCollisionDebug;
        }

        player->update(delta);
        camera.target = player->getPosition();

        BeginDrawing();
        ClearBackground(Color{ 170,200,150,255 });

        BeginMode2D(camera);
        DrawTexture(background, 0, 0, WHITE);
        player->draw(showCollisionDebug);

        // Dibujar zonas de colisión si el modo debug está activado
        if (showCollisionDebug) {
            for (const Rectangle& r : collisionRects) {
                DrawRectangleLines(r.x, r.y, r.width, r.height, RED);
            }
        
            for (const Triangle& t : walkableTriangles) {
                DrawTriangleLines(t.p1, t.p2, t.p3, GREEN);
            }
        }

        EndMode2D();
        EndDrawing();
    }
}
