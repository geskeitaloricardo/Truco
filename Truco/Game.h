//
//  Game.h
//  Polygons
//
//  Created by Italo Ricardo Geske on 2021/05/16.
//  Copyright © 2021 Italo Ricardo Geske. All rights reserved.
//

#include <SFML/Graphics.hpp>

#ifndef Game_h
#define Game_h

#define noPlayers 4
#define cardsPerPlayer 3
#define noAllCards 40

#define cardWidth 691
#define cardHeight 1056
#define cardWidthScale 0.5f
#define cardHeightScale 0.5f

#define totalPlayers 4
#define membersPerTeam 2
#define noTeams 2

#define fontSize 70

#define playerTeamIndex 0
#define rivalTeamIndex 1
#define playerIndex 0
#define partnerIndex 1
#define rightSideRivalIndex 0
#define leftSideRivalIndex 1

#define playerName "You"

extern sf::IntRect CardRect;

#endif /* Game_h */
