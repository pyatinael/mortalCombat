#pragma once

#include <SFML/Network.hpp>
#include <cstdint>

#include "GameStatePacket.hpp"
#include "network/InputPacket.hpp"

/**
 * @brief Класс сетевого клиента.
 *
 * Отвечает за подключение к серверу, отправку выбранной карты,
 * выбранного персонажа и пользовательского ввода, а также за получение
 * текущего состояния игры от сервера.
 */
class NetworkClient {
private:
    /** @brief TCP-сокет для обмена данными с сервером. */
    sf::TcpSocket socket;

    /** @brief Флаг текущего подключения к серверу. */
    bool connected = false;

    /** @brief Идентификатор игрока, выданный сервером. */
    std::uint32_t playerId = 999;

    /** @brief Флаг, показывающий, был ли получен id игрока. */
    bool hasPlayerId = false;

public:
    /**
     * @brief Подключается к серверу.
     *
     * @param ip IP-адрес сервера.
     * @param port Порт сервера.
     * @return true, если подключение выполнено успешно.
     */
    bool connect(const sf::IpAddress& ip, unsigned short port);

    /**
     * @brief Отключает клиента от сервера.
     */
    void disconnect();

    /**
     * @brief Проверяет, подключён ли клиент к серверу.
     *
     * @return true, если клиент подключён.
     */
    bool isConnected() const;

    /**
     * @brief Отправляет выбранную карту на сервер.
     *
     * @param mapId Индекс выбранной карты.
     * @return true, если пакет успешно отправлен.
     */
    bool sendMap(std::uint32_t mapId);

    /**
     * @brief Отправляет выбранного персонажа на сервер.
     *
     * @param character Идентификатор выбранного персонажа.
     * @return true, если пакет успешно отправлен.
     */
    bool sendCharacter(std::uint8_t character);

    /**
     * @brief Отправляет ввод игрока на сервер.
     *
     * @param input Пакет с данными о движении, атаке и хитбоксе игрока.
     * @return true, если пакет успешно отправлен.
     */
    bool sendInput(const InputPacket& input);

    /**
     * @brief Получает текущее состояние игры от сервера.
     *
     * @param state Переменная, в которую записывается полученное состояние игры.
     * @return true, если состояние было успешно получено.
     */
    bool receiveGameState(GameStatePacket& state);

    /**
     * @brief Возвращает id текущего игрока.
     *
     * @return Идентификатор игрока, полученный от сервера.
     */
    std::uint32_t getPlayerId() const;

    /**
     * @brief Проверяет, получил ли клиент id от сервера.
     *
     * @return true, если id уже получен.
     */
    bool hasId() const;
};