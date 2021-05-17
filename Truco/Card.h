//
//  Card.h
//  Polygons
//
//  Created by Italo Ricardo Geske on 2021/05/16.
//  Copyright © 2021 Italo Ricardo Geske. All rights reserved.
//

#ifndef Card_h
#define Card_h

#include <SFML/Graphics.hpp>

enum Suit
{
    Unknown = 0,
    Spades = 1,
    Hearts = 2,
    Diamonds = 3,
    Clubs = 4
};

class Card
{
private:
    int number;
    Suit suit;
    std::string sourceDirectory;
    sf::Vector2f coordinates;
public:
    Card();
    Card(int number, Suit suit, std::string sourceDirectory);
    int GetNumber();
    Suit GetSuit();
    std::string GetSuitString();
    std::string GetSourceDirectory();
    sf::Vector2f GetCoordinates();
    void SetCoordinates(sf::Vector2f coordinates);
};


#endif /* Card_h */
