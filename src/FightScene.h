//
// Created by xiao on 2023-08-21.
//

#ifndef GAMETOWER1_FIGHT_SCENE_H
#define GAMETOWER1_FIGHT_SCENE_H
#include "Monster.h"
#include "Hero.h"

class fightScene {
public:
    fightScene();
    void show();//不停清屏展示新内容
    void drop();//掉字符
    void fight();//效果计算等
private:
    Monster mon;//本关所面对的怪物
    std::string scene[10];
    Hero hero;

};


#endif //GAMETOWER1_FIGHT_SCENE_H
