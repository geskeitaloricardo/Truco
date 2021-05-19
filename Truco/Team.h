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
    bool isPlayerTeam = false;
public:
    Team();
    Team (std::string name, bool isPlayerTeam = false);
    std::string GetName();
    bool IsPlayerTeam();
};

#endif /* Team_h */
