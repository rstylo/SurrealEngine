#include "deck.h"

#include "Card.h"


Deck::Deck()
{
	for (int it1 = 0; it1 < 54; it1++) 
	{ 
		for (int it2 = 0; it2 < 4; it2++)
		{
			AddCard(it1+1, it2+1);
		}
	}
}


Deck::~Deck()
{
	ClearDeck();
}

void Deck::AddCard(int number, int type)
{
	Card* temp = new Card(number, type);

	cards.push_back(temp);

}

void Deck::RemoveCard(Card* card) 
{
	for (auto it = cards.begin; it != cards.end(); it++)
	{

		if ((*it) == card) 
		{
			delete (*it);
		}
		it = NULL;
	}
}

void Deck::ClearDeck()
{
	for (auto it = cards.begin; it != cards.end(); it++)
	{

		delete (*it);
	}
}