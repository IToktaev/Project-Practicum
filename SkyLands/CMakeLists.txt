cmake_minimum_required(VERSION 3.16)

project(sfml-test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_PREFIX_PATH "C:/SFML")

find_package(SFML 3 CONFIG REQUIRED COMPONENTS Graphics Window System)
find_package(SFML 3 CONFIG REQUIRED COMPONENTS Graphics Window System Audio)

add_executable(app
    src/main.cpp
    src/Player/Player.cpp
    src/Game/Game.cpp
    src/Map/Map.cpp
    src/Displays/Level/Level.cpp
    src/Displays/Menu/Menu.cpp
    src/Displays/Home/Home.cpp
    src/Displays/LevelFinalScreen/LevelFinalScreen.cpp
    src/Utils/DrawImage.cpp
    src/Animator/Animator.cpp
    src/Sound/Sound.cpp
)

target_include_directories(app PRIVATE 
    src/Player
    src/Game
    src/Map
    src/Displays/Level
    src/Displays/Menu
    src/Displays/Home
    srs/Displays/LevelFinalScreen
    src/Utils
    src/GlobalConstants
    src/Animator
    src/Sound
)

target_link_libraries(app PRIVATE
    SFML::Graphics
    SFML::Audio
)