//
//  Team.h
//  Polygons
//
//  Created by Italo Ricardo Geske on 2021/05/16.
//  Copyright © 2021 Italo Ricardo Geske. All rights reserved.
//

#ifndef Team_h
#define Team_h

#include "Player.h"

class Team
{
private:
    std::string name;
    Player players[membersPerTeam];
    bool isPlayerTeam = false;
public:
    Team();
    Team (std::string name, Player players[], bool isPlayerTeam = false);
    std::string GetName();
    Player GetPlayer(int index);
    bool IsPlayerTeam();
};

#endif /* Team_h */
