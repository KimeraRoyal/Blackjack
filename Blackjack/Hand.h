#pragma once

#ifndef HAND_H_
#define HAND_H_

#include "Deck.h"

namespace blackjack
{
	/// <summary>
	/// The return values for hand validity checks.
	/// </summary>
	enum eHandValidity : int
	{
		HAND_VALIDITY_BUST = 0,
		HAND_VALIDITY_VALID,
		HAND_VALIDITY_NATURAL
	};

	/// <summary>
	/// The return values for hand comparison checks.
	/// </summary>
	enum eHandValidityComparison : int
	{
		HAND_COMPARISON_LOSS = 0,
		HAND_COMPARISON_TIE,
		HAND_COMPARISON_WIN,
		HAND_COMPARISON_NATURAL
	};

	/// <summary>
	/// 4 1-Aces, 4 Twos, and 3 Threes makes a perfect 21. Adding one for bust, a player cannot possibly have more cards in their hand than this.
	/// </summary>
	constexpr auto c_maxHandSize = 12;

	/// <summary>
	/// The max amount of lines that can be displayed when printing card columns.<br>
	/// This is equal to the maximum hand size, plus two lines for the player names, and total hand values.
	/// </summary>
	constexpr auto c_maxDisplaySize = c_maxHandSize + 2;

	/// <summary>
	/// The max length of individual lines that are displayed in card columns.
	/// This is equal to the maximum card name length, plus 12 bytes for additional characters that are displayed.
	/// </summary>
	constexpr auto c_maxDisplayLength = c_maxCardNameSize + 12;

	/// <summary>
	/// Get the total combined value of a hand. If a card is face down, it is not counted.
	/// </summary>
	/// <param name="_hand">The hand to be accumulated.</param>
	/// <param name="_aceValue">The integer value of Aces (should be 1 or 11, set elsewhere in the program)</param>
	/// <returns>An integer value corresponding to the hand's total value.</returns>
	int GetTotalHandValue(Deck* _hand, int _aceValue);

	/// <summary>
	/// Perform a check on a hand to determine its validity.
	/// </summary>
	/// <param name="_hand">The hand to be checked.</param>
	/// <param name="_aceValue">The integer value of Aces (should be 1 or 11, set elsewhere in the program)</param>
	/// <returns>An enum value determining whether the hand is bust, valid, or natural.</returns>
	eHandValidity IsHandValid(Deck* _hand, int _aceValue);

	/// <summary>
	/// Compare a hand to another and determine whether it wins against it.
	/// </summary>
	/// <param name="_handA">The hand to check.</param>
	/// <param name="_handB">The hand to check against.</param>
	/// <param name="_aceValue">The integer value of Aces (should be 1 or 11, set elsewhere in the program)</param>
	/// <returns>An enum value determining whether the hand loses, ties, wins, or holds a winning natural.</returns>
	eHandValidityComparison CompareHands(Deck* _handA, Deck* _handB, int _aceValue);

	/// <summary>
	/// Copy the data of a hand into a specifically formatted 2D char-array used to display columns.
	/// </summary>
	/// <param name="_hand">The hand to display.</param>
	/// <param name="_aceValue">The integer value of Aces (should be 1 or 11, set elsewhere in the program)</param>
	/// <param name="o_returnValue">A 2D char array to be output into. MUST be at least the dimensions ("c_maxDisplaySize * TOTAL_PLAYERS", "c_maxDisplayLength")</param>
	/// <param name="_column">The column this data will be output in. MUST be less than the enum value "TOTAL_PLAYERS"</param>
	/// <param name="_offset">The offset of this data in the 2D array, in-case there is additional data above it in the column.</param>
	void DisplayHand(Deck* _hand, int _aceValue, char o_returnValue[][c_maxDisplayLength], int _column, int _offset);
}

#endif
