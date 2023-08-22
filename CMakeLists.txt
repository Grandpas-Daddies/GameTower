cmake_minimum_required(VERSION 3.25)
project(GameTower)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(GameTower
        FightScene.cpp
        FightScene.h
        init.h
        location.h
        main.cpp
        map.h
        Monster.cpp
        Monster.h Backpack.h Item.h
        Item.cpp
        Backpack.cpp
        Hero.cpp
        Word.cpp
)
