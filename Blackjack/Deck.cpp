#include "Deck.h"

#include <iostream>

namespace blackjack
{
	Deck* GenerateDeck()
	{
		auto* deck = new Deck{ {}, 0 };

		return deck;
	}

	void DestroyDeck(Deck*& _deck)
	{
		// All card pointers stored by the deck must be de-allocated / nullified BEFORE the deck itself, to prevent memory leaks.
		for (auto card_index = 0; card_index < _deck->m_size; card_index++)
		{
			delete _deck->m_cards[card_index];
			_deck->m_cards[card_index] = nullptr;
		}

		delete _deck;
		_deck = nullptr;
	}

	void PopulateDeck(Deck* _deck)
	{
		for (auto card_index = 0; card_index < c_maxDeckSize; card_index++)
		{
			AddCard(_deck, new Card{ (eSuit)(card_index / TOTAL_RANKS), (eRank)(card_index % TOTAL_RANKS), true });
		}
	}

	void AddCard(Deck* _deck, Card* _card)
	{
		// Cards cannot be added past the max deck size, to prevent errors.
		// As long as only one deck is populated, this should never actually be possible, but it's good to catch edge cases.
		if (_deck->m_size < c_maxDeckSize)
		{
			_deck->m_cards[_deck->m_size] = _card;
			_deck->m_size++;
		}
	}

	Card* DrawCard(Deck* _deck)
	{
		Card* card = nullptr;

		// You cannot draw cards from an empty deck. You should not even try. Do not do it.
		if (_deck->m_size > 0)
		{
			_deck->m_size -= 1;

			card = _deck->m_cards[_deck->m_size];

			// Prevent the card's position from becoming duplicated in memory by nullifying its pointer in the original deck.
			_deck->m_cards[_deck->m_size] = nullptr;
		}

		return card;
	}

	void MoveCard(Deck* _from, Deck* _to)
	{
		AddCard(_to, DrawCard(_from));
	}


	void ShuffleDeck(Deck* _deck, const int _min, const int _max)
	{
		// A very simple shuffle. Every card in the deck gets swapped at least once, so it's effective enough for our purposes.
		for (auto cardIndex = _min; cardIndex < _max; cardIndex++)
		{
			const auto targetIndex = rand() % (_max - _min) + _min;
			SwapCards(_deck->m_cards[cardIndex], _deck->m_cards[targetIndex]);
		}
	}

	void ShuffleDeck(Deck* _deck)
	{
		ShuffleDeck(_deck, 0, _deck->m_size);
	}

	void SwapCards(Card*& _a, Card*& _b)
	{
		// No actual memory manipulation is needed here, just change where the pointers point to.
		auto* temp = _a;
		_a = _b;
		_b = temp;
	}

	void MergeDecks(Deck* _from, Deck* _to)
	{
		// Cache the starting size of _from, since the value changes when we draw cards from it.
		const auto fromSize = _from->m_size;
		for (auto cardIndex = 0; cardIndex < fromSize; cardIndex++)
		{
			MoveCard(_from, _to);
		}
	}
}