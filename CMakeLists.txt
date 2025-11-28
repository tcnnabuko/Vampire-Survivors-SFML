cmake_minimum_required(VERSION 3.10)
project(VampireSFML)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(VampireSFML
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Bullet.cpp
    src/XP.cpp
)

target_link_libraries(VampireSFML sfml-graphics sfml-window sfml-system)
