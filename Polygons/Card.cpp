//
//  Card.cpp
//  Polygons
//
//  Created by Italo Ricardo Geske on 2021/05/16.
//  Copyright © 2021 Italo Ricardo Geske. All rights reserved.
//

#include <string>

#include "Card.h"

Card::Card() {
    number = 0;
    suit = Suit::Unknown;
    sourceDirectory = "";
};

Card::Card(int number, Suit suit, std::string sourceDirectory) {
    this->number = number;
    this->suit = suit;
    this->sourceDirectory = sourceDirectory;
}

int Card::GetNumber() {
    return number;
}

Suit Card::GetSuit() {
    return suit;
}

std::string Card::GetSuitString() {
    switch (suit) {
        case Unknown:
            return "Unknown";
        case Spades:
            return "Spades";
        case Hearts:
            return "Hearts";
        case Diamonds:
            return "Diamonds";
        case Clubs:
            return "Clubs";
    }
}

std::string Card::GetSourceDirectory() {
    return sourceDirectory;
}

sf::Vector2f Card::GetCoordinates() {
    return coordinates;
}

void Card::SetCoordinates(sf::Vector2f coordinates) {
    this->coordinates = coordinates;
}
