find_package(SFML 3.0.2 COMPONENTS
    Graphics
    Window
    System
    Network
    REQUIRED
)

add_executable(Client
    src/Fighter.cpp
    src/Game.cpp
    src/Main.cpp
    src/TextureManager.cpp
    src/Animation.cpp
    src/Animator.cpp
    src/Stage.cpp
    src/NetworkClient.cpp
)

target_include_directories(Client  
    PRIVATE
    include
    ,,/Shared/include
)

target_link_libraries(Client 
    PRIVATE
    Shared
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Network
)

target_compile_options(Client PRIVATE 
    -Wall
    -Wextra
    -Wpedantic
)