#pragma once

#include <SFML/Graphics.hpp>
#include <string>

/**
 * @brief Класс игровой арены.
 *
 * Хранит и отрисовывает фон выбранной карты боя.
 */
class Stage {
private:
    /** @brief Спрайт фона текущей арены. */
    sf::Sprite background;

public:
    /**
     * @brief Создаёт объект арены.
     */
    Stage();

    /**
     * @brief Устанавливает фон арены по пути к изображению.
     *
     * @param path Путь к файлу изображения карты.
     * @param window Окно игры, размер которого используется для подгонки фона.
     */
    void setBackground(const std::string& path, sf::RenderWindow& window);

    /**
     * @brief Отрисовывает арену.
     *
     * @param window Окно, в которое выполняется отрисовка.
     */
    void render(sf::RenderWindow& window);
};