#include "Deck.h"

const std::string Deck::suits[] = {"H", "D", "S", "C"};
const std::string Deck::ranks[] = {"2", "3", "4", "5", "6", "7", 
                                   "8", "9", "10", "A", "J", "Q", "K"};

Deck::Deck()
{
    // Build the deck
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            Card newCard;
            newCard.rank = ranks[j];
            newCard.suit = suits[i];
            cards.push_back(newCard);
        }
    }
    stackIterator = 0;
}

void Deck::shuffle()
{
	resetStack();
	srand((int)time(0));

    // Swaps each card with a random card in the deck
    for(unsigned int i = 0; i < cards.size(); i++)
    {
        int randCardIndex = rand() % cards.size();
        Card tempCard = cards[i];
        cards[i] = cards[randCardIndex];
        cards[randCardIndex] = tempCard;
    }
}

void Deck::resetStack()
{
    stackIterator = 0;
}

// The deck acts as psuedo-stack with an iterator keeping track of the top card
Card Deck::popStack()
{
    if(endOfStack())
    {
        resetStack();
    }
    
    Card top = cards[stackIterator];
    stackIterator++;

    return top;
}

// Checks if the iterator has reached the end of the deck's card vector
bool Deck::endOfStack()
{
	if (stackIterator >= cards.size())
	{
		return true;
	}
	return false;
}