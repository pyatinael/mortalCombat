#include "resource/TextureManager.hpp"
#include <iostream>

TextureManager& TextureManager::getInstance() {
    // Создаём единственный экземпляр менеджера текстур.
    static TextureManager manager;
    return manager;
}

sf::Texture& TextureManager::getTexture(const std::string& path) {
    // Если текстура ещё не загружена, загружаем её из файла.
    if (textures.find(path) == textures.end()) {
        sf::Texture texture;

        if (!texture.loadFromFile(path)) {
            std::cerr << "Fail load texture: " << path << std::endl;
        }

        textures[path] = std::move(texture);
    }

    // Возвращаем уже загруженную текстуру из хранилища.
    return textures[path];
}