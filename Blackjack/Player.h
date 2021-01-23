#pragma once

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Hand.h"

namespace blackjack
{
	/// <summary>
	/// Player enum, with the total players in game (only the dealer and player).<br>
	/// Includes a value to refer to for the total amount of players, which should not be used as an index ever.
	/// </summary>
	enum ePlayer : int
	{
		PLAYER_DEALER,
		PLAYER_PLAYER,
		TOTAL_PLAYERS
	};

	/// <summary>
	/// String values for every player name.<br>
	/// Includes an additional blank value for the TOTAL_PLAYERS value, just in-case. Don't be that case.
	/// </summary>
	constexpr char c_playerNames[][7] = { "Dealer", "Player", "" };

	/// <summary>
	/// Data necessary for players.
	/// </summary>
	struct Player
	{
		/// <summary>
		/// The cards currently in the player's card.
		/// </summary>
		Deck* m_hand;

		/// <summary>
		/// The amount of money the player currently has available for bets.
		/// </summary>
		int m_bank;
	};

	/// <summary>
	/// Allocate memory to and create a new player in the heap.
	/// </summary>
	/// <param name="_startingBank">The starting amount of money that the player will have available for bets. Dealer's is 0.</param>
	/// <returns>A pointer to the created player in memory.</returns>
	Player* CreatePlayer(int _startingBank);

	/// <summary>
	/// Free the memory allocated to a player and its "children" stored in the heap, and nullify their pointers.
	/// </summary>
	/// <param name="_player">The player to be de-allocated.</param>
	void DestroyPlayer(Player*& _player);

	/// <summary>
	/// Get a string value to display a player's name.
	/// </summary>
	/// <param name="_player"></param>
	/// <returns></returns>
	const char* GetPlayerName(ePlayer _player);

	/// <summary>
	/// Get the total combined value of a player's hand. If a card is face down, it is not counted.
	/// </summary>
	/// <param name="_player">The player whose hand is to be accumulated.</param>
	/// <param name="_aceValue">The integer value of Aces (should be 1 or 11, set elsewhere in the program)</param>
	/// <returns>An integer value corresponding to the hand's total value.</returns>
	int GetTotalHandValue(Player* _player, int _aceValue);

	/// <summary>
	/// Compare one player's hand to another and determines whether they wins against them.
	/// </summary>
	/// <param name="_a">The player whose hand will be checked.</param>
	/// <param name="_b">The player whose hand will be checked against.</param>
	/// <param name="_aceValue">The integer value of Aces (should be 1 or 11, set elsewhere in the program)</param>
	/// <returns>An enum value determining whether the hand loses, ties, wins, or holds a winning natural.</returns>
	eHandValidityComparison CompareHands(Player* _a, Player* _b, int _aceValue);
}

#endif