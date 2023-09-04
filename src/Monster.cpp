//
// Created by hang on 2023-09-04.
//

#include "Monster.h"
#include "Player.h"
#include "Hero.h"

Monster createMonster(int hp, int damage, std::string description) {
//    std::vector<Word> wordList = Player.deliverWord();

    Monster monster(hp, damage, wordList, description);

    return monster;
}

std::vector<std::string> descriptions = readMonsterDes("../Assets/.monsterDes");

Monster KargusDraco = createMonster(100, 10, descriptions[0]);
Monster Adra1 = createMonster(120, 15, descriptions[1]);
Monster Helms = createMonster(150, 20, descriptions[2]);
Monster DarkKnight = createMonster(180, 30, descriptions[3]);
Monster Adra2 = createMonster(200, 50, descriptions[4]);

