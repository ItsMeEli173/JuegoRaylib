#include "Animation.h"

Animation::Animation() : currentFrame(0), frameTimer(0.0f), frameDuration(0.2f), valid(false) {}

Animation::Animation(Texture2D spriteSheet, int frameWidth, int frameHeight, int frameCount, float frameDuration, int row)
    : spriteSheet(spriteSheet), currentFrame(0), frameTimer(0.0f), frameDuration(frameDuration), valid(true)
{
    float yOffset = row * frameHeight;
    for (int i = 0; i < frameCount; ++i) {
        Rectangle frameRect = { (float)(i * frameWidth), yOffset, (float)frameWidth, (float)frameHeight };
        frames.push_back({ frameRect });
    }
}

void Animation::update(float deltaTime) {
    if (!valid) return;
    frameTimer += deltaTime;
    if (frameTimer >= frameDuration) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % frames.size();
    }
}

void Animation::draw(Vector2 position) const {
    if (!valid) return;
    DrawTextureRec(spriteSheet, frames[currentFrame].source, position, WHITE);
}
