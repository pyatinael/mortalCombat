#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "GamePlay/Stage.hpp"
#include "GamePlay/Fighter.hpp"
#include "network/NetworkClient.hpp"

#include <optional>
#include <iostream>
#include <memory>

/**
 * @brief Экраны клиентской части игры.
 *
 * Используется для переключения между главным меню, выбором карты,
 * выбором персонажа, боем и финальными экранами.
 */
enum class GameScreen {

    MainMenu,
    MapSelect,
    CharacterSelect,
    Fight,
    Win,
    Lose
};

/**
 * @brief Основной класс клиентской части игры.
 *
 * Отвечает за создание окна, обработку пользовательского ввода,
 * переключение экранов, отрисовку интерфейса и обмен данными с сервером.
 */
class Game {
private:
    /** @brief Главное окно игры. */
    sf::RenderWindow window;

    /** @brief Текущий экран игры. */
    GameScreen screen = GameScreen::MainMenu;

    // Кнопки и изображения главного меню.
    sf::RectangleShape startButton;
    sf::RectangleShape playButtonImage;
    sf::RectangleShape logoImage;
    sf::RectangleShape startFightButton;

    // Фоны игровых экранов.
    sf::RectangleShape menuBackground;
    sf::RectangleShape mapSelectBackground;
    sf::RectangleShape characterBackground;
    sf::RectangleShape winBackground;
    sf::RectangleShape loseBackground;

    // Кнопки выбора персонажей.
    sf::RectangleShape orkButton;
    sf::RectangleShape ork2Button;
    sf::RectangleShape ork3Button;
    sf::RectangleShape ogreButton;
    sf::RectangleShape devilButton;
    sf::RectangleShape devil2Button;
    sf::RectangleShape trollButton;
    sf::RectangleShape zombieButton;
    sf::RectangleShape zombie2Button;
    sf::RectangleShape gremlinButton;
    sf::RectangleShape goblinButton;
    sf::RectangleShape marauderButton;

    /** @brief Часы для расчёта времени между кадрами анимации. */
    sf::Clock animationClock;

    /** @brief Текущая арена боя. */
    Stage stage;

    /** @brief Персонаж текущего клиента. */
    std::unique_ptr<Fighter> fighter;

    /** @brief Персонаж противника. */
    std::unique_ptr<Fighter> enemy;

    /** @brief Объект для сетевого взаимодействия с сервером. */
    NetworkClient networkClient;

    /** @brief Показывает, подключён ли клиент к серверу. */
    bool serverConnected = false;

    /** @brief Последнее состояние игры, полученное от сервера. */
    GameStatePacket lastState;

    /** @brief Персонаж, выбранный текущим клиентом. */
    Character selectedCharacter = Character::None;

    /** @brief Кнопки выбора карт. */
    std::vector<sf::RectangleShape> mapButtons;

    /** @brief Пути к изображениям карт. */
    std::vector<std::string> mapPaths;

    /** @brief Индекс выбранной карты. */
    int selectedMap = 0;

    /**
     * @brief Обновляет состояние игры.
     *
     * Получает данные от сервера, обновляет персонажей,
     * обрабатывает состояние матча и отправляет ввод игрока.
     */
    void update();

    /**
     * @brief Отрисовывает текущий экран игры.
     */
    void render();

    /**
     * @brief Обрабатывает события окна и действия пользователя.
     *
     * Обрабатывает закрытие окна, клики мыши, выбор карты,
     * выбор персонажа и переход между экранами.
     */
    void processEvent();

    /** @brief Отрисовывает главное меню. */
    void renderMainMenu();

    /** @brief Отрисовывает экран выбора карты. */
    void renderMapSelect();

    /** @brief Отрисовывает экран выбора персонажа. */
    void renderCharacterSelect();

    /**
     * @brief Отрисовывает экран боя.
     *
     * Рисует арену, персонажа текущего клиента, противника
     * и элементы здоровья.
     */
    void renderFight();

    /** @brief Отрисовывает экран победы. */
    void renderWin();

    /** @brief Отрисовывает экран поражения. */
    void renderLose();

public:
    /**
     * @brief Создаёт объект игры.
     *
     * Инициализирует окно, фоны, кнопки, список карт
     * и подключение к серверу.
     */
    Game();

    /**
     * @brief Запускает основной игровой цикл.
     *
     * Пока окно открыто, обрабатывает события, обновляет состояние
     * игры и отрисовывает текущий экран.
     */
    void run();
};
