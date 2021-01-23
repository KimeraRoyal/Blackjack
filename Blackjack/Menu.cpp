#include "Menu.h"

#include <iostream>

#include "Game.h"
#include "IO.h"

namespace blackjack
{
	void MenuLoop()
	{
		auto running = true;
		while(running)
		{
			// Execute a system instruction to clear the console.
			// This isn't recommended for plenty of reasons, but it's easy and simple for our specific purposes.
			system("CLS");
			std::cout << "Options:\n(1) - New Game\n(2) - Debug Mode\n(3) - Quit\n";
			const auto playerInput = GetOption(3);
			
			switch(playerInput)
			{
				// Both the New Game and Debug Mode options launch the game - just with debug mode either enabled or disabled.
				case 1:
				case 2:
				{
					// New Game: 1 becomes 0 aka. false, turning off Debug Mode.
					// Debug Mode: 2 becomes 1 aka. true, enabling Debug Mode.
					auto* game = blackjack::InitGame(playerInput - 1);

					// All game logic is handled in the Game Loop.
					GameLoop(game);
					// Once the user decides to break the Game Loop, we need to dispose of the Game object to prevent memory leaks.
					EndGame(game);
						
					break;
				}
				case 3:
				{
					// Quit: 3 disables the while loop, ending the program.
					running = false;
						
					break;
				}
				default:
				{
					// The IO code should automatically prevent other options from being selected but it's good to catch errors.
					std::cout << "Unexpected menu case encountered!\n\n";
				}
			}
		}
	}
}
