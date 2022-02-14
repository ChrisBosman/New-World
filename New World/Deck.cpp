#include "Deck.h"


//constructor
Deck::Deck(std::vector<Card*> _cards) {
	cards = _cards;
}

//destructor
Deck::~Deck() {
	for (int i = 0; i < cards.size(); i++)
		delete(cards[i]);
	for (int i = 0; i < discardedCards.size(); i++)
		delete(discardedCards[i]);
}

//Returns the top card of the deck/pile
Card* Deck::drawCard(bool discardCard = false){
	if (cards.empty())
		return nullptr;
	Card* topCard = cards.front();
	if (discardCard) {
		cards.erase(cards.begin()); //remove card
		discardedCards.push_back(topCard); //move card to discard pile
	}
	else
		cards.push_back(topCard); //move card to bottom of pile
	return topCard;
}

//Peek at a card, by default the top card (=0)
Card* Deck::peekCard(int8_t num)
{
	if (cards.empty()) //if no card then return null
		return nullptr;
	if (num == 0)
		return cards.front();
	return cards[cards.size() - num - 1];
}

//shuffel the deck/pile
void Deck::shuffel() {
	//shuffel by randomly taking the last and first cards
	std::random_shuffle(cards.begin(), cards.end());

}