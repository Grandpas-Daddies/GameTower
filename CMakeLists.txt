cmake_minimum_required(VERSION 3.25)
project(GameTower1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(GameTower1
        FightScene.cpp
        FightScene.h
        init.h
        location.h
        main.cpp
        map.h
        Monster.cpp
        Monster.h Backpack.h Item.h)
