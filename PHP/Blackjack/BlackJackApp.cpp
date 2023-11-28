/**
 * BlackjackApp.h
*/
#include "BlackJackApp.h"
#include <climits>

// Runs the BlackJack app
void BlackJackApp::run()
{
    resetPlayerOptions();
    playerOptions[0] = "[a]Stand"; 
    playerOptions[1] = "[b]Hit";
    playerOptions[2] = "[c]DoubleDown";
    playerOptions[3] = "[d]Split";

    cardVals["2"] = 2;
    cardVals["3"] = 3;
    cardVals["4"] = 4;
    cardVals["5"] = 5;
    cardVals["6"] = 6;
    cardVals["7"] = 7;
    cardVals["8"] = 8;
    cardVals["9"] = 9;
    cardVals["10"] = 10;
    cardVals["J"] = 10;
    cardVals["K"] = 10;
    cardVals["Q"] = 10;
    cardVals["A"] = 11;

    std::cout << "----\nWelcome to Blackjack!\n----\n";

    std::string keepPlaying;
    do
    {
        playRound();
        std::cout << "Play again? [Y]";
        std::cin >> keepPlaying;
    } 
    while (keepPlaying.compare("Y") == 0);

    std::cout << "Thanks for playing! Bye!\n";
}

// Plays a new game of BlackJack with the user
void BlackJackApp::playRound()
{
    // Since a player can have multiple hands of cards through splitting,
    // we will store their hands in a vector.
	// The dealer can only have one hand of cards.
    std::vector<Hand> playerHands;
    Hand dealerHand;

    deck.shuffle();

    Hand playerHand;
    deal(2, playerHand);
    deal(2, dealerHand);

    std::cout << "How much do you want to bet? Enter a number:\n";
	std::cin >> playerHand.bet;

	while (!std::cin.good())
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Invalid bet. Please enter a number:\n";
		std::cin >> playerHand.bet;
	}

    playerHands.push_back(playerHand);

    printAllHands(playerHands, dealerHand);

    for(unsigned int i = 0; i < playerHands.size(); i++)
    {
        int handVal = 0;
		bool handStand = false;

        resetPlayerOptions();

        // If the player has already split, or if the hand cards
        // don't match rank, then remove the split option
        if(i > 0)
        {
            optionsValid[3] = false;
        }
        else if(i == 0 && playerHands[i].cards.size() == 2)
        {
            std::string firstCardRank = playerHands[i].cards[0].rank;
            std::string secondCardRank = playerHands[i].cards[1].rank;
            if(firstCardRank.compare(secondCardRank) != 0)
            {
                optionsValid[3] = false;
            }
        }

		// loop the player options
		while (handVal < blackJackVal && !handStand && !deck.endOfStack())
        {
            std::cout << "What do you want to do with hand #" << i + 1 << "?\n";
            printPlayerOptions();

            std::string choice;
            std::cin >> choice;

            // stand
            if(choice.compare("a") == 0 && optionsValid[0])
            {
				std::cout << "-> You've chosen to stand!\n\n";
				handStand = true;
            }
            // hit
            else if (choice.compare("b") == 0 && optionsValid[1])
            {
				std::cout << "-> You've chosen to hit! New card dealt!\n\n";
                hit(playerHands[i]); 
            }
			// double down
			else if (choice.compare("c") == 0 && optionsValid[2])
			{
				std::cout << "-> You've chosen to double down! New card dealt and bet has doubled! \n\n";
				doubleDown(playerHands[i]);
				optionsValid[1] = false;
				optionsValid[2] = false;
				optionsValid[3] = false;
			}
            // split
            else if (choice.compare("d") == 0 && optionsValid[3])
            {
				std::cout << "-> You've chosen to split! This hand was split into two. Continue with this hand. \n\n";
                split(playerHands[i], playerHands);
                optionsValid[3] = false;
            }
            else
            {
                std::cout << "Please choose a valid option!\n\n";
            }

            handVal = getHandValue(playerHands[i]);
			std::cout << "Current hand:\n";
			std::cout << "Bet: " << playerHands[i].bet << "\n";
			std::cout << "Hand value: " << handVal << "\n";
            printHandCards(playerHands[i]);
        } 
    }

	if (deck.endOfStack())
	{
		std::cout << "Deck is finished!";
	}

    checkWinningHands(playerHands, dealerHand);
}

// Deals a card from the top of the deck to the given hand
void BlackJackApp::deal(int numCards, Hand& hand)
{
	for (int i = 0; i < numCards; i++)
	{
		hand.cards.push_back(deck.popStack());
	}
}

// Prints the hands of the dealer and player
void BlackJackApp::printAllHands(const std::vector<Hand> &pHands, const Hand &dHand, bool showDealer)
{
    for(unsigned int i = 0; i < pHands.size(); i++)
    {
        std::cout << "\nPlayer hand #" << i + 1 << " (Bet: " << pHands[i].bet << ")\n";
        printHandCards(pHands[i]);
    }

    std::cout << "Dealer hand:\n";

	if (showDealer)
	{
		printHandCards(dHand);
	}
	else
	{
		std::cout << "cards:  ";
		std::string dRank = dHand.cards[0].rank;
		std::string dSuit = dHand.cards[0].suit;
		std::cout << dRank << dSuit << "  ";
		std::cout << "[HIDDEN CARD]" << "\n\n";
	}
}

// Prints the cards of a given hand
void BlackJackApp::printHandCards(const Hand &hand)
{
	std::cout << "cards:  ";
    for(unsigned int i = 0; i < hand.cards.size(); i++)
    {
        std::string rank = hand.cards[i].rank;
        std::string suit = hand.cards[i].suit;
        std::cout << rank << suit << "  ";
    }
    std::cout << "\n\n";
}

void BlackJackApp::hit(Hand &hand)
{
    deal(1, hand);
}

void BlackJackApp::split(Hand &hand, std::vector<Hand> &pHands)
{
    Hand splitHand;
    splitHand.bet = hand.bet / 2;
    splitHand.cards.push_back(hand.cards.back());

    hand.bet = hand.bet - splitHand.bet;
    hand.cards.pop_back();

    pHands.push_back(splitHand);
}

void BlackJackApp::doubleDown(Hand &hand)
{
    hand.bet = hand.bet * 2;
    deal(1, hand);
}

void BlackJackApp::printPlayerOptions()
{
    std::cout << "\n";
    for(int i = 0; i < 4; i++)
    {
        if(optionsValid[i])
        {
            std::cout << playerOptions[i] << "    ";
        }
    }
    std::cout << "\n\n";
}

// Resets all player options to valid
void BlackJackApp::resetPlayerOptions()
{
    for(int i = 0; i < 4; i++)
    {
        optionsValid[i] = true;
    }
}

// Calculates and returns the BlackJack value of a hand
int BlackJackApp::getHandValue(const Hand &hand)
{
    int handTotal = 0;
    for(unsigned int i = 0; i < hand.cards.size(); i++)
    {
        int value = cardVals.at(hand.cards[i].rank);

        // If there is an Ace, add its value as 1 instead of 11 if
        // an added 11 would result in a player bust
        if(hand.cards[i].rank.compare("A") == 0 && handTotal + value > blackJackVal)
        {
            handTotal += 1;
        }
        else
        {
            handTotal += value;
        }
    }
    return handTotal;
}

// Compares the player's hands to the dealer's to see who wins
void BlackJackApp::checkWinningHands(const std::vector<Hand> &pHands, const Hand &dHand)
{
	std::cout << "\n------\nAll Hands Played! The Game Has Ended!\n------\n";
    printAllHands(pHands, dHand, true);
    for(unsigned int i = 0; i < pHands.size(); i++)
    {
        int playerScore = getHandValue(pHands[i]);
        int dealerScore = getHandValue(dHand);

        std::cout << "------\nResults of hand #" << i + 1 << ":\n\n";
        std::cout << "Player Hand value: " << playerScore << "\n";
        std::cout << "Dealer Hand value: " << dealerScore << "\n\n";

        if(playerScore > dealerScore)
        {
            if(playerScore <= blackJackVal)
            {
                std::cout << "Player Hand #" << i + 1 << " WINS!\n";
                std::cout << "You won " << pHands[i].bet * 2 << " chips from this hand.\n\n";
            }
            else
            {
                if(dealerScore <= blackJackVal)
                {
                    std::cout << "Dealer WINS!\n";
                    std::cout << "You lost " << pHands[i].bet << " chips from this hand.\n\n";
                }
                else
                {
                    std::cout << "Player and Dealer bust on their hands...No winner.\n";
                    std::cout << "You keep your " << pHands[i].bet << " chips from this hand.\n\n";
                }
            } 
        }
        else if(dealerScore > playerScore)
        {
            if(dealerScore <= blackJackVal)
            {
                std::cout << "Dealer WINS!\n";
                std::cout << "You lost " << pHands[i].bet << " chips from this hand.\n\n";
            }
            else
            {
                if(playerScore <= blackJackVal)
                {
                    std::cout << "Player Hand #" << i + 1 << " WINS!\n";
                    std::cout << "You won " << pHands[i].bet * 2 << " chips from this hand.\n\n";
                }
                else
                {
                    std::cout << "Player and Dealer bust on their hands...No winner.\n";
                    std::cout << "You keep your " << pHands[i].bet << " chips from this hand.\n\n";
                }
            } 
        }
        else
        {
            std::cout << "Player and Dealer hands are equal in value...No winner.\n";
            std::cout << "You keep your " << pHands[i].bet << " chips from this hand.\n\n";
        }
    }
    std::cout << "------\n\n";
}
