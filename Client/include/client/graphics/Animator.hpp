#pragma once

#include "Animation.hpp"
#include "FighterState.hpp"
#include <unordered_map>

/**
 * @brief Класс для управления анимациями персонажа.
 *
 * Animator хранит набор анимаций, связанных с состояниями персонажа,
 * и отвечает за выбор текущей анимации, её обновление и применение
 * текущего кадра к спрайту.
 */
class Animator {
private:
    /**
     * @brief Текущее состояние персонажа, для которого проигрывается анимация.
     */
    FighterState currentState = FighterState::Idle;

    /**
     * @brief Словарь анимаций персонажа.
     *
     * Ключом является состояние персонажа, например Idle, Walk, Attack или Die.
     * Значением является объект Animation, который содержит кадры для этого состояния.
     */
    std::unordered_map<FighterState, Animation> animations;

public:
    /**
     * @brief Добавляет анимацию для указанного состояния персонажа.
     *
     * @param state Состояние персонажа, к которому относится анимация.
     * @param animation Анимация, которая будет проигрываться для этого состояния.
     */
    void addAnimation(FighterState state, const Animation& animation);

    /**
     * @brief Применяет текущий кадр активной анимации к спрайту.
     *
     * @param sprite Спрайт, к которому применяется текущая анимация.
     */
    void applyToSprite(sf::Sprite& sprite);

    /**
     * @brief Обновляет активную анимацию.
     *
     * Увеличивает таймер текущей анимации и переключает кадр,
     * если прошло достаточно времени.
     *
     * @param dt Время, прошедшее с предыдущего обновления, в секундах.
     */
    void update(float dt);

    /**
     * @brief Переключает активную анимацию на указанное состояние.
     *
     * Если новое состояние отличается от текущего, Animator начинает
     * проигрывать соответствующую анимацию.
     *
     * @param state Новое состояние персонажа.
     */
    void play(FighterState state);
};