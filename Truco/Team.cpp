//
//  Team.cpp
//  Polygons
//
//  Created by Italo Ricardo Geske on 2021/05/16.
//  Copyright © 2021 Italo Ricardo Geske. All rights reserved.
//

#include <stdio.h>
#include <string>

#include "Team.h"
#include "Player.h"

Team::Team() {
    name = "";
}

Team::Team (std::string name, Player players[], bool isPlayerTeam) {
    this->name = name;
    for (int i = 0; i < membersPerTeam; i++) {
        this->players[i] = players[i];
    }
    this->isPlayerTeam = isPlayerTeam;
}

std::string Team::GetName() {
    return name;
}

Player Team::GetPlayer(int index) {
    return players[index];
}

bool Team::IsPlayerTeam() {
    return isPlayerTeam;
}
