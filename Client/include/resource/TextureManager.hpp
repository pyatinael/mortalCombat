#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

/**
 * @brief Класс для загрузки и хранения текстур.
 *
 * TextureManager хранит уже загруженные текстуры и позволяет повторно
 * использовать их по пути к файлу без повторной загрузки с диска.
 */
class TextureManager {
private:
    /** @brief Словарь загруженных текстур, где ключом является путь к файлу. */
    std::unordered_map<std::string, sf::Texture> textures;

public:
    /**
     * @brief Возвращает текстуру по указанному пути.
     *
     * Если текстура ещё не была загружена, она загружается из файла
     * и сохраняется во внутреннем словаре.
     *
     * @param path Путь к файлу текстуры.
     * @return Ссылка на загруженную текстуру.
     */
    sf::Texture& getTexture(const std::string& path);

    /**
     * @brief Возвращает единственный экземпляр менеджера текстур.
     *
     * Используется для доступа к общему хранилищу текстур из разных частей игры.
     *
     * @return Ссылка на объект TextureManager.
     */
    static TextureManager& getInstance();
};