#include "IO.h"

#include <iostream>

namespace blackjack
{
	int GetInput(const int _maxValue, const char _inputName[],
		const char _valuePrefix[], const char _valueSuffix[], const char _inputPrefix[])
	{
		auto playerInput = 0;

		while (playerInput == 0)
		{
			std::cout << "Please select " << _inputName << " from " << _valuePrefix << "1" << _valueSuffix << " to " <<
				_valuePrefix << _maxValue << _valueSuffix << ": " << _inputPrefix;

			// If the value that is read by std::cin is invalid, i.e. a user entering "a", it will return false.
			// This can just be mixed with an OR of the range validation.
			if (!ReadLine(playerInput) || playerInput < 1 || playerInput > _maxValue)
			{
				std::cout << "Invalid Input.\n";
				
				// Reset the player's input, so that the while doesn't break when a type-valid input is out of range.
				playerInput = 0;
			}
		}

		return playerInput;
	}

	int GetOption(const int _options)
	{
		return GetInput(_options, "an option", "(", ")", "");
	}

	int GetBet(const int _maxValue)
	{
		return GetInput(_maxValue, "a value", "\x9C", "", "\x9C");
	}

	bool ReadLine(int& o_returnValue)
	{
		char intArray[c_maxInputLength];

		auto hasBreak = false;
		for(auto i = 0; i < c_maxInputLength; i++)
		{
			const auto in = std::cin.get();

			// If the current character is a newline, break the for loop and null-terminate the int array.
			if(in == '\n')
			{
				intArray[i] = 0;
				hasBreak = true;
				
				break;
			}
			
			// If the current character isn't a number value, immediately invalidate the input.
			if (in < '0' || in > '9')
			{
				break;
			}
			intArray[i] = (char) in;
		}

		// If the line was longer than c_maxInputLength, invalidate the input.
		if(!hasBreak)
		{
			// Clear any error flags in the input stream, otherwise we can't interact with it (like with std::cin.ignore)
			std::cin.clear();

			// Flush the input stream, skipping to the next new line.
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			return false;
		}

		o_returnValue = atoi(intArray);
		return true;
	}
}