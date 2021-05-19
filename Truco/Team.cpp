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

Team::Team (std::string name, bool isPlayerTeam) {
    this->name = name;
    this->isPlayerTeam = isPlayerTeam;
}

std::string Team::GetName() {
    return name;
}

bool Team::IsPlayerTeam() {
    return isPlayerTeam;
}
