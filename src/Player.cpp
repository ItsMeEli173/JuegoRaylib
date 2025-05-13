#include "Player.h"
#include <cstdlib>

Player::~Player() {} // Destructor vacío

Player::Player(Texture2D lateral, Texture2D vertical, Texture2D idleSheet,
               Texture2D descansoSheet, Texture2D mirarFloresSheet, Vector2 startPosition,
               const std::vector<Rectangle>& rects,
               const std::vector<Triangle>& tris)
    : position(startPosition),
      speed(100.0f),
      inSpecialAction(false),
      inactivityTimer(0.0f),
      specialActionTimer(0.0f),
      collisionRects(rects),
      walkableTriangles(tris)
{
    walkRight = Animation(lateral, 32, 48, 3, 0.15f, 0);
    walkLeft  = Animation(lateral, 32, 48, 3, 0.15f, 1);
    walkUp    = Animation(vertical, 32, 48, 3, 0.15f, 0);
    walkDown  = Animation(vertical, 32, 48, 3, 0.15f, 1);
    idle      = Animation(idleSheet, 32, 48, 3, 0.3f, 0);

    descanso = Animation(descansoSheet, 32, 48, 6, 0.3f);
    mirarFlores = Animation(mirarFloresSheet, 32, 48, 6, 0.25f);

    currentAnim = &idle;
}

void Player::update(float deltaTime) {
    if (inSpecialAction) {
        specialActionTimer += deltaTime;
        currentAnim->update(deltaTime);
        if (specialActionTimer >= 6 * 0.3f) {
            inSpecialAction = false;
            inactivityTimer = 0.0f;
            specialActionTimer = 0.0f;
            currentAnim = &idle;
        }
        return;
    }

    velocity = { 0.0f, 0.0f };
    bool moved = false;

    if (IsKeyDown(KEY_RIGHT)) {
        velocity.x += 1.0f;
        currentAnim = &walkRight;
        moved = true;
    } else if (IsKeyDown(KEY_LEFT)) {
        velocity.x -= 1.0f;
        currentAnim = &walkLeft;
        moved = true;
    } else if (IsKeyDown(KEY_UP)) {
        velocity.y -= 1.0f;
        currentAnim = &walkUp;
        moved = true;
    } else if (IsKeyDown(KEY_DOWN)) {
        velocity.y += 1.0f;
        currentAnim = &walkDown;
        moved = true;
    } else {
        currentAnim = &idle;
    }

    if (moved) {
        inactivityTimer = 0.0f;
    } else {
        inactivityTimer += deltaTime;
    }

    Vector2 newPos = {
        position.x + velocity.x * speed * deltaTime,
        position.y + velocity.y * speed * deltaTime
    };

    if (!willCollide(newPos)) {
        position = newPos;
    }

    // LÍMITES DEL MUNDO
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x > 1024 - 32) position.x = 1024 - 32;
    if (position.y > 1536 - 32) position.y = 1536 - 32;

    currentAnim->update(deltaTime);

    if (inactivityTimer >= 5.0f) {
        playRandomAction();
    }
}

bool CheckCollisionPointTriangle(Vector2 point, Vector2 v1, Vector2 v2, Vector2 v3) {
    float d1 = (point.x - v2.x) * (v1.y - v2.y) - (v1.x - v2.x) * (point.y - v2.y);
    float d2 = (point.x - v3.x) * (v2.y - v3.y) - (v2.x - v3.x) * (point.y - v3.y);
    float d3 = (point.x - v1.x) * (v3.y - v1.y) - (v3.x - v1.x) * (point.y - v1.y);
    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);
    return !(has_neg && has_pos);
}

bool Player::willCollide(Vector2 newPosition) {
    // Hitbox de colisión en los pies
    Rectangle hitbox = {
        newPosition.x + 6,              // desplazamiento X para centrar
        newPosition.y + 36,             // parte baja del sprite (48 px alto - 12 px hitbox)
        20,                             // ancho de la hitbox
        12                              // alto de la hitbox
    };

    Vector2 center = {
        hitbox.x + hitbox.width / 2,
        hitbox.y + hitbox.height / 2
    };

    for (const Rectangle& rect : collisionRects) {
        if (CheckCollisionPointRec(center, rect)) {
            for (const Triangle& tri : walkableTriangles) {
                if (CheckCollisionPointTriangle(center, tri.p1, tri.p2, tri.p3)) {
                    return false;
                }
            }
            return true;
        }
    }

    return false;
}


void Player::playRandomAction() {
    inSpecialAction = true;
    specialActionTimer = 0.0f;
    inactivityTimer = 0.0f;

    int r = rand() % 2;
    currentAnim = (r == 0) ? &descanso : &mirarFlores;
}

void Player::draw(bool debug) const {
    currentAnim->draw(position);

    if (debug) {
        Rectangle hitbox = {
            position.x + 6,
            position.y + 36,
            20,
            12
        };
        DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, BLUE);
    }
}



Vector2 Player::getPosition() const {
    return position;
}
