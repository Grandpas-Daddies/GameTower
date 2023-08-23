cmake_minimum_required(VERSION 3.25)
project(GameTower)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(GameTower
        src/FightScene.cpp
        src/FightScene.h
        src/Location.h
        src/Main.cpp
        src/Map.h
        src/Monster.cpp
        src/Monster.h src/Backpack.h src/Item.h
        src/Item.cpp
        src/Backpack.cpp
        src/Hero.cpp
        src/Word.cpp
        src/Interface.h
        src/Interface.h
        src/Init.h
)
