#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "Deck.h"

class BlackJackApp
{
private:
	Deck deck;
	bool optionsValid[4];
	std::string playerOptions[4];
	std::unordered_map<std::string, int> cardVals;

	void playRound();
	int getHandValue(const Hand& hand);
	void deal(int numCards, Hand& hand);
	void printAllHands(const std::vector<Hand>& pHands, const Hand& dHand, bool showDealer = false);
	void printHandCards(const Hand& hand);
	void printPlayerOptions();
	void resetPlayerOptions();
	void hit(Hand& hand);
	void split(Hand& hand, std::vector<Hand>& pHands);
	void doubleDown(Hand& hand);
	void checkWinningHands(const std::vector<Hand>& pHands, const Hand& dHand);

public:
	const static int blackJackVal = 21;
	void run();
};