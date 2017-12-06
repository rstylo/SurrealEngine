#ifndef DECK_H_
#define DECK_H_


#include <list>
class Card;

class Deck
{
public:
	Deck();
	virtual ~Deck();

	virtual void AddCard(int, int);
	virtual void RemoveCard(Card*);

	virtual void Shuffle();


	virtual void ClearDeck();

private:
	int amount;

	std::list<Card*> cards;
};

#endif // DECK_H_