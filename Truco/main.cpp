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
    sf::Vector2f rectanglePosition = sf::Vector2f(720.f, 450.f);
    sf::RectangleShape rectangle(rectanglePosition);
    rectangle.setPosition((sf::VideoMode::getDesktopMode().width / 2) - rectanglePosition.x / 2, (sf::VideoMode::getDesktopMode().height / 2) - rectanglePosition.y / 2);
    rectangle.setFillColor(sf::Color(255, 0, 0));
    window->draw(rectangle);
    
    // Loop teams
    for (int currTeamIndex = 0; currTeamIndex < noTeams; currTeamIndex++) {
        Team currentTeam = teams[currTeamIndex];
        // Loop team members
        for (int currTeamPlayerIndex = 0; currTeamPlayerIndex < membersPerTeam; currTeamPlayerIndex++) {
                Player currentPlayer = currentTeam.GetPlayer(currTeamPlayerIndex);
                // Loop team members cards
                for (int currHandCardIndex = 0; currHandCardIndex < cardsPerPlayer; currHandCardIndex++) {
                    Card currentCard = currentPlayer.GetCard(currHandCardIndex);

                    sf::Texture texture;
                    texture.setSmooth(true);
                    sf::Sprite sprite;
                    sprite.scale(sf::Vector2f(0.5f, 0.5f));
                    sf::IntRect rect = sf::IntRect(0, 0, cardWidth, cardHeight);
                    if (currentTeam.IsPlayerTeam()) {
                        float cardY = 0;
                        if (currentPlayer.IsPlayer()) {
                            texture.loadFromFile(currentCard.GetSourceDirectory(), rect);
                            sprite.setTexture(texture);
                            
                            float cardX = (sf::VideoMode::getDesktopMode().width / 2) - (cardWidth * 0.5f / 2) * currHandCardIndex;
                            cardY = sf::VideoMode::getDesktopMode().height - (cardHeight * 0.5f);
                            sf::Vector2f cardPosition = sf::Vector2f(cardX, cardY);
                            sprite.setPosition(cardPosition);
                            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                            {
                                sf::Vector2i clickPosition = sf::Mouse::getPosition(*window);
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
                                    sprite.setPosition(sf::Vector2f(posX, posY));
                                    window->draw(sprite);
                                    continue;
                                }
                            }
                            
                            // If not selected, set unselected
                            cardSelected[currHandCardIndex] = -1;;
                            window->draw(sprite);
                            continue;
                        }
                        
                        // If member is same team, show cards with red back
                        texture.loadFromFile("cards/red_back.png", rect);
                        sprite.setTexture(texture);
                        
                        float cardX = (sf::VideoMode::getDesktopMode().width / 2) - (cardWidth * 0.5f / 2) * currHandCardIndex;
                        sprite.setPosition(sf::Vector2f(cardX, cardY));
                        window->draw(sprite);
                        continue;
                    }
                    
                    // If not same team
                    texture.loadFromFile("cards/yellow_back.png", rect);
                    sprite.setTexture(texture);
                    
                    float cardX = currTeamPlayerIndex == 0 ? sf::VideoMode::getDesktopMode().width - (cardHeight * 0.5f) : 0;
                    float cardY = ((sf::VideoMode::getDesktopMode().height / 2) - (cardWidth * 0.5f / 2) * currHandCardIndex) + 360.f;
                    sprite.setPosition(sf::Vector2f(cardX, cardY));
                    sprite.setRotation(-90.f);
                    window->draw(sprite);
                }
        }
    }
    window->display();
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
    
    std::string playerNames[noPlayers] = { "Pedro", "Lucas", "Osvaldo", playerName };
    std::string teamNames[noTeams] = { "A Team", "B Team" };
    int alreadySelectedCards[noPlayers * cardsPerPlayer];
    int alreadySelectedPlayers[noTeams * membersPerTeam] = {-1, -1, -1, -1};
    int playersCount = 0;
    int cardsCounter = 0;
    // Teams Loop
    Team teams[noTeams];
    for (int teamIndex = 0; teamIndex < noTeams; teamIndex++) {
        // Players Loop
        Player players[noTeams][membersPerTeam];
        bool isPlayerTeam = false;
        for (int playerIndex = 0; playerIndex < membersPerTeam; playerIndex++) {
            // Cards Loop
            Card handCards[cardsPerPlayer];
            for (int cardIndex = 0; cardIndex < cardsPerPlayer; cardIndex++) {
                // Select unique card from cards
                int randIndex = rand() % noAllCards;
                while (isAlreadySelected(alreadySelectedCards, noPlayers * cardsPerPlayer, randIndex)) {
                    randIndex = rand() % noAllCards;
                }
                
                // Card Assign
                alreadySelectedCards[cardsCounter] = randIndex;
                handCards[cardIndex] = allCards[randIndex];
                cardsCounter++;
            }
            
            // Select unique user from users
            int randIndex = rand() % noPlayers;
            while (isAlreadySelected(alreadySelectedPlayers, noPlayers, randIndex)) {
                randIndex = rand() % noPlayers;
            }
            
            // Player Assign
            alreadySelectedPlayers[playersCount] = randIndex;
            players[teamIndex][playerIndex] = Player(playerNames[randIndex], handCards, playerNames[randIndex] == playerName);;
            if (!isPlayerTeam) {
                isPlayerTeam = players[teamIndex][randIndex].IsPlayer();
            }
            playersCount++;
        }
        teams[teamIndex] = Team(teamNames[teamIndex], players[teamIndex], isPlayerTeam);
    }

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
        
        showContents(&window, teams);
    }

    return 0;
}
