#include "GamePlay/Stage.hpp"
#include "resource/TextureManager.hpp"

Stage::Stage() : background(TextureManager::getInstance().getTexture("../Assets/menu.png")) {
}

void Stage::setBackground(const std::string& path, sf::RenderWindow& window) {
    // Загружаем текстуру выбранной карты.
    auto& texture = TextureManager::getInstance().getTexture(path);

    background.setTexture(texture, true);

    // Масштабируем фон под размер окна.
    float scaleX = window.getSize().x / static_cast<float>(texture.getSize().x);
    float scaleY = window.getSize().y / static_cast<float>(texture.getSize().y);

    background.setScale({scaleX, scaleY});
    background.setPosition({0.f, 0.f});
}

void Stage::render(sf::RenderWindow& window) {
    // Отрисовываем фон арены.
    window.draw(background);
}