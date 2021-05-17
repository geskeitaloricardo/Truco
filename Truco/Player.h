//
//  Player.h
//  Polygons
//
//  Created by Italo Ricardo Geske on 2021/05/16.
//  Copyright © 2021 Italo Ricardo Geske. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <string>

#include "Card.h"
#include "Game.h"

class Player
{
private:
    std::string name;
    Card cards[cardsPerPlayer];
    bool isPlayer = false;
public:
    Player();
    Player (std::string name, Card cards[], bool isPlayer = false);
    Card GetCard(int index);
    std::string GetName();
    bool IsPlayer();
};


#endif /* Player_h */
