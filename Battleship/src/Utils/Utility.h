#pragma once

#include <iostream>

enum class CharacterCaseType
{
	UpperCase = 0,
	LowerCase,
	Either
};

class Utility
{
public:
	static char GetCharacter(const std::string& prompt, const std::string& error);
	static char GetCharacter(const std::string& prompt, const std::string& error, const char validInput[], int validInputLength, CharacterCaseType charCase);

	static int GetInteger(const std::string& prompt, const std::string& error, const int validInput[], int validInputLength);

	static void ClearScreen();
	static void WaitForKeyPress();
};
