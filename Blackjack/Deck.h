#pragma once

#ifndef DECK_H_
#define DECK_H_

#include "Card.h"

namespace blackjack
{
	constexpr int c_maxDeckSize = TOTAL_SUITS * TOTAL_RANKS;

	/// <summary>
	/// A simple struct for tracking an array of cards, along with how many items are in it.<br>
	/// While this is called Deck, it is also used to store players' hands, and the discard pile.
	/// </summary>
	struct Deck
	{
		Card* m_cards[c_maxDeckSize];
		int m_size;
	};

	/// <summary>
	/// Allocate memory to and create a new deck in the heap.
	/// </summary>
	/// <returns>A pointer to the created deck in memory.</returns>
	Deck* GenerateDeck();

	/// <summary>
	/// Free the memory allocated to a deck stored in the heap, and nullify its pointer.
	/// </summary>
	/// <param name="_deck">The deck to be de-allocated.</param>
	void DestroyDeck(Deck*& _deck);

	/// <summary>
	/// Populate a deck with one copy of every single card.
	/// </summary>
	/// <param name="_deck">The deck to be populated.</param>
	void PopulateDeck(Deck* _deck);

	/// <summary>
	/// Add a card into a deck, incrementing its size value.
	/// </summary>
	/// <param name="_deck">The deck to add the card into.</param>
	/// <param name="_card">The card to be added.</param>
	void AddCard(Deck* _deck, Card* _card);

	/// <summary>
	/// Draw a card from a deck, decrementing its size value.
	/// </summary>
	/// <param name="_deck">The deck to draw the card from.</param>
	/// <returns>The card that was drawn.</returns>
	Card* DrawCard(Deck* _deck);

	/// <summary>
	/// Move the top card of one deck into another, changing their size values respectively.
	/// </summary>
	/// <param name="_from">The deck to draw the card from.</param>
	/// <param name="_to">The deck to add the drawn card into.</param>
	void MoveCard(Deck* _from, Deck* _to);

	/// <summary>
	/// Randomly shuffle every card in a deck, within a specific range.<br>
	/// All cards outside of this function's bounds will remain within their original position.
	/// </summary>
	/// <param name="_deck">The deck to be shuffled.</param>
	/// <param name="_min">The minimum position to shuffle from.</param>
	/// <param name="_max">The maximum position to shuffle from.</param>
	void ShuffleDeck(Deck* _deck, int _min, int _max);

	/// <summary>
	/// Randomly shuffle every card in a deck, up to its current size.
	/// </summary>
	/// <param name="_deck">The deck to be shuffled.</param>
	void ShuffleDeck(Deck* _deck);

	/// <summary>
	/// Swap the addresses of two card pointers.
	/// </summary>
	/// <param name="_a">A card to be swapped.</param>
	/// <param name="_b">A card to be swapped.</param>
	void SwapCards(Card*& _a, Card*& _b);

	/// <summary>
	/// Draw the entire contents of one deck, adding them onto another.
	/// </summary>
	/// <param name="_from">The deck to be drawn from.</param>
	/// <param name="_to">The deck to have cards added to.</param>
	void MergeDecks(Deck* _from, Deck* _to);
}

#endif