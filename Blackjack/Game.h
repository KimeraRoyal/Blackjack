#pragma once

#ifndef GAME_H_
#define GAME_H_

#include "Player.h"
#include "Deck.h"

namespace blackjack
{
	/// <summary>
	/// Whatever default money value the player should start at.
	/// </summary>
	constexpr auto c_startingBank = 100;

	/// <summary>
	/// The initial amount of cards dealt to the player and dealer.
	/// </summary>
	constexpr auto c_initialDeal = 2;

	/// <summary>
	/// A mandatory amount of padding to be applied when displaying columns in the menu.
	/// </summary>
	constexpr auto c_columnOffset = 10;

	struct Game
	{
		Player* m_players[(int)TOTAL_PLAYERS];

		/// <summary>
		/// The amount of money that has been put into the bet pool.
		/// </summary>
		int m_currentBet;

		Deck* m_deck;
		Deck* m_discard;

		/// <summary>
		/// The integer value of Aces (should be 1 or 11)
		/// </summary>
		int m_aceValue;

		/// <summary>
		/// Whether the game is running in Debug Mode. If this is true, "Hole Cards" will be displayed face-up.
		/// </summary>
		bool m_debug;
	};

	/// <summary>
	/// Allocate memory to and initialize a new game instance in the heap.
	/// </summary>
	/// <param name="_debug">Whether or not the game is being run in "Debug Mode", where the "Hole Card" is made face-up.</param>
	/// <returns>A pointer to the created game in memory.</returns>
	Game* InitGame(bool _debug);

	/// <summary>
	/// Free the memory allocated to a game instance and its "children" stored in the heap, and nullify their pointers.
	/// </summary>
	/// <param name="_game">The game to be de-allocated.</param>
	void EndGame(Game*& _game);

	/// <summary>
	/// Main function that dictates the structure of the game.
	/// </summary>
	/// <param name="_game">The game instance.</param>
	void GameLoop(Game* _game);

	/// <summary>
	/// The player may select how much of their remaining money they wish to bet.
	/// </summary>
	/// <param name="_game">The game instance.</param>
	void SelectBet(Game* _game);

	/// <summary>
	/// The player may select whether they want their aces to be valued at 1 or 11. This value is saved to the game struct.
	/// </summary>
	/// <param name="_game">The game instance.</param>
	void SelectAceValue(Game* _game);

	/// <summary>
	/// The player and dealer are both dealt 2 cards. One of the dealer's cards is dealt face down.
	/// </summary>
	/// <param name="_game">The game instance.</param>
	void InitialDeal(Game* _game);

	/// <summary>
	/// At this point, the player may choose to hit or stand.
	/// </summary>
	/// <param name="_game">The game instance.</param>
	void PlayerTurn(Game* _game);

	/// <summary>
	/// The dealer flips their face down card over. They deal themselves cards until their hand is valued over 17.
	/// </summary>
	/// <param name="_game">The game instance.</param>
	void DealerTurn(Game* _game);
	
	/// <summary>
	/// Compare players' hands, to find the winner of this deal.
	/// </summary>
	/// <param name="_game">The game instance.</param>
	void ComparePlayers(Game* _game);

	/// <summary>
	/// Discard all players' hands, in preparation for the next deal.
	/// </summary>
	/// <param name="_game">The game instance.</param>
	void DiscardHands(Game* _game);

	/// <summary>
	/// Check if the player wants to continue playing the game.
	/// </summary>
	/// <returns>True if the player wants to continue playing.</returns>
	bool EndOfRound();

	/// <summary>
	/// Deal a card from the game's primary deck, into a player's hand.
	/// </summary>
	/// <param name="_game">The game instance.</param>
	/// <param name="_hand">The player's hand to deal a card into.</param>
	void DealCard(Game* _game, Deck* _hand);

	/// <summary>
	/// Display information that is needed at multiple states of the game.<br>
	/// Specifically, the player's remaining money & current bet, current revealed cards, and the total card values.
	/// </summary>
	/// <param name="_game">The game instance.</param>
	void DisplayGameInformation(Game* _game);
}

#endif