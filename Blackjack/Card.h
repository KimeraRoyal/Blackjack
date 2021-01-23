#pragma once

#ifndef CARD_H_
#define CARD_H_

namespace blackjack
{
	/// <summary>
	/// Card suit enum.<br>
	/// Includes a value to refer to for the total amount of suits, which should not be assigned to a value ever.
	/// </summary>
	enum eSuit : int
	{
		SUIT_HEARTS = 0,
		SUIT_DIAMONDS,
		SUIT_CLUBS,
		SUIT_SPADES,
		TOTAL_SUITS
	};

	/// <summary>
	/// Card rank enum.<br>
	/// Includes a value to refer to for the total amount of ranks, which should not be assigned to a value ever.
	/// </summary>
	enum eRank : int
	{
		RANK_ACE = 0,
		RANK_TWO,
		RANK_THREE,
		RANK_FOUR,
		RANK_FIVE,
		RANK_SIX,
		RANK_SEVEN,
		RANK_EIGHT,
		RANK_NINE,
		RANK_TEN,
		RANK_JACK,
		RANK_QUEEN,
		RANK_KING,
		TOTAL_RANKS
	};

	/// <summary>
	/// 18 is the maximum size a card name can possibly be (including the zero-terminator), i.e. "Queen of Diamonds"
	/// </summary>
	constexpr auto c_maxCardNameSize = 18;

	/// <summary>
	/// 48 is the ASCII value for 0.
	/// </summary>
	constexpr auto c_asciiNumbersBegin = 48;

	/// <summary>
	/// String values for every suit name.<br>
	/// Includes an additional blank value for if the TOTAL_SUITS value is used for a card. Don't do this, by the way.
	/// </summary>
	constexpr char c_suitNames[][9] = { "Hearts", "Diamonds", "Clubs", "Spades", "" };

	/// <summary>
	/// String values for every rank name.<br>
	/// Includes an additional blank value for if the TOTAL_RANKS value is used for a card. Seriously, though, don't do this.
	/// </summary>
	constexpr char c_rankNames[][6] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "King", "Queen", "" };

	/// <summary>
	/// All data that is necessary to store for a card.<br>
	/// Cards will, in memory, always keep their suit and rank but these should be hidden from the user if m_visible is false.
	/// </summary>
	struct Card
	{
		eSuit m_suit;
		eRank m_rank;

		/// <summary>
		/// If this is set to false, it is assumed that the card is face-down (the "Hole Card")
		/// </summary>
		bool m_visible;
	};

	/// <summary>
	/// Get a string value to display a suit's name.
	/// </summary>
	/// <param name="_suit">An enum value corresponding to the suit that is to be displayed.</param>
	/// <returns>A 9-byte long const char array of the suit's name.</returns>
	const char* GetSuitName(eSuit _suit);

	/// <summary>
	/// Get a string value to display a rank's name.
	/// </summary>
	/// <param name="_rank">An enum value corresponding to the rank that is to be displayed.</param>
	/// <returns>A 6-byte long const char array of the rank's name.</returns>
	const char* GetRankName(eRank _rank);

	/// <summary>
	/// Copy the string value of a card's name (formatted "Rank of Suit") to a char array.
	/// </summary>
	/// <param name="_card">Card struct to read data from.</param>
	/// <param name="o_returnValue">A char array to be output into. MUST be at least the size of const value "c_maxCardNameSize"</param>
	void GetCardName(Card* _card, char o_returnValue[]);

	/// <summary>
	/// Get the integer value of a specific rank.
	/// </summary>
	/// <param name="_rank">An enum value corresponding to the rank whose value is needed.</param>
	/// <param name="_aceValue">The integer value of Aces (should be 1 or 11, set elsewhere in the program)</param>
	/// <returns>An integer value corresponding to the rank's value.</returns>
	int GetRankValue(eRank _rank, int _aceValue);

	/// <summary>
	/// Get the integer value of a card, based on its rank.
	/// </summary>
	/// <param name="_card">The card whose rank is to be read.</param>
	/// <param name="_aceValue">The integer value of Aces (should be 1 or 11, set elsewhere in the program)</param>
	/// <returns>An integer value corresponding to the card's rank's value.</returns>
	int GetCardValue(Card* _card, int _aceValue);

	/// <summary>
	/// Copy the 1-2 character string value of card's value to a char array.
	/// </summary>
	/// <param name="_value">Integer value to be converted to a string.</param>
	/// <param name="o_returnValue">A char array to be output into. MUST be at least 3-bytes long.</param>
	void GetValueString(int _value, char o_returnValue[]);
}

#endif