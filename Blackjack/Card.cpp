#include <cstring>

#include "Card.h"

namespace blackjack
{
	const char* GetSuitName(const eSuit _suit)
	{
		return c_suitNames[_suit];
	}

	const char* GetRankName(const eRank _rank)
	{
		return c_rankNames[_rank];
	}

	void GetCardName(Card* _card, char o_returnValue[])
	{
		char cardNameString[c_maxCardNameSize];

		// The player should not be allowed to see any information about cards that aren't visible (face down)
		if (_card->m_visible)
		{
			strcpy_s(cardNameString, GetRankName(_card->m_rank));
			strcat_s(cardNameString, " of ");
			strcat_s(cardNameString, GetSuitName(_card->m_suit));
		}
		else
		{
			strcpy_s(cardNameString, "Face Down");
		}

		// This memcpy_s is required due to a quirk of C++ where arrays degrade to pointers when passed as an argument to a function.
		memcpy_s(o_returnValue, c_maxCardNameSize, cardNameString, c_maxCardNameSize);
	}

	int GetRankValue(const eRank _rank, const int _aceValue)
	{
		switch (_rank)
		{
			case RANK_ACE:
			{
				return _aceValue;
			}

			// The Jack, Queen, and King are valued at 10.
			case RANK_JACK:
			case RANK_QUEEN:
			case RANK_KING:
			{
				return 10;
			}

			default:
			{
				//  Enum values start at 0, so 1 is added to get the "proper" value.
				return (int)_rank + 1;
			}
		}
	}

	int GetCardValue(Card* _card, const int _aceValue)
	{
		return GetRankValue(_card->m_rank, _aceValue);
	}

	void GetValueString(int _value, char o_returnValue[])
	{
		char cardValueString[3] = { 0, 0, 0 };

		int i = 0;
		while (_value > 0)
		{
			// Modulo by 10 returns just the smallest digit of the number.
			// Since this is a char array, the digit needs to have "c_asciiNumbersBegin" added so that the ASCII digit is properly displayed. 
			cardValueString[i] = (char)(_value % 10 + c_asciiNumbersBegin);

			// Integer division precision loss chops off the decimal place and makes the next digit the smallest.
			_value /= 10;

			i++;
		}

		// If the value has two characters, it will need to be flipped due to being put into the array in a reverse order.
		if (i > 1)
		{
			cardValueString[0] ^= cardValueString[1];
			cardValueString[1] ^= cardValueString[0];
			cardValueString[0] ^= cardValueString[1];
		}

		// This memcpy_s is required due to a quirk of C++ where arrays degrade to pointers when passed as an argument to a function.
		memcpy_s(o_returnValue, 3, cardValueString, 3);
	}
}