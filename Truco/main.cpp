#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <iterator>

#include "Card.h"
#include "Player.h"
#include "Team.h"

bool isAlreadySelected(int indexArr[], int arrSize, int targetIndex) {
    for (int i = 0; i < arrSize; i++) {
        if (indexArr[i] == targetIndex) {
            return true;
        }
    }
    
    return false;
}

int cardsOnTable[noTeams][membersPerTeam][cardsPerPlayer] = {
    {
        { -1, -1, -1 },
        { -1, -1, -1 },
    },
    {
        { -1, -1, -1 },
        { -1, -1, -1 }
    }
};
int currentOrder = 1;

void nextTurn(int &currentPlayerTurn, int &currentTeamTurn, int cardIndex) {
    
    cardsOnTable[currentTeamTurn][currentPlayerTurn][cardIndex] = 0;
    currentOrder += 1;
    
    if (currentPlayerTurn == 0 && currentTeamTurn == 0) {
        currentPlayerTurn = 1;
        currentTeamTurn = 1;
        return;
    }
    
    if (currentPlayerTurn == 1 && currentTeamTurn == 1) {
        currentPlayerTurn = 1;
        currentTeamTurn = 0;
        return;
    }
    
    if (currentPlayerTurn == 1 && currentTeamTurn == 0) {
        currentPlayerTurn = 0;
        currentTeamTurn = 1;
        return;
    }
    
    if (currentPlayerTurn == 0 && currentTeamTurn == 1) {
        currentPlayerTurn = 0;
        currentTeamTurn = 0;
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(2880, 1800), "Truco valendo o toba", sf::Style::Fullscreen);
    
    float screenWidth = sf::VideoMode::getDesktopMode().width;
    float screenHeight = sf::VideoMode::getDesktopMode().height;
    
    sf::Font font;
    font.loadFromFile("fonts/arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(fontSize);
    text.setFillColor(sf::Color::Red);
    
    srand((unsigned)time(NULL));
    
    // Generate Cards
    Card allCards[noAllCards] = {
        Card(1, Suit::Clubs, "cards/AC.png"), Card(1, Suit::Hearts, "cards/AH.png"), Card(1, Suit::Spades, "cards/AS.png"), Card(1, Suit::Diamonds, "cards/AD.png"),
        Card(2, Suit::Clubs, "cards/2C.png"), Card(2, Suit::Hearts, "cards/2H.png"), Card(2, Suit::Spades, "cards/2S.png"), Card(2, Suit::Diamonds, "cards/2D.png"),
        Card(3, Suit::Clubs, "cards/3C.png"), Card(3, Suit::Hearts, "cards/3H.png"), Card(3, Suit::Spades, "cards/3S.png"), Card(3, Suit::Diamonds, "cards/3D.png"),
        Card(4, Suit::Clubs, "cards/4C.png"), Card(4, Suit::Hearts, "cards/4H.png"), Card(4, Suit::Spades, "cards/4S.png"), Card(4, Suit::Diamonds, "cards/4D.png"),
        Card(5, Suit::Clubs, "cards/5C.png"), Card(5, Suit::Hearts, "cards/5H.png"), Card(5, Suit::Spades, "cards/5S.png"), Card(5, Suit::Diamonds, "cards/5D.png"),
        Card(6, Suit::Clubs, "cards/6C.png"), Card(6, Suit::Hearts, "cards/6H.png"), Card(6, Suit::Spades, "cards/6S.png"), Card(6, Suit::Diamonds, "cards/6D.png"),
        Card(7, Suit::Clubs, "cards/7C.png"), Card(7, Suit::Hearts, "cards/7H.png"), Card(7, Suit::Spades, "cards/7S.png"), Card(7, Suit::Diamonds, "cards/7D.png"),
        Card(11, Suit::Clubs, "cards/JC.png"), Card(11, Suit::Hearts, "cards/JH.png"), Card(11, Suit::Spades, "cards/JS.png"), Card(11, Suit::Diamonds, "cards/JD.png"),
        Card(12, Suit::Clubs, "cards/QC.png"), Card(12, Suit::Hearts, "cards/QH.png"), Card(12, Suit::Spades, "cards/QS.png"), Card(12, Suit::Diamonds, "cards/QD.png"),
        Card(13, Suit::Clubs, "cards/KC.png"), Card(13, Suit::Hearts, "cards/KH.png"), Card(13, Suit::Spades, "cards/KS.png"), Card(12, Suit::Diamonds, "cards/KD.png")
    };
    
    Team teams[noTeams] { Team("A Team", true), Team("B Team") };
    
    Player players[noTeams][membersPerTeam] {
        { Player("You", true), Player("Pedro") },
        { Player("Lucas"), Player("Osvaldo") }
    };
    
    std::shuffle(allCards, allCards + noAllCards, std::default_random_engine(0));
    
    int alreadySelectedCards[(noPlayers * cardsPerPlayer) + 1];
    int cardsCounter = 0;
    
    Card handCards[noTeams][membersPerTeam][cardsPerPlayer];
    
    sf::Texture opponentBackCardTexture;
    opponentBackCardTexture.loadFromFile("cards/yellow_back.png", CardRect);
    sf::Sprite opponentBackCardSprite;
    opponentBackCardSprite.setTexture(opponentBackCardTexture);
    opponentBackCardSprite.scale(cardWidthScale, cardHeightScale);
    
    sf::Texture partnerBackCardTexture;
    partnerBackCardTexture.loadFromFile("cards/red_back.png", CardRect);
    sf::Sprite partnerBackCardSprite;
    partnerBackCardSprite.setTexture(partnerBackCardTexture);
    partnerBackCardSprite.scale(cardWidthScale, cardHeightScale);
    
    for (int teamIndex = 0; teamIndex < noTeams; teamIndex++) {
        for (int pIndex = 0; pIndex < membersPerTeam; pIndex++) {
            // Cards Loop
            for (int cardIndex = 0; cardIndex < cardsPerPlayer; cardIndex++) {
                // Select unique card from cards
                int randCardIndex = rand() % noAllCards;
                while (isAlreadySelected(alreadySelectedCards, noPlayers * cardsPerPlayer, randCardIndex)) {
                    randCardIndex = rand() % noAllCards;
                }
                // Card Assign
                alreadySelectedCards[cardsCounter] = randCardIndex;
                handCards[teamIndex][pIndex][cardIndex] = allCards[randCardIndex];
                cardsCounter++;
                // Load Texture and sprite
                handCards[teamIndex][pIndex][cardIndex].texture.loadFromFile(handCards[teamIndex][pIndex][cardIndex].GetSourceDirectory(), CardRect);
                handCards[teamIndex][pIndex][cardIndex].sprite.setTexture(handCards[teamIndex][pIndex][cardIndex].texture);
                handCards[teamIndex][pIndex][cardIndex].sprite.scale(cardWidthScale, cardHeightScale);
            }
        }
    }

    // Under card
    int randCardIndex = rand() % noAllCards;
    while (isAlreadySelected(alreadySelectedCards, noPlayers * cardsPerPlayer, randCardIndex)) {
        randCardIndex = rand() % noAllCards;
    }
    // Under Card Assign
    alreadySelectedCards[cardsCounter] = randCardIndex;
    Card underCard = allCards[randCardIndex];
    underCard.texture.loadFromFile(underCard.GetSourceDirectory(), CardRect);
    underCard.sprite.setTexture(underCard.texture);
    underCard.sprite.scale(sf::Vector2f(cardWidthScale, cardHeightScale));
    underCard.sprite.setPosition(sf::Vector2f((screenWidth / 3) - (cardWidth * cardWidthScale / 2), (screenHeight / 2) - (cardHeight * cardHeightScale / 2)));
    underCard.sprite.setRotation(20);
    cardsCounter++;
    
    // Deck
    sf::Sprite deckSprite;
    deckSprite.setTexture(opponentBackCardTexture);
    deckSprite.scale(sf::Vector2f(cardWidthScale, cardHeightScale));
    deckSprite.setPosition(sf::Vector2f((screenWidth / 3) - (cardWidth * cardWidthScale / 2), (screenHeight / 2) - (cardHeight * cardHeightScale / 2)));
    deckSprite.setRotation(-20.f);
    
    // Rectangle
    sf::Vector2f rectangleSize = sf::Vector2f(screenWidth / 2, screenHeight / 3);
    sf::RectangleShape rectangle(rectangleSize);
    rectangle.setPosition(sf::Vector2f(screenWidth / 4, screenHeight / 3));
    
    // Logic
    int currentTeamTurn = 0;
    int currentPlayerTurn = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();
        }
        
        if (currentOrder > 5) {
            currentOrder = 1;
            for (int i = 0; i < noTeams; i++) {
                for (int j = 0; j < membersPerTeam; j++) {
                    for (int k = 0; k < cardsPerPlayer; k++) {
                        if (cardsOnTable[i][j][k] == 0) {
                            cardsOnTable[i][j][k] = 1;
                        }
                    }
                }
            }
            sf::sleep(sf::seconds(1.00f));
        }

        window.clear(sf::Color::Green);
        
        window.draw(rectangle);
        window.draw(underCard.sprite);
        window.draw(deckSprite);
        
        // Loop teams
        for (int currTeamIndex = 0; currTeamIndex < noTeams; currTeamIndex++) {
            Team currentTeam = teams[currTeamIndex];
            // Loop team members
            for (int currTeamPlayerIndex = 0; currTeamPlayerIndex < membersPerTeam; currTeamPlayerIndex++) {
                Player currentPlayer = players[currTeamIndex][currTeamPlayerIndex];
                std::string currentPlayerName = currentPlayer.GetName();
                // Loop team members cards
                for (int currHandCardIndex = 0; currHandCardIndex < cardsPerPlayer; currHandCardIndex++) {
                    Card& currentCard = handCards[currTeamIndex][currTeamPlayerIndex][currHandCardIndex];
                    
                    // Cards thrown, don't show anymore
                    if (cardsOnTable[currTeamIndex][currTeamPlayerIndex][currHandCardIndex] == 1) {
                        continue;
                    }
                    
                    switch (currTeamIndex) {
                        case playerTeamIndex: {
                            switch (currTeamPlayerIndex) {
                                case playerIndex: {
                                    text.setPosition(screenWidth / 2 + (cardWidth * cardWidthScale), screenHeight - (cardHeight * cardHeightScale));
                                    text.setString(currentPlayerName);
                                    window.draw(text);
                                    
                                    float defaultCardPosX = (screenWidth / 2) - (cardWidth * cardWidthScale / 2) * currHandCardIndex;
                                    float defaultCardPosY = screenHeight - (cardHeight * cardHeightScale);
                                    
                                    // Reset position if not selected anymore
                                    if (currentCard.GetState() == Unselected) {
                                        currentCard.sprite.setPosition(defaultCardPosX, defaultCardPosY);
                                    }
                                    
                                    if (currentCard.GetState() == Table) {
                                        if (cardsOnTable[currTeamPlayerIndex][currTeamPlayerIndex][currHandCardIndex] == 0) {
                                            window.draw(currentCard.sprite);
                                        }
                                    }
                                    
                                    // Drag card
                                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentCard.GetState() != Table)
                                    {
                                        sf::Vector2i clickPosition = sf::Mouse::getPosition(window);
                                        // If showing only half card, make just half card selectable
                                        float originPos = (currHandCardIndex < cardsPerPlayer - 1 && handCards[currTeamIndex][currTeamPlayerIndex][currHandCardIndex + 1].GetState() == Table) || currHandCardIndex == cardsPerPlayer - 1 ? currentCard.sprite.getPosition().x : currentCard.sprite.getPosition().x + (cardWidth * cardWidthScale / 2);
                                        // Cards collision (user click)
                                        if (clickPosition.x >= originPos && clickPosition.x <= currentCard.sprite.getPosition().x + (cardWidth * cardWidthScale) &&
                                            clickPosition.y >= currentCard.sprite.getPosition().y && clickPosition.y <= currentCard.sprite.getPosition().y + cardHeight * cardHeightScale) {
                                            bool hasCardSelectedAlready = false;
                                            for (int selectedCardsIndex = 0; selectedCardsIndex < cardsPerPlayer; selectedCardsIndex++) {
                                                if (handCards[currTeamIndex][currTeamPlayerIndex][selectedCardsIndex].GetState() == Selected) {
                                                    hasCardSelectedAlready = true;
                                                }
                                            }
                                            // If has any card selected, cannot select more than one
                                            if (!hasCardSelectedAlready) {
                                                currentCard.SetState(Selected);
                                            }
                                        }
                                        // Current selected card
                                        if (currentCard.GetState() == Selected) {
                                            float posX = clickPosition.x - (cardWidth * cardWidthScale / 2);
                                            float posY = clickPosition.y - (cardHeight * cardHeightScale / 2);
                                            currentCard.sprite.setPosition(posX, posY);
                                            window.draw(currentCard.sprite);
                                            break;
                                        }
                                    }
                                    // If dropped inside area
                                    if (currentCard.sprite.getPosition().x >= rectangle.getPosition().x && currentCard.sprite.getPosition().x + (cardWidth * cardWidthScale) <= rectangle.getPosition().x + rectangleSize.x && currentCard.sprite.getPosition().y >= rectangle.getPosition().y && currentCard.sprite.getPosition().y + (cardWidth * cardWidthScale) <= rectangle.getPosition().y + rectangleSize.y) {
                                        if (currentCard.GetState() != Table) {
                                            currentCard.SetState(Table);
                                            nextTurn(currentPlayerTurn, currentTeamTurn, currHandCardIndex);
                                        }
                                        break;
                                    }
                                    
                                    // If not selected, set unselected
                                    currentCard.SetState(Unselected);
                                    window.draw(currentCard.sprite);
                                    break;
                                }
                                case partnerIndex: {
                                    float cardY = 0;
                                    text.setPosition((screenWidth / 2) - (cardWidth * cardWidthScale * 2), (cardHeight * cardHeightScale) - fontSize);
                                    text.setString(currentPlayerName);
                                    window.draw(text);
                                    
                                    if (currentCard.GetState() != Table) {
                                        float cardX = (screenWidth / 2) - (cardWidth * cardWidthScale / 2) * currHandCardIndex;
                                        partnerBackCardSprite.setPosition(cardX, cardY);
                                        window.draw(partnerBackCardSprite);
                                        break;
                                    }

                                    // If partner card is on table
                                    float cardX = (screenWidth / 2) - (cardWidth * cardWidthScale / 2) + (currentOrder * 2);
                                    cardY = (screenHeight / 2) - (cardHeight * cardHeightScale / 2);
                                    currentCard.sprite.setPosition(cardX, cardY);
                                    window.draw(currentCard.sprite);
                                    break;
                                }
                            }
                            break;
                        }
                        case rivalTeamIndex: {
                            switch (currTeamPlayerIndex) {
                                case rightSideRivalIndex:
                                case leftSideRivalIndex: {
                                    float textX = currTeamPlayerIndex == 0 ? screenWidth - (cardHeight * cardHeightScale) : cardHeight * cardHeightScale / 2;
                                    float textY = currTeamPlayerIndex == 0 ? (screenHeight / 2) - (cardWidth * cardWidthScale) - fontSize : (screenHeight / 2) + (cardWidth * cardWidthScale);
                                    text.setPosition(textX, textY);
                                    text.setString(currentPlayerName);
                                    window.draw(text);
                                    if (currentCard.GetState() != Table) {
                                        float cardX = currTeamPlayerIndex == 0 ? screenWidth - (cardHeight * cardHeightScale) : 0;
                                        float cardY = ((screenHeight / 2) - (cardWidth * cardWidthScale / 2) * currHandCardIndex) + 360.f;
                                        opponentBackCardSprite.setPosition(cardX, cardY);
                                        opponentBackCardSprite.setRotation(-90.f);
                                        window.draw(opponentBackCardSprite);
                                        break;
                                    }

                                    float cardX = (screenWidth / 2) - (cardWidth * cardWidthScale / 2) + (currentOrder * 2);
                                    float cardY = (screenHeight / 2) - (cardHeight * cardHeightScale / 2);
                                    currentCard.sprite.setPosition(cardX, cardY);
                                    window.draw(currentCard.sprite);
                                    break;
                                }
                            }
                        }
                    };
                }
            }
        }
        
        if (!players[currentTeamTurn][currentPlayerTurn].IsPlayer()) {
            // TODO: Logic
            for (int handCardIndex = 0; handCardIndex < cardsPerPlayer; handCardIndex++) {
                Card& currentCard = handCards[currentTeamTurn][currentPlayerTurn][handCardIndex];
                if (currentCard.GetState() != Table) {
                    currentCard.SetState(Table);
                    nextTurn(currentPlayerTurn, currentTeamTurn, handCardIndex);
                    break;
                }
            }
        }
        
        window.display();
    }

    return 0;
}
