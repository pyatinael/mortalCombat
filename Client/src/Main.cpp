#include "client/Game.hpp"

#include "client/Game.hpp"

/**
 * @brief Точка входа в клиентское приложение.
 *
 * Создаёт объект игры и запускает основной игровой цикл.
 *
 * @return Код завершения программы.
 */
int main() {
    Game game;
    game.run();

    return 0;
}