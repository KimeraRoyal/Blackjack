#include <iostream>
#include <ctime>
#include <windows.h>

#include "Menu.h"

int main()
{
	// Sets the window title displayed at the top of the console. This is a Windows-exclusive function.
	SetConsoleTitle(TEXT("Blackjack"));

	// Seeds the rand() function based on the user's current system time.
	// This only needs to be run once - running it more could at best be pointless be pointless and at worst enable exploits.
	srand(time(nullptr));

	// Enter the menu function. All subsequent game logic is handled here.
	blackjack::MenuLoop();
	
	return 0;
}