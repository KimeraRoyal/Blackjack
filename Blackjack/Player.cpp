#include "Player.h"

namespace blackjack
{
	Player* CreatePlayer(const int _startingBank)
	{
		// Player hands are stored using the deck struct. Yes, this is kind of confusing terminology.
		// A possible alternative could be renaming Deck to CardPool or something, but there's no need.
		// I know that "deck" just loosely means "pool of cards" and I'm the only one programming this.
		auto* hand = GenerateDeck();
		auto* player = new Player{ hand, _startingBank };
		return player;
	}

	void DestroyPlayer(Player*& _player)
	{
		// The player's deck must be de-allocated BEFORE the player themselves!
		DestroyDeck(_player->m_hand);

		delete _player;
		_player = nullptr;
	}

	const char* GetPlayerName(const ePlayer _player)
	{
		return c_playerNames[_player];
	}

	int GetTotalHandValue(Player* _player, const int _aceValue)
	{
		// This is just a proxy function for the one defined in Hand
		return GetTotalHandValue(_player->m_hand, _aceValue);
	}

	eHandValidityComparison CompareHands(Player* _a, Player* _b, const int _aceValue)
	{
		// This is just a proxy function for the one defined in Hand
		return CompareHands(_a->m_hand, _b->m_hand, _aceValue);
	}
}