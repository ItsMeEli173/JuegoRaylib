#ifndef ANIMATION_H
#define ANIMATION_H

#include "raylib.h"
#include <vector>

struct AnimationFrame {
    Rectangle source;
};

class Animation {
public:
    Animation();
    Animation(Texture2D spriteSheet, int frameWidth, int frameHeight, int frameCount, float frameDuration, int row = 0);
    void update(float deltaTime);
    void draw(Vector2 position) const;

private:
    Texture2D spriteSheet;
    std::vector<AnimationFrame> frames;
    int currentFrame;
    float frameTimer;
    float frameDuration;
    bool valid;
};

#endif
