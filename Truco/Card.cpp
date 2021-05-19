//
//  Card.cpp
//  Polygons
//
//  Created by Italo Ricardo Geske on 2021/05/16.
//  Copyright © 2021 Italo Ricardo Geske. All rights reserved.
//

#include <string>
#include <iostream>
#include "Card.h"

Card::Card() {
    number = 0;
    suit = Suit::Unknown;
    state = State::Still;
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

State Card::GetState() {
    return state;
}

void Card::SetState(State state) {
    this->state = state;
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
