#include "client/Game.hpp"
#include "resource/TextureManager.hpp"

Game::Game(): window(sf::VideoMode({1920,1080}),"SFML works!") {
    window.setFramerateLimit(60);
    serverConnected = networkClient.connect(sf::IpAddress::LocalHost, 54000);

    startButton.setSize({700.f, 370.f});
    startButton.setPosition({(window.getSize().x - 700.f) / 2.f, 370.f});

    auto& texture = TextureManager::getInstance().getTexture("../Assets/playButton.png");
    playButtonImage.setTexture(&texture);
    playButtonImage.setSize(startButton.getSize());
    playButtonImage.setPosition(startButton.getPosition());

    logoImage.setTexture(&TextureManager::getInstance().getTexture("../Assets/logo.png"));
    logoImage.setPosition({(window.getSize().x - 1170.f) / 2.f, -10.f});
    logoImage.setSize({1200.f,700.f});

    menuBackground.setSize({ static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
    menuBackground.setTexture(&TextureManager::getInstance().getTexture("../Assets/menu.png"));

    mapSelectBackground.setSize({static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y)});
    mapSelectBackground.setTexture(&TextureManager::getInstance().getTexture("../Assets/mapSelect.png"));

    characterBackground.setSize({static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y)});
    characterBackground.setTexture(&TextureManager::getInstance().getTexture("../Assets/characterSelect.png"));

    orkButton.setSize({370.f, 200.f});
    orkButton.setPosition({150.f, 80.f});
    orkButton.setTexture(&TextureManager::getInstance().getTexture("../Assets/characters/ch2.png"));

    ork2Button.setSize({370.f, 200.f});
    ork2Button.setPosition({420.f, 80.f});
    ork2Button.setTexture(&TextureManager::getInstance().getTexture("../Assets/characters/ch8.png"));

    ork3Button.setSize({370.f, 200.f});
    ork3Button.setPosition({690.f, 80.f});
    ork3Button.setTexture(&TextureManager::getInstance().getTexture("../Assets/characters/ch11.png"));

    ogreButton.setSize({370.f, 200.f});
    ogreButton.setPosition({960.f, 80.f});
    ogreButton.setTexture(&TextureManager::getInstance().getTexture("../Assets/characters/ch12.png"));

    devilButton.setSize({370.f, 200.f});
    devilButton.setPosition({150.f, 300.f});
    devilButton.setTexture(&TextureManager::getInstance().getTexture("../Assets/characters/ch10.png"));

    devil2Button.setSize({370.f, 200.f});
    devil2Button.setPosition({420.f, 300.f});
    devil2Button.setTexture(&TextureManager::getInstance().getTexture("../Assets/characters/ch7.png"));

    goblinButton.setSize({370.f, 200.f});
    goblinButton.setPosition({690.f, 300.f});
    goblinButton.setTexture(&TextureManager::getInstance().getTexture("../Assets/characters/ch9.png"));

    gremlinButton.setSize({370.f, 200.f});
    gremlinButton.setPosition({960.f, 300.f});
    gremlinButton.setTexture(&TextureManager::getInstance().getTexture("../Assets/characters/ch3.png"));

    zombieButton.setSize({370.f, 200.f});
    zombieButton.setPosition({150.f, 520.f});
    zombieButton.setTexture(&TextureManager::getInstance().getTexture("../Assets/characters/ch1.png"));

    zombie2Button.setSize({370.f, 200.f});
    zombie2Button.setPosition({420.f, 520.f});
    zombie2Button.setTexture(&TextureManager::getInstance().getTexture("../Assets/characters/ch4.png")); 
    
    trollButton.setSize({370.f, 200.f});
    trollButton.setPosition({690.f, 520.f});
    trollButton.setTexture(&TextureManager::getInstance().getTexture("../Assets/characters/ch6.png"));

    marauderButton.setSize({370.f, 200.f});
    marauderButton.setPosition({960.f, 520.f});
    marauderButton.setTexture(&TextureManager::getInstance().getTexture("../Assets/characters/ch5.png"));

    startFightButton.setSize({640.f, 320.f});
    startFightButton.setPosition({(window.getSize().x - 670.f) / 2.f, 600.f});
    startFightButton.setTexture(&TextureManager::getInstance().getTexture("../Assets/startButton.png"));

    mapPaths = {
        "../Assets/maps/map1.png",
        "../Assets/maps/map2.png",
        "../Assets/maps/map3.png",
        "../Assets/maps/map4.png",
        "../Assets/maps/map5.png",
        "../Assets/maps/map6.png"
    };

    float cardW = 400.f;
    float cardH = 230.f;

    float gapX = 100.f;
    float gapY = 80.f;

    int cols = 3;
    int rows = 2;

    float totalW = cols * cardW + (cols - 1) * gapX;
    float totalH = rows * cardH + (rows - 1) * gapY;

    float startX = (window.getSize().x - totalW) / 2.f;
    float startY = (window.getSize().y - totalH) / 2.f;

    for (int i = 0; i < 6; i++) {
        sf::RectangleShape rect;

        rect.setSize({cardW, cardH});
        rect.setTexture(&TextureManager::getInstance().getTexture(mapPaths[i]));
        float x = startX + (i % cols) * (cardW + gapX);
        float y = startY + (i / cols) * (cardH + gapY);
        rect.setPosition({x, y});

        mapButtons.push_back(rect);
    }

    winBackground.setSize({static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y)});
    winBackground.setTexture(&TextureManager::getInstance().getTexture("../Assets/win.png"));

    loseBackground.setSize({static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y)});
    loseBackground.setTexture(&TextureManager::getInstance().getTexture("../Assets/lose.png"));
}

void Game::update() {
    float animationDt = animationClock.restart().asSeconds();

    if (animationDt > 0.05f) {
        animationDt = 0.05f;
    }

    if (!serverConnected || !networkClient.isConnected()) {
        return;
    }

    GameStatePacket state;
    while (networkClient.receiveGameState(state)) {
        lastState = state;
        selectedMap = static_cast<int>(state.mapId);

        if (selectedMap >= 0 &&
            selectedMap < static_cast<int>(mapPaths.size())) {
            stage.setBackground(mapPaths[selectedMap], window);
        }

        if (state.phase == GamePhase::WaitingCharacters) {
            if (screen == GameScreen::MainMenu ||
                screen == GameScreen::MapSelect) {
                screen = GameScreen::CharacterSelect;
            }
        }

        if (state.phase == GamePhase::Dying) {
            screen = GameScreen::Fight;
        }

        if (state.phase == GamePhase::Finished) {
            if (state.winnerId == networkClient.getPlayerId()) {
                screen = GameScreen::Win;
            } 
            else {
                screen = GameScreen::Lose;
            }

            return;
        }

        if (state.phase == GamePhase::Running || state.phase == GamePhase::Dying) {
            std::uint32_t myId = networkClient.getPlayerId();

            FighterStatePacket myState;
            FighterStatePacket enemyState;

            if (state.player1.playerId == myId) {
                myState = state.player1;
                enemyState = state.player2;
            } 
            else {
                myState = state.player2;
                enemyState = state.player1;
            }

            Character myCharacter = static_cast<Character>(myState.character);
            Character enemyCharacter = static_cast<Character>(enemyState.character);

            if (!fighter || fighter->getCharacter() != myCharacter) {
                fighter = std::make_unique<Fighter>(myCharacter);
            }

            if (!enemy || enemy->getCharacter() != enemyCharacter) {
                enemy = std::make_unique<Fighter>(enemyCharacter);
            }

            fighter->setPosition(myState.x, myState.y);
            fighter->setHealth(myState.hp);
            fighter->setFacingRight(myState.playerId == 0);
            fighter->setState(static_cast<FighterState>(myState.state));
            fighter->setHealthBarPosition(550.f, 785.f, false);


            enemy->setPosition(enemyState.x, enemyState.y);
            enemy->setHealth(enemyState.hp);
            enemy->setFacingRight(enemyState.playerId == 0);
            enemy->setState(static_cast<FighterState>(enemyState.state));
            enemy->setHealthBarPosition(970.f, 785.f, true);

            screen = GameScreen::Fight;
        }
    }
    if (fighter) {
        fighter->updateAnimation(animationDt);
    }
    if (enemy) {
        enemy->updateAnimation(animationDt);
    }

    if (screen != GameScreen::Fight) {
        return;
    }

    if (!fighter) {
        return;
    }

    InputPacket input;

    if (window.hasFocus()) {
        input.left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
        input.right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
        input.jump = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
        input.attack = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    } 
    else {
        input.left = false;
        input.right = false;
        input.jump = false;
        input.attack = false;
    }

    if (fighter) {
        HitBox hb = fighter->getHitbox();

        input.hitboxX = hb.x;
        input.hitboxY = hb.y;
        input.hitboxW = hb.width;
        input.hitboxH = hb.height;
    }

    networkClient.sendInput(input);
}

void Game::render() {
    window.clear();

    if (screen == GameScreen::MainMenu) {
        renderMainMenu();
    }
    else if (screen == GameScreen::MapSelect) {
        renderMapSelect();
    }
    else if (screen == GameScreen::CharacterSelect) {
        renderCharacterSelect();
    }
    else if (screen == GameScreen::Fight) {
        renderFight();
    }
    else if (screen == GameScreen::Win) {
        renderWin();
    }
    else if (screen == GameScreen::Lose) {
        renderLose();
    }

    window.display();
}

void Game::processEvent() {
     while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2f mousePos = window.mapPixelToCoords({
                mouse->position.x,
                mouse->position.y
            });

            if (screen == GameScreen::MainMenu) {
                if (startButton.getGlobalBounds().contains(mousePos)) {
                    screen = GameScreen::MapSelect;
                }
            }

            else if (screen == GameScreen::MapSelect) {
                if (!networkClient.hasId()) {
                    return;
                }

                if (networkClient.getPlayerId() != 0) {
                    return;
                }

                for (std::size_t i = 0; i < mapButtons.size(); i++) {
                    if (mapButtons[i].getGlobalBounds().contains(mousePos)) {
                        selectedMap = static_cast<int>(i);

                        stage.setBackground(mapPaths[selectedMap], window);

                        if (serverConnected && networkClient.isConnected()) {
                            networkClient.sendMap(selectedMap);
                        }

                        screen = GameScreen::CharacterSelect;
                    }
                }
            }

            if (screen == GameScreen::CharacterSelect) {

                if (orkButton.getGlobalBounds().contains(mousePos)) {
                    selectedCharacter = Character::Ork;

                    fighter = nullptr;
                    enemy = nullptr;

                    if (serverConnected && networkClient.isConnected()) {
                        networkClient.sendCharacter(static_cast<std::uint8_t>(selectedCharacter));
                    }
                }

                else if (ork2Button.getGlobalBounds().contains(mousePos)) {
                    selectedCharacter = Character::Ork2;
                    fighter = nullptr;
                    enemy = nullptr;

                    if (serverConnected && networkClient.isConnected()) {
                        networkClient.sendCharacter(static_cast<std::uint8_t>(selectedCharacter));
                    }
                }

                else if (ork3Button.getGlobalBounds().contains(mousePos)) {
                    selectedCharacter = Character::Ork3;
                    fighter = nullptr;
                    enemy = nullptr;

                    if (serverConnected && networkClient.isConnected()) {
                        networkClient.sendCharacter(static_cast<std::uint8_t>(selectedCharacter));
                    }
                }

                else if (ogreButton.getGlobalBounds().contains(mousePos)) {
                    selectedCharacter = Character::Ogre;
                    fighter = nullptr;
                    enemy = nullptr;

                    if (serverConnected && networkClient.isConnected()) {
                        networkClient.sendCharacter(static_cast<std::uint8_t>(selectedCharacter));
                    }
                }

                else if (devilButton.getGlobalBounds().contains(mousePos)) {
                    selectedCharacter = Character::Devil;
                    fighter = nullptr;
                    enemy = nullptr;

                    if (serverConnected && networkClient.isConnected()) {
                        networkClient.sendCharacter(static_cast<std::uint8_t>(selectedCharacter));
                    }
                }

                else if (devil2Button.getGlobalBounds().contains(mousePos)) {
                    selectedCharacter = Character::Devil2;
                    fighter = nullptr;
                    enemy = nullptr;

                    if (serverConnected && networkClient.isConnected()) {
                        networkClient.sendCharacter(static_cast<std::uint8_t>(selectedCharacter));
                    }
                }

                else if (trollButton.getGlobalBounds().contains(mousePos)) {
                    selectedCharacter = Character::Troll;
                    fighter = nullptr;
                    enemy = nullptr;

                    if (serverConnected && networkClient.isConnected()) {
                        networkClient.sendCharacter(static_cast<std::uint8_t>(selectedCharacter));
                    }
                }

                else if (zombieButton.getGlobalBounds().contains(mousePos)) {
                    selectedCharacter = Character::Zombie;
                    fighter = nullptr;
                    enemy = nullptr;

                    if (serverConnected && networkClient.isConnected()) {
                        networkClient.sendCharacter(static_cast<std::uint8_t>(selectedCharacter));
                    }
                }

                else if (zombie2Button.getGlobalBounds().contains(mousePos)) {
                    selectedCharacter = Character::ZombieKnight;
                    fighter = nullptr;
                    enemy = nullptr;

                    if (serverConnected && networkClient.isConnected()) {
                        networkClient.sendCharacter(static_cast<std::uint8_t>(selectedCharacter));
                    }
                }

                else if (marauderButton.getGlobalBounds().contains(mousePos)) {
                    selectedCharacter = Character::Marauder;
                    fighter = nullptr;
                    enemy = nullptr;

                    if (serverConnected && networkClient.isConnected()) {
                        networkClient.sendCharacter(static_cast<std::uint8_t>(selectedCharacter));
                    }
                }

                else if (goblinButton.getGlobalBounds().contains(mousePos)) {
                    selectedCharacter = Character::Goblin;
                    fighter = nullptr;
                    enemy = nullptr;

                    if (serverConnected && networkClient.isConnected()) {
                        networkClient.sendCharacter(static_cast<std::uint8_t>(selectedCharacter));
                    }
                }

                else if (gremlinButton.getGlobalBounds().contains(mousePos)) {
                    selectedCharacter = Character::Gremlin;
                    fighter = nullptr;
                    enemy = nullptr;

                    if (serverConnected && networkClient.isConnected()) {
                        networkClient.sendCharacter(static_cast<std::uint8_t>(selectedCharacter));
                    }
                }
            }
        }
    }
}

void Game::run() {
    while(window.isOpen()) {
        processEvent();
        update();
        render();
    }
}

void Game::renderMainMenu() {
    window.draw(menuBackground);
    window.draw(logoImage);
    window.draw(playButtonImage);
}

void Game::renderMapSelect() {
    window.draw(mapSelectBackground);
    for (auto& map : mapButtons) {
        window.draw(map);
    }
}

void Game::renderCharacterSelect() {
    window.draw(characterBackground);

    window.draw(orkButton);
    window.draw(ogreButton);
    window.draw(devilButton);
    window.draw(ork2Button);
    window.draw(ork3Button);
    window.draw(devil2Button);
    window.draw(zombieButton);
    window.draw(zombie2Button);
    window.draw(gremlinButton);
    window.draw(goblinButton);
    window.draw(trollButton);
    window.draw(marauderButton);
}

void Game::renderFight() {
    stage.render(window);

    if (fighter) {
        fighter->render(window);
        fighter->drawHealth(window);

    }

    if (enemy) {
        enemy->render(window);
        enemy->drawHealth(window);
    }
}

void Game::renderWin() {
    window.draw(winBackground);
}

void Game::renderLose() {
    window.draw(loseBackground);
}