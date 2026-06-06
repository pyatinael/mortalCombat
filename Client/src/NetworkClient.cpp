#include "network/NetworkClient.hpp"
<<<<<<< Updated upstream
#include "network/PacketType.hpp"

#include <iostream>
#include <cstdint>

bool NetworkClient::connect(const sf::IpAddress& ip, unsigned short port) {
    // Пытаемся подключиться к серверу.
    if (socket.connect(ip, port) != sf::Socket::Status::Done) {
        std::cout << "Cannot connect to server\n";
        connected = false;
        return false;
    }
    // Переводим сокет в неблокирующий режим, чтобы игра не зависала при ожидании пакетов.
    socket.setBlocking(false);

    std::cout << "Connected to server\n";
    connected = true;
=======
#include "network/InputPacket.hpp"
#include "network/PacketType.hpp"

#include <iostream>

#include <cstdint>

bool NetworkClient::connect(
    const sf::IpAddress& ip,
    unsigned short port
) {
    if (socket.connect(ip, port) != sf::Socket::Done) {
        return false;
    }

    socket.setBlocking(false);

    std::cout << "Connected" << std::endl;

>>>>>>> Stashed changes
    return true;
}

void NetworkClient::disconnect() {
<<<<<<< Updated upstream
    // Закрываем соединение с сервером.
    socket.disconnect();
    connected = false;
}

bool NetworkClient::isConnected() const {
    return connected;
}

bool NetworkClient::sendMap(std::uint32_t mapId) {
    if (!connected) {
        return false;
    }

    sf::Packet packet;

    // Отправляем серверу пакет с выбранной картой.
    packet << static_cast<std::uint8_t>(PacketType::MapSelect);
    packet << mapId;

    return socket.send(packet) == sf::Socket::Status::Done;
}

bool NetworkClient::sendCharacter(std::uint8_t character) {
    if (!connected) {
        return false;
    }

    sf::Packet packet;

    // Отправляем серверу пакет с выбранным персонажем.
    packet << static_cast<std::uint8_t>(PacketType::CharacterSelect);
    packet << character;

    return socket.send(packet) == sf::Socket::Status::Done;
}

bool NetworkClient::sendInput(const InputPacket& input) {
    if (!connected) {
        return false;
    }

    sf::Packet packet;

    // Отправляем серверу текущее состояние клавиш и хитбокс игрока.
    packet << static_cast<std::uint8_t>(PacketType::Input);
    packet << input.left
        << input.right
        << input.jump
        << input.attack
        << input.hitboxX
        << input.hitboxY
        << input.hitboxW
        << input.hitboxH;

    return socket.send(packet) == sf::Socket::Status::Done;
}

bool NetworkClient::receiveGameState(GameStatePacket& state) {
    if (!connected) {
        return false;
    }

    sf::Packet packet;

    // Пробуем получить пакет от сервера.
    auto status = socket.receive(packet);

    if (status == sf::Socket::Status::NotReady) {
        return false;
    }

    if (status == sf::Socket::Status::Disconnected ||
        status == sf::Socket::Status::Error) {
        connected = false;
        return false;
    }

    if (status != sf::Socket::Status::Done) {
=======
    socket.disconnect();
}

bool NetworkClient::sendInput(const InputPacket& input) {
    sf::Packet packet;

    packet << static_cast<std::uint8_t>(PacketType::Input);

    packet << input.left << input.right << input.attack;

    auto status = socket.send(packet);

    std::cout
        << "send status = "
        << status
        << std::endl;

    if (status == sf::Socket::Done) {
        std::cout << "Input sent" << std::endl;
    }

    return status == sf::Socket::Done;
}

bool NetworkClient::receiveState(
    FighterStatePacket& state
)
{
    sf::Packet packet;

    auto status =
        socket.receive(packet);

    if (status == sf::Socket::NotReady)
    {
        return false;
    }

    if (status != sf::Socket::Done)
    {
>>>>>>> Stashed changes
        return false;
    }

    std::uint8_t typeUint8;
<<<<<<< Updated upstream
    packet >> typeUint8;

    PacketType type = static_cast<PacketType>(typeUint8);

    // Пакет AssignId приходит один раз и сохраняет id игрока.
    if (type == PacketType::AssignId) {
        packet >> playerId;
        hasPlayerId = true;

        std::cout << "My player id = " << playerId << std::endl;
        return false;
    }

    // Здесь ожидается пакет состояния игры.
    if (type != PacketType::State) {
        return false;
    }

    std::uint8_t phaseUint8;

    // Читаем общую информацию о матче.
    packet >> phaseUint8;
    state.phase = static_cast<GamePhase>(phaseUint8);

    packet >> state.mapId;
    packet >> state.winnerId;

    // Читаем состояние первого игрока.
    packet >> state.player1.playerId
           >> state.player1.x
           >> state.player1.y
           >> state.player1.hp
           >> state.player1.character
           >> state.player1.state;

    // Читаем состояние второго игрока.
    packet >> state.player2.playerId
           >> state.player2.x
           >> state.player2.y
           >> state.player2.hp
           >> state.player2.character
           >> state.player2.state;

    return true;
}

std::uint32_t NetworkClient::getPlayerId() const {
    return playerId;
}

bool NetworkClient::hasId() const {
    return hasPlayerId;
=======

    packet >> typeUint8;

    PacketType type =
        static_cast<PacketType>(typeUint8);

    if (type != PacketType::State)
    {
        return false;
    }

    packet
        >> state.playerId
        >> state.x
        >> state.y;

    return true;
>>>>>>> Stashed changes
}