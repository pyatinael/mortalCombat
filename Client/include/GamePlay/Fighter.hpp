#pragma once

#include "Entity.hpp"
#include "GamePlay/HitBox.hpp"
#include "FighterState.hpp"
#include "client/graphics/Animator.hpp"
#include "GamePlay/Character.hpp"
#include <SFML/Graphics.hpp>

/**
 * @brief Класс игрового персонажа на клиенте.
 *
 * Отвечает за отображение персонажа, проигрывание анимаций,
 * хранение здоровья, хитбокса и визуального состояния.
 */
class Fighter : public Entity {
private:
    /** @brief Основные параметры здоровья персонажа. */
    int hp = 100;
    float maxHealth = 100.f;
    float health = 100.f;

    /** @brief Параметры прыжка и гравитации. */
    bool isJumping = false;
    float jumpForce = -900.f;
    float gravity = 1200.f;
    float groundY;

    /** @brief Параметры масштаба, позиции и границ движения. */
    float scale = 0.5f;
    float posX;
    float minX = 0.f;
    float maxX = 1920.f;

    /** @brief Направление взгляда персонажа. */
    bool facingRight = true;

    /** @brief Хитбокс персонажа, используемый для проверки столкновений. */
    HitBox hitbox{};

    /** @brief Спрайты персонажа и элементов здоровья. */
    sf::Sprite sprite;
    sf::Sprite healthBack;
    sf::Sprite healthFront;
    sf::Sprite heartSprite;

    /** @brief Объект управления анимациями персонажа. */
    Animator animator;

    /** @brief Тип выбранного персонажа. */
    Character character;

    /** @brief Текущее логическое и анимационное состояние персонажа. */
    FighterState state = FighterState::Idle;
    FighterState currentAnimationState = FighterState::Idle;

    /**
     * @brief Обрабатывает локальный ввод персонажа.
     *
     * Используется для обновления скорости, состояния ходьбы,
     * прыжка и атаки в локальной логике.
     *
     * @param dt Время, прошедшее с прошлого обновления.
     */
    void processInput(float dt);

public:
    /**
     * @brief Создаёт персонажа выбранного типа.
     *
     * Загружает нужные текстуры, настраивает масштаб, стартовую позицию,
     * анимации и элементы здоровья.
     *
     * @param selectedCharacter Тип персонажа, выбранный игроком.
     */
    Fighter(Character selectedCharacter);

    /**
     * @brief Возвращает тип персонажа.
     *
     * @return Значение enum Character для текущего персонажа.
     */
    Character getCharacter() const;

    /**
     * @brief Задаёт направление взгляда персонажа.
     *
     * @param right true, если персонаж смотрит вправо; false, если влево.
     */
    void setFacingRight(bool right);

    /**
     * @brief Обновляет только анимацию персонажа.
     *
     * Используется в сетевом режиме, когда позиция приходит от сервера,
     * а клиент только отображает нужное состояние.
     *
     * @param dt Время, прошедшее с прошлого обновления.
     */
    void updateAnimation(float dt);

    /**
     * @brief Устанавливает текущее состояние персонажа.
     *
     * @param newState Новое состояние персонажа: Idle, Walk, Attack, Hurt или Die.
     */
    void setState(FighterState newState);

    /**
     * @brief Задаёт позицию полоски здоровья.
     *
     * @param x Координата X.
     * @param y Координата Y.
     * @param flip Нужно ли отразить расположение элементов здоровья.
     */
    void setHealthBarPosition(float x, float y, bool flip = false);

    /**
     * @brief Обновляет персонажа в локальном режиме.
     *
     * Обрабатывает ввод, физику прыжка, гравитацию, позицию,
     * анимацию и ограничения движения.
     *
     * @param dt Время, прошедшее с прошлого обновления.
     */
    void update(float dt) override;

    /**
     * @brief Отрисовывает персонажа.
     *
     * @param window Окно, в которое выполняется отрисовка.
     */
    void render(sf::RenderWindow& window);

    /**
    * @brief Устанавливает позицию персонажа.
     *
     * @param x Новая координата X.
     * @param y Новая координата Y.
     */
    void setPosition(float x, float y);

    /**
     * @brief Устанавливает текущее здоровье персонажа.
     *
     * @param value Новое значение здоровья.
     */
    void setHealth(float value);

    /**
     * @brief Отрисовывает здоровье персонажа.
     *
    @param window Окно, в которое выполняется отрисовка.
     */
    void drawHealth(sf::RenderWindow& window);

    /**
     * @brief Возвращает текущий хитбокс персонажа.
     *
     * @return Хитбокс персонажа.
     */
    HitBox getHitbox() const;

    /**
     * @brief Обновляет хитбокс относительно текущей позиции персонажа.
     */
    void updateHitbox();

    /**
     * @brief Отрисовывает хитбокс для отладки.
     *
     * @param window Окно, в которое выполняется отрисовка.
     */
    void drawDebugHitbox(sf::RenderWindow& window);
};