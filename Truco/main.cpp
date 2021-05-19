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

int cardSelected[cardsPerPlayer] = {-1, -1, -1};

bool isAlreadySelected(int indexArr[], int arrSize, int targetIndex) {
    for (int i = 0; i < arrSize; i++) {
        if (indexArr[i] == targetIndex) {
            return true;
        }
    }
    
    return false;
}

void showContents(sf::RenderWindow* window, Team teams[]) {
    
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(2880, 1800), "Truco valendo o toba", sf::Style::Fullscreen);
    
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
    
    
    std::shuffle(allCards, allCards + noAllCards, std::default_random_engine(0));
    
    float screenWidth = sf::VideoMode::getDesktopMode().width;
    float screenHeight = sf::VideoMode::getDesktopMode().height;
    
    std::string playerNames[noPlayers] = { "Pedro", "Lucas", "Osvaldo", playerName };
    std::string teamNames[noTeams] = { "A Team", "B Team" };
    int alreadySelectedCards[noPlayers * cardsPerPlayer];
    int alreadySelectedPlayers[noTeams * membersPerTeam] = {-1, -1, -1, -1};
    int playersCount = 0;
    int cardsCounter = 0;
    // Teams Loop
    Team teams[noTeams];
    Player players[noTeams][membersPerTeam];
    Card handCards[noTeams][membersPerTeam][cardsPerPlayer];
    
    sf::Texture opponentBackCardTexture;
    opponentBackCardTexture.loadFromFile("cards/yellow_back.png", CardRect);
    opponentBackCardTexture.setSmooth(true);
    
    sf::Texture partnerBackCardTexture;
    partnerBackCardTexture.loadFromFile("cards/red_back.png", CardRect);
    partnerBackCardTexture.setSmooth(true);
    
    for (int teamIndex = 0; teamIndex < noTeams; teamIndex++) {
        // Players Loop
        bool isPlayerTeam = false;
        for (int playerIndex = 0; playerIndex < membersPerTeam; playerIndex++) {
            // Select unique user from users
            int randPlayerIndex = rand() % noPlayers;
            while (isAlreadySelected(alreadySelectedPlayers, noPlayers, randPlayerIndex)) {
                randPlayerIndex = rand() % noPlayers;
            }
            // Player Assign
            alreadySelectedPlayers[playersCount] = randPlayerIndex;
            players[teamIndex][playerIndex] = Player(playerNames[randPlayerIndex], playerNames[randPlayerIndex] == playerName);
            playersCount++;
            
            // Cards Loop
            for (int cardIndex = 0; cardIndex < cardsPerPlayer; cardIndex++) {
                // Select unique card from cards
                int randCardIndex = rand() % noAllCards;
                while (isAlreadySelected(alreadySelectedCards, noPlayers * cardsPerPlayer, randCardIndex)) {
                    randCardIndex = rand() % noAllCards;
                }
                // Card Assign
                alreadySelectedCards[cardsCounter] = randCardIndex;
                handCards[teamIndex][playerIndex][cardIndex] = allCards[randCardIndex];
                // Load Texture and sprite
                handCards[teamIndex][playerIndex][cardIndex].texture.loadFromFile(handCards[teamIndex][playerIndex][cardIndex].GetSourceDirectory(), CardRect);
                bool isPlayer = players[teamIndex][playerIndex].IsPlayer();
                if (isPlayer) {
                    isPlayerTeam = true;
                    handCards[teamIndex][playerIndex][cardIndex].sprite.setTexture(handCards[teamIndex][playerIndex][cardIndex].texture);
                    if (playerIndex == 1) {
                        // Partner card back has to be red
                        handCards[teamIndex][0][cardIndex].sprite.setTexture(partnerBackCardTexture);
                    }
                } else {
                    if (isPlayerTeam) {
                        handCards[teamIndex][playerIndex][cardIndex].sprite.setTexture(partnerBackCardTexture);
                    } else {
                        handCards[teamIndex][playerIndex][cardIndex].sprite.setTexture(opponentBackCardTexture);
                    }
                }
                handCards[teamIndex][playerIndex][cardIndex].sprite.scale(sf::Vector2f(cardWidthScale, cardHeightScale));
                cardsCounter++;
            }
        }
        teams[teamIndex] = Team(teamNames[teamIndex], isPlayerTeam);
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
    sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));
    rectangle.setSize(sf::Vector2f(screenWidth / 2, screenHeight / 3));
    rectangle.setPosition(screenWidth / 4, screenHeight / 3);

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

        window.clear(sf::Color::Green);
        
        window.draw(rectangle);
        window.draw(underCard.sprite);
        window.draw(deckSprite);
        
        // Loop teams
        for (int currTeamIndex = 0; currTeamIndex < noTeams; currTeamIndex++) {
            Team currentTeam = teams[currTeamIndex];
            // Loop team members
            for (int currTeamPlayerIndex = 0; currTeamPlayerIndex < membersPerTeam; ++currTeamPlayerIndex) {
                    Player currentPlayer = players[currTeamIndex][currTeamPlayerIndex];
                    // Loop team members cards
                    for (int currHandCardIndex = 0; currHandCardIndex < cardsPerPlayer; currHandCardIndex++) {
                        Card currentCard = handCards[currTeamIndex][currTeamPlayerIndex][currHandCardIndex];
                        
                        if (currentTeam.IsPlayerTeam()) {
                            float cardY = 0;
                            
                            if (currentPlayer.IsPlayer()) {
                                float cardX = (screenWidth / 2) - (cardWidth * cardWidthScale / 2) * currHandCardIndex;
                                float cardY = screenHeight - (cardHeight * cardHeightScale);
                                sf::Vector2f cardPosition = sf::Vector2f(cardX, cardY);
                                currentCard.sprite.setPosition(cardPosition.x, cardPosition.y);
                                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                                {
                                    sf::Vector2i clickPosition = sf::Mouse::getPosition(window);
                                    float originPos = currHandCardIndex == 2 ? cardPosition.x : cardPosition.x + (cardWidth * 0.5f / 2);
                                    // Cards collision (user click)
                                    if (clickPosition.x >= originPos && clickPosition.x <= cardPosition.x + (cardWidth * 0.5f) &&
                                        clickPosition.y >= cardPosition.y && clickPosition.y <= cardPosition.y + cardHeight * 0.5f) {
                                        bool hasCardSelectedAlready = false;
                                        for (int selectedCardsIndex = 0; selectedCardsIndex < cardsPerPlayer; selectedCardsIndex++) {
                                            if (cardSelected[selectedCardsIndex] != -1) {
                                                hasCardSelectedAlready = true;
                                            }
                                        }
                                        // If has any card selected, cannot select more than one
                                        if (!hasCardSelectedAlready) {
                                            cardSelected[currHandCardIndex] = currHandCardIndex;
                                        }
                                    }
                                    // Current selected card
                                    if (cardSelected[currHandCardIndex] != -1) {
                                        float posX = clickPosition.x - (cardWidth * 0.5f / 2);
                                        float posY = clickPosition.y - (cardHeight * 0.5f / 2);
                                        currentCard.sprite.setPosition(sf::Vector2f(posX, posY));
                                        window.draw(currentCard.sprite);
                                        continue;
                                    }
                                }
                                // If not selected, set unselected
                                cardSelected[currHandCardIndex] = -1;;
                                window.draw(currentCard.sprite);
                                continue;
                            }
                            // If member is same team, show cards with red back
                            float cardX = (screenWidth / 2) - (cardWidth * cardWidthScale / 2) * currHandCardIndex;
                            currentCard.sprite.setPosition(sf::Vector2f(cardX, cardY));
                            window.draw(currentCard.sprite);
                            continue;
                        }
                        // If not same team
                        float cardX = currTeamPlayerIndex == 0 ? screenWidth - (cardHeight * cardHeightScale) : 0;
                        float cardY = ((screenHeight / 2) - (cardWidth * cardWidthScale / 2) * currHandCardIndex) + 360.f;
                        currentCard.sprite.setPosition(sf::Vector2f(cardX, cardY));
                        currentCard.sprite.setRotation(-90.f);
                        window.draw(currentCard.sprite);
                    }
            }
        }
        window.display();
    }

    return 0;
}
