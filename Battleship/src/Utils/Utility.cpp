#include <iostream>
#include <cctype>

#include "Utility.h"

char Utility::GetCharacter(const std::string& prompt, const std::string& error)
{
	const int IGNORE_CHARS = 256;

	char input;
	bool failure;

	do
	{
		failure = false;

		std::cout << prompt;
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(IGNORE_CHARS, '\n');
			std::cout << error << std::endl;
			failure = true;
		}
		else
		{
			std::cin.ignore(IGNORE_CHARS, '\n');

			if (std::isalpha(input))
				input = std::tolower(input);
			else
			{
				std::cout << error << std::endl;
				failure = true;
			}
		}
	}
	while (failure);

	return input;
}

char Utility::GetCharacter(const std::string& prompt, const std::string& error, const char validInput[], int validInputLength, CharacterCaseType charCase)
{
	const int IGNORE_CHARS = 256;

	char input;
	bool failure;

	do
	{
		failure = false;

		std::cout << prompt;
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(IGNORE_CHARS, '\n');
			std::cout << error << std::endl;
			failure = true;
		}
		else
		{
			std::cin.ignore(IGNORE_CHARS, '\n');

			if (std::isalpha(input))
			{
				if (charCase == CharacterCaseType::UpperCase)
					input = std::toupper(input);
				else if (charCase == CharacterCaseType::LowerCase)
					input = std::tolower(input);

				for (int i = 0; i < validInputLength; i++)
				{
					if (input == validInput[i])
						return input;
				}
			}

			std::cout << error << std::endl;
			failure = true;
		}

	}
	while (failure);

	return input;
}

int Utility::GetInteger(const std::string& prompt, const std::string& error, const int validInput[], int validInputLength)
{
	int input;
	bool inputFailure;

	const int IGNORE_CHARS = 256;
	do
	{
		inputFailure = false;

		std::cout << prompt;
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(IGNORE_CHARS, '\n');
			std::cout << error << std::endl;
			inputFailure = true;
		}
		else
		{
			for (int i = 0; i < validInputLength; i++)
			{
				if (input == validInput[i])
					return input;
			}

			std::cout << error << std::endl;
			inputFailure = true;
		}
	}
	while (inputFailure);

	return -1;
}

void Utility::ClearScreen()
{
	system("cls");
}

void Utility::WaitForKeyPress()
{
	system("pause -n 1 -s -p \"Press any key to continue...\";echo");
}
