#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

struct Card
{
public:
	std::string rank;
	std::string suit;
};

struct Hand
{
	std::vector<Card> cards;
	int bet = 0;
};

class Deck
{
private:
	std::vector<Card> cards;
	static const std::string suits[];
	static const std::string ranks[];
	unsigned int stackIterator;

public:
	Deck();
	void shuffle();
	void resetStack();
	Card popStack();
	bool endOfStack();
};
