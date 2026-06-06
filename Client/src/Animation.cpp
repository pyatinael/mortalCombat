#include "client/graphics/Animation.hpp"

Animation::Animation(float frameTime) : frameTime(frameTime) {
}

void Animation::addFrame(sf::Texture& texture) {
    frames.push_back(&texture);
}

void Animation::reset() {
    currentFrame = 0;
    timer = 0.f;
}

void Animation::applyToSprite(sf::Sprite& sprite) {
    if (frames.empty()) {
        return;
    }

    sprite.setTexture(*frames[currentFrame]);

    // Сбрасываем origin, чтобы спрайт корректно позиционировался после смены кадра.
    sprite.setOrigin({0.f, 0.f});
}

void Animation::update(float dt) {
    if (frames.empty()) {
        return;
    }

    timer += dt;

    // Если время показа текущего кадра прошло, переключаемся на следующий кадр.
    if (timer >= frameTime) {
        timer = 0.f;
        currentFrame += 1;

        // После последнего кадра анимация начинается заново.
        if (currentFrame >= frames.size()) {
            currentFrame = 0;
        }
    }
}