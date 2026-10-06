cmake_minimum_required(VERSION 3.16)

project(sfml-test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_PREFIX_PATH "C:/SFML")

find_package(SFML 3 CONFIG REQUIRED COMPONENTS Graphics Window System)

add_executable(app
    src/main.cpp
    src/Player/Player.cpp
    src/Game/Game.cpp
)

target_include_directories(app PRIVATE 
    src/Player
    src/Game
)

target_link_libraries(app PRIVATE
    SFML::Graphics
)