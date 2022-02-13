#include "Deck.h"


//constructor
Deck::Deck(std::vector<Card> _cards) {
	cards = _cards;
}

//destructor
Deck::~Deck() {

}

//Returns the top card of the deck/pile
Card Deck::drawCard(bool discardCard = false){
	Card topCard = cards.front();
	if (discardCard) {
		cards.erase(cards.begin()); //remove card
		discardedCards.push_back(topCard); //move card to discard pile
	}
	else
		cards.push_back(topCard); //move card to bottom of pile
	return topCard;
}

//shuffel the deck/pile
void Deck::shuffel() {
	//shuffel by randomly taking the last and first cards
	std::random_shuffle(cards.begin(), cards.end());

}