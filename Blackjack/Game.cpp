#include "Game.h"

#include <iostream>
#include <iomanip>

#include "IO.h"

namespace blackjack
{
	Game* InitGame(const bool _debug)
	{
		auto* dealer = CreatePlayer(0);
		auto* player = CreatePlayer(c_startingBank);
		auto* game = new Game{{dealer, player}, 0, {}, {}, 1, _debug };

		game->m_deck = GenerateDeck();
		game->m_discard = GenerateDeck();

		// The actual deck is populated at the start of the game. No other deck should be!
		// There will never be any issues with too many cards in any one deck as long as only this deck is populated at the start.
		PopulateDeck(game->m_deck);

		ShuffleDeck(game->m_deck);

		return game;
	}

	void EndGame(Game*& _game)
	{
		// The deck, discard pile, and every player must all be de-allocated before the game.
		// Failing to remember to do this could cause memory leaks.
		DestroyDeck(_game->m_deck);
		DestroyDeck(_game->m_discard);

		for (auto playerIndex = 0; playerIndex < TOTAL_PLAYERS; playerIndex++)
		{
			DestroyPlayer(_game->m_players[playerIndex]);
		}

		delete _game;
		_game = nullptr;
	}

	void GameLoop(Game* _game)
	{
		// The game will loop infinitely until either the player runs out of money or they choose to stop playing.
		// When done, the function will resolve, where the menu will then delete the game instance and loop.
		auto playing = true;
		while (playing)
		{
			SelectBet(_game);
			SelectAceValue(_game);

			InitialDeal(_game);
			PlayerTurn(_game);
			DealerTurn(_game);

			ComparePlayers(_game);

			DiscardHands(_game);

			// If the player goes bankrupt, they automatically lose the game and are returned to the menu.
			if (_game->m_players[PLAYER_PLAYER]->m_bank < 1)
			{
				playing = false;

				// The screen is paused until the player enters a key, so that they know what's happened.
				// std::flush forces the console to sync up with the output stream, which is necessary for calls to system.
				// I'm obviously oversimplifying a lot, but this is a comment in my program, not cppreference.
				std::cout << "You are bankrupt! Returning to menu...\n\n" << std::flush;
				system("PAUSE");
			}
			else if(!EndOfRound())
			{
				playing = false;
			}
		}
	}

	void SelectBet(Game* _game)
	{
		const auto currentMoney = _game->m_players[PLAYER_PLAYER]->m_bank;

		system("CLS");
		std::cout << "How much do you want to bet? (Current Money: \x9C" << currentMoney << ")\n";

		// The player can obviously only bet an amount of money they actually have!
		const auto bet = GetBet(currentMoney);

		_game->m_players[PLAYER_PLAYER]->m_bank -= bet;
		_game->m_currentBet = bet;

		std::cout << "\n";
	}

	void SelectAceValue(Game* _game)
	{
		std::cout << "How much do you want aces to be worth?\nOptions:\n(1) - Aces are worth 1\n(2) - Aces are worth 11\n";

		// Change the input value to 0 or 1, then multiply by 10 and add 1.
		// (1): 1 - 1 = 0, 0 * 10 = 0, 0 + 1 = 1
		// (2): 2 - 1 = 1, 1 * 10 = 10, 10 + 1 = 11
		_game->m_aceValue = (GetOption(2) - 1) * 10 + 1;
	}

	void InitialDeal(Game* _game)
	{
		for (auto i = 0; i < c_initialDeal; i++)
		{
			for (auto playerIndex = 0; playerIndex < TOTAL_PLAYERS; playerIndex++)
			{
				DealCard(_game, _game->m_players[playerIndex]->m_hand);
			}
		}

		if (!_game->m_debug)
		{
			_game->m_players[PLAYER_DEALER]->m_hand->m_cards[0]->m_visible = false;
		}

		system("CLS");
		std::cout << "Initial Draw..." << std::endl << std::endl;
		DisplayGameInformation(_game);
	}

	void PlayerTurn(Game* _game)
	{
		auto isPlayerTurn = true;
		while (isPlayerTurn)
		{
			std::cout << "Options:\n(1) - Hit (Ask for another card)\n(2) - Stand (Keep current hand)\n";
			const auto playerInput = GetOption(2);

			switch(playerInput)
			{
				case 1:
				{
					system("CLS");
					std::cout << "Player Draws...\n\n";

					DealCard(_game, _game->m_players[PLAYER_PLAYER]->m_hand);
					DisplayGameInformation(_game);

					// If the player's hand is bust, then they automatically pass their turn to the dealer as there's nothing else they can do.
					const auto totalHandValue = GetTotalHandValue(_game->m_players[PLAYER_PLAYER], _game->m_aceValue);
					if (totalHandValue > 21)
					{
						// Pause the console until the player enters a key, so they know that their hand is bust.
						std::cout << "Player's hand is bust! (Over 21)\n" << std::flush;
						system("PAUSE");
						isPlayerTurn = false;
					}

					break;
				}
				case 2:
				{
					// The player is happy with their hand and passes to the dealer, breaking the while loop.
					isPlayerTurn = false;

					break;
				}
				default:
				{
					// The IO code should automatically prevent other options from being selected but it's good to catch errors.
					std::cout << "Unexpected player option case encountered!\n\n";
						
					break;
				}
			}
		}
	}

	void DealerTurn(Game* _game)
	{
		// Flip dealer's first card face up
		if (!_game->m_debug)
		{
			_game->m_players[PLAYER_DEALER]->m_hand->m_cards[0]->m_visible = true;
		}

		while (GetTotalHandValue(_game->m_players[PLAYER_DEALER], _game->m_aceValue) < 17)
		{
			DealCard(_game, _game->m_players[PLAYER_DEALER]->m_hand);
		}

		system("CLS");
		std::cout << "Dealer Draws...\n\n";

		DisplayGameInformation(_game);
	}

	void ComparePlayers(Game* _game)
	{
		switch (CompareHands(_game->m_players[PLAYER_PLAYER], _game->m_players[PLAYER_DEALER], _game->m_aceValue))
		{
		case HAND_COMPARISON_LOSS:
			{
				std::cout << "Dealer Wins!\nYou lose your bet (\x9C" << _game->m_currentBet << ")...\n";
				
				_game->m_currentBet = 0;
				break;
			}

		case HAND_COMPARISON_TIE:
			{
				std::cout << "Player Ties!\nYou receive your bet (\x9C" << _game->m_currentBet << ") back.\n";
				
				_game->m_players[PLAYER_PLAYER]->m_bank += _game->m_currentBet;
				_game->m_currentBet = 0;
				break;
			}

		case HAND_COMPARISON_WIN:
			{
				std::cout << "Player Wins!\nYou receive double your initial bet, earning \x9C" << _game->m_currentBet * 2 <<
					" back!\n";
				
				_game->m_players[PLAYER_PLAYER]->m_bank += _game->m_currentBet * 2;
				_game->m_currentBet = 0;
				break;
			}

		case HAND_COMPARISON_NATURAL:
			{
				std::cout << "...BLACKJACK!!!\nYou receive two and a half times your initial bet, earning \x9C" << 
					(int)((float)_game->m_currentBet * 2.5f) << " back!\n";
				
				_game->m_players[PLAYER_PLAYER]->m_bank += (int)((float)_game->m_currentBet * 2.5f);
				_game->m_currentBet = 0;
				break;
			}
		}

		std::cout << "\n" << std::flush;
		system("PAUSE");
	}

	void DiscardHands(Game* _game)
	{
		for (auto playerIndex = 0; playerIndex < TOTAL_PLAYERS; playerIndex++)
		{
			MergeDecks(_game->m_players[playerIndex]->m_hand, _game->m_discard);
		}
	}

	bool EndOfRound()
	{
		std::cout << "Do you wish to continue playing?\n(1) - Yes\n(2) - No\n";

		// The brackets here are important, as otherwise the possible values would be -1 and -2, which we obviously don't want.
		return 1 - (GetOption(2) - 1);
	}


	void DealCard(Game* _game, Deck* _hand)
	{
		MoveCard(_game->m_deck, _hand);

		// If the deck is empty, then shuffle the discard pile back into it.
		if (_game->m_deck->m_size < 1)
		{
			MergeDecks(_game->m_discard, _game->m_deck);
			ShuffleDeck(_game->m_deck);
		}
	}

	void DisplayGameInformation(Game* _game)
	{
		if(_game->m_debug)
		{
			std::cout << "DEBUG MODE\n";
		}

		// \x9C is the Unicode character for the pound symbol. Not guaranteed to be the same on every system ever.
		// ...but it should be standard amongst most systems.
		std::cout << "Total Money: \x9C" << _game->m_players[PLAYER_PLAYER]->m_bank << " Current Bet: \x9C" << _game->
			m_currentBet << "\n\n";

		// A two dimensional array, double the potential length of the actual display.
		// This means that the array will be formatted { Dealer, Player, Dealer, Player, Dealer Player ... }
		char cardDisplay[c_maxDisplaySize * TOTAL_PLAYERS][c_maxDisplayLength];
		memset(cardDisplay, 0, c_maxDisplaySize * TOTAL_PLAYERS * c_maxDisplayLength);

		for (auto playerIndex = 0; playerIndex < TOTAL_PLAYERS; playerIndex++)
		{
			strcpy_s(cardDisplay[playerIndex], GetPlayerName((ePlayer)playerIndex));
			strcat_s(cardDisplay[playerIndex], " Hand");

			// The offset here is offset by TOTAL_PLAYERS, since there is an additional line at the top of each column for the player name.
			DisplayHand(_game->m_players[playerIndex]->m_hand, _game->m_aceValue, cardDisplay, TOTAL_PLAYERS, playerIndex + TOTAL_PLAYERS);
		}

		for (auto displayIndex = 0; displayIndex < c_maxDisplaySize; displayIndex++)
		{
			// If both columns are blank then the display text array is finished, and the loop can be broken.
			// The alternative to this is up to 10 lines of nothing. It doesn't look good.
			if (cardDisplay[displayIndex * TOTAL_PLAYERS][0] == 0 && cardDisplay[displayIndex * TOTAL_PLAYERS + 1][0] == 0)
			{
				break;
			}

			// Set the output to be padded, keeping text to the left, so that every column is neatly formatted.
			std::cout << std::setw(c_maxDisplayLength + c_columnOffset) << std::left <<
				cardDisplay[displayIndex * TOTAL_PLAYERS] << cardDisplay[displayIndex * TOTAL_PLAYERS + 1] << "\n";
		}

		// One line break, just to neatly format the application.
		std::cout << "\n";
	}
}
