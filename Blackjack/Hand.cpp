#include "Hand.h"

#include <iostream>

namespace blackjack
{
	int GetTotalHandValue(Deck* _hand, const int _aceValue)
	{
		// Sum together the values of every card in the hand.
		auto totalHandValue = 0;
		for (auto cardIndex = 0; cardIndex < _hand->m_size; cardIndex++)
		{
			// Multiply the card's value by its visibility means that face-down cards don't contribute to the total value.
			totalHandValue += GetCardValue(_hand->m_cards[cardIndex], _aceValue) * _hand->m_cards[cardIndex]->m_visible;
		}
		return totalHandValue;
	}

	eHandValidity IsHandValid(Deck* _hand, const int _aceValue)
	{
		const auto total_hand_value = GetTotalHandValue(_hand, _aceValue);

		// If the hand's value is less than or equal to 21, this will return 1.
		// If the hand's value is equal to 21 and there are only 2 cards in hand, it will return 2 (1 + 1)
		// I love that I can treat booleans like numbers in C++. It's very handy.
		return (eHandValidity)((total_hand_value <= 21) + (_hand->m_size == 2 && total_hand_value == 21));
	}

	eHandValidityComparison CompareHands(Deck* _handA, Deck* _handB, const int _aceValue)
	{
		const auto handAValidity = IsHandValid(_handA, _aceValue);
		const auto handBValidity = IsHandValid(_handB, _aceValue);
		const auto handAValue = GetTotalHandValue(_handA, _aceValue);
		const auto handBValue = GetTotalHandValue(_handB, _aceValue);

		// Check if hand A is bust.
		const auto bust = handAValidity == HAND_VALIDITY_BUST;

		// If both hands are bust, their values don't need to be equal to result in a tie.
		const auto tie = handAValidity == handBValidity && (bust || handAValue == handBValue);

		// If hand A is bust or hand A greater than it in value.
		// Also checks if hand A is a natural but hand B isn't, in case hand B is a non-natural 21.
		const auto win = handAValue > handBValue || handBValidity == HAND_VALIDITY_BUST || handAValidity == HAND_VALIDITY_NATURAL && handBValidity != HAND_VALIDITY_NATURAL;

		// Check if hand A is a natural 21.
		const auto natural = handAValidity == HAND_VALIDITY_NATURAL;

		// If the hand is a bust or tie then it obviously can't win or be a natural. This check prevents weird edge cases.
		// I say "edge case" as if I didn't encounter every single one of them during testing.
		return (eHandValidityComparison)(tie + (!bust && !tie) * (win * 2 + natural));
	}

	void DisplayHand(Deck* _hand, const int _aceValue, char o_returnValue[][c_maxDisplayLength], const int _column, const int _offset)
	{
		char cardValue[3];
		int returnLineIndex;

		for (auto i = 0; i < _hand->m_size; i++)
		{
			returnLineIndex = i * _column + + _offset;
			
			char cardName[c_maxCardNameSize];
			GetCardName(_hand->m_cards[i], cardName);

			// String memory manipulation can be used directly on the return value, since it's a 2D array.
			// The first dimension does degrade to a pointer, but the second dimension is what's being copied to.
			strcpy_s(o_returnValue[returnLineIndex], "Card: ");
			strcat_s(o_returnValue[returnLineIndex], cardName);

			if (_hand->m_cards[i]->m_visible)
			{
				GetValueString(GetCardValue(_hand->m_cards[i], _aceValue), cardValue);

				strcat_s(o_returnValue[returnLineIndex], " (");
				strcat_s(o_returnValue[returnLineIndex], cardValue);
				strcat_s(o_returnValue[returnLineIndex], ")");
			}
		}

		// This will always be the line immediately following the last card in the hand.
		returnLineIndex = _hand->m_size * _column + _offset;

		GetValueString(GetTotalHandValue(_hand, _aceValue), cardValue);

		strcpy_s(o_returnValue[returnLineIndex], "Hand Value: ");
		strcat_s(o_returnValue[returnLineIndex], cardValue);
	}
}
