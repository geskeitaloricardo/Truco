//
//  Player.cpp
//  Polygons
//
//  Created by Italo Ricardo Geske on 2021/05/16.
//  Copyright © 2021 Italo Ricardo Geske. All rights reserved.
//

#include <stdio.h>

#include "Player.h"

Player::Player() {
    name = "";
}

Player::Player (std::string name, bool isPlayer) {
    this->name = name;
    this->isPlayer = isPlayer;
}

std::string Player::GetName() {
    return name;
}

bool Player::IsPlayer() {
    return isPlayer;
}
