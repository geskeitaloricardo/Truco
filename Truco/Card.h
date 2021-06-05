//
//  Card.h
//  Polygons
//
//  Created by Italo Ricardo Geske on 2021/05/16.
//  Copyright © 2021 Italo Ricardo Geske. All rights reserved.
//

#include "Game.h"

#ifndef Card_h
#define Card_h

enum Suit
{
    Unknown = 0,
    Spades = 1,
    Hearts = 2,
    Diamonds = 3,
    Clubs = 4
};

enum State
{
    Still,
    Unselected,
    Selected,
    Table,
    Gone
};

class Card
{
private:
    int number;
    Suit suit;
    State state;
    std::string sourceDirectory;
public:
    sf::Sprite sprite;
    sf::Texture texture;
    
    Card();
    Card(int number, Suit suit, std::string sourceDirectory);
    int GetNumber();
    Suit GetSuit();
    State GetState();
    void SetState(State state);
    std::string GetSuitString();
    std::string GetSourceDirectory();
    void LoadGraphics();
    void LoadGraphics(std::string sourceDirectory);
};


#endif /* Card_h */
