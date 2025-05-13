#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "Animation.h"
#include "Geometry.h"
#include <vector>

class Player {
public:
    Player(Texture2D lateral, Texture2D vertical, Texture2D idleSheet,
           Texture2D descansoSheet, Texture2D mirarFloresSheet, Vector2 startPosition,
           const std::vector<Rectangle>& rects,
           const std::vector<Triangle>& tris);
    ~Player();

    void update(float deltaTime);
    void draw(bool debug = false) const;
    Vector2 getPosition() const;

private:
    Vector2 position;
    Vector2 velocity;
    float speed;

    Animation walkRight;
    Animation walkLeft;
    Animation walkUp;
    Animation walkDown;
    Animation idle;

    Animation descanso;
    Animation mirarFlores;

    Animation* currentAnim;

    bool inSpecialAction;
    float inactivityTimer;
    float specialActionTimer;

    const std::vector<Rectangle> collisionRects;
    const std::vector<Triangle> walkableTriangles;

    void playRandomAction();
    bool willCollide(Vector2 newPosition);
};

#endif
