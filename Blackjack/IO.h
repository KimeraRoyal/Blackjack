#pragma once

#ifndef INPUT_H_
#define INPUT_H_

namespace blackjack
{
	/// <summary>
	/// Get and validate the user's input as an integer from 1 to a maximum value (inclusive).
	/// </summary>
	/// <param name="_maxValue">The amount of options, maximum value that can be entered, etc.</param>
	/// <param name="_inputName">What the input will be described as i.e. "an option".</param>
	/// <param name="_valuePrefix">A prefix to be displayed before the min / max values.</param>
	/// <param name="_valueSuffix">A suffix to be displayed after the min / max values.</param>
	/// <param name="_inputPrefix">A prefix to be displayed before the user's input.</param>
	/// <returns></returns>
	int GetInput(int _maxValue, const char _inputName[], const char _valuePrefix[], const char _valueSuffix[], const char _inputPrefix[]);

	/// <summary>
	/// A shorthand to GetInput that displays "Please select an option from (1) to (max): _"
	/// </summary>
	/// <param name="_options">The amount of options that are available.</param>
	/// <returns></returns>
	int GetOption(int _options);

	/// <summary>
	/// A shorthand to GetInput that displays "Please select a value from £1 to £max: £_"
	/// </summary>
	/// <param name="_maxValue">The maximum amount the player can bet.</param>
	/// <returns>The chosen bet.</returns>
	int GetBet(int _maxValue);
}

#endif