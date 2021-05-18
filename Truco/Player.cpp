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

Card Player::GetCard(int index) {
//      TODO: 実際に外したいな
    return cards[index];
}

void Player::SetCards(Card cards[]) {
    for (int i = 0; i < cardsPerPlayer; i++) {
        this->cards[i] = cards[i];
    }
}

std::string Player::GetName() {
    return name;
}

bool Player::IsPlayer() {
    return isPlayer;
}
