#pragma once
#include "Card.h"
#include <algorithm>
#include <vector>
/*
	Bundels the cards into a deck, with functions like draw card
	and shuffel
*/

class Deck
{
public:
	Deck(std::vector<Card*> _cards);
	~Deck();
	Card* drawCard(bool discardCard); //return the top card
	Card* peekCard(int8_t num = 0);//peek at a card, default=topCard
	void shuffel();
private:
	std::vector<Card*> cards;
	std::vector<Card*> discardedCards;
};