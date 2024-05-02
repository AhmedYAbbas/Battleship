#include "Utils/Utility.h"
#include "Game.h"
#include "Ship.h"
#include "Player.h"

Game::Game(const std::string& playerOneName, const std::string& playerTwoName)
	: m_Player1(std::make_shared<Player>(playerOneName)), m_Player2(std::make_shared<Player>(playerTwoName))
{
}

void Game::Start()
{
	std::srand(std::time(nullptr));

	Utility::ClearScreen();
	m_Player1->SetType(PlayerType::Human);
	m_Player2->SetType(GetPlayerTwoType());

	SetupBoards(m_Player1.get());
	SetupBoards(m_Player2.get());
}

void Game::Run()
{
	Player* currentPlayer = m_Player1.get();;
	Player* otherPlayer = m_Player2.get();

	Position guess;
	do
	{
		if (currentPlayer->GetType() == PlayerType::Human)
			DrawBoards(currentPlayer);

		bool isValidGuess;
		do
		{
			if (currentPlayer->GetType() == PlayerType::Human)
			{
				std::cout << currentPlayer->GetName() << ", what is your guess? " << std::endl;
				guess = GetShipPosition();
			}
			else
				guess = GetRandomPosition();

			isValidGuess = currentPlayer->GetGuessBoard().GetGrid()[guess.row][guess.col] == GuessType::None;
			if (!isValidGuess && currentPlayer->GetType() == PlayerType::Human)
				std::cout << "That was not a valid guess! Please try again." << std::endl;
		}
		while (!isValidGuess);

		ShipType type = UpdateBoards(guess, currentPlayer, otherPlayer);

		if (currentPlayer->GetType() == PlayerType::AI)
		{
			DrawBoards(otherPlayer);
			std::cout << currentPlayer->GetName() << " chose row " << char(guess.row + 'A') << " and column " << guess.col + 1 << std::endl;
		}
		else
			DrawBoards(currentPlayer);

		if (type != ShipType::None && IsSunk(otherPlayer, otherPlayer->GetShips()[static_cast<int>(type) - 1]))
		{
			if (currentPlayer->GetType() == PlayerType::AI)
				std::cout << currentPlayer->GetName() << " sunk your " << otherPlayer->GetShips()[static_cast<int>(type) - 1].GetName() << "!" << std::endl;
			else
				std::cout << "You sunk " << otherPlayer->GetName() << "'s " << otherPlayer->GetShips()[static_cast<int>(type) - 1].GetName() << "!" << std::endl;
		}

		Utility::WaitForKeyPress();
		SwitchPlayers(currentPlayer, otherPlayer);
	}
	while (!IsGameOver(m_Player1.get(), m_Player2.get()));

	DisplayWinner(m_Player1.get(), m_Player2.get());
}

PlayerType Game::GetPlayerTwoType() const
{
	const int validInputs[2] = {1, 2};
	int input = Utility::GetInteger("Who would you like to player against?\n1. Human\n2. AI\n\nWhat is your choice? ", "Input error! Please try again.", validInputs, 2);

	if (input == 1)
		return PlayerType::Human;
	else
		return PlayerType::AI;
}

Position Game::GetRandomPosition() const
{
	return { std::rand() % 10, std::rand() % 10 };
}

bool Game::IsSunk(const Player* player, const Ship& ship)
{
	if (ship.GetOrientation() == ShipOrientation::Horizontal)
	{
		for (int col = ship.GetPosition().col; col < (ship.GetPosition().col + ship.GetSize()); ++col)
		{
			if (!player->GetShipBoard().GetGrid()[ship.GetPosition().row][col].Hit)
				return false;
		}
	}
	else
	{
		for (int row = ship.GetPosition().row; row < (ship.GetPosition().row + ship.GetSize()); ++row)
		{
			if (!player->GetShipBoard().GetGrid()[row][ship.GetPosition().col].Hit)
				return false;
		}
	}

	return true;
}

void Game::SwitchPlayers(Player*& currentPlayer, Player*& otherPlayer)
{
	Player* tmp = currentPlayer;
	currentPlayer = otherPlayer;
	otherPlayer = tmp;
}

void Game::SetupBoards(Player* player)
{
	player->ClearBoards();

	if (player->GetType() == PlayerType::AI)
	{
		SetupAIBoards(player);
		return;
	}

	for (int i = 0; i < 5; ++i)
	{
		DrawBoards(player);
		Ship& ship = player->GetShips()[i];

		Position shipPos;
		ShipOrientation shipOrientation;

		bool isValidPlacement = false;
		do
		{
			std::cout << player->GetName() << " please set the position and orientation for your " << ship.GetName() << std::endl;

			shipPos = GetShipPosition();
			shipOrientation = GetShipOrientation();

			isValidPlacement = IsValidPlacement(player, ship, shipPos, shipOrientation);
			if (!isValidPlacement)
			{
				std::cout << "That was not a valid placement. Please try again." << std::endl;
				Utility::WaitForKeyPress();
			}
		}
		while (!isValidPlacement);

		PlaceShipOnBoard(player, ship, shipPos, shipOrientation);
	}

	DrawBoards(player);
	Utility::WaitForKeyPress();
}

void Game::SetupAIBoards(Player* player)
{
	Position pos;
	ShipOrientation orientation;

	for (int i = 0; i < 5; ++i)
	{
		Ship& currentShip = player->GetShips()[i];

		do
		{
			pos = GetRandomPosition();
			orientation = static_cast<ShipOrientation>(std::rand() % 2);
		}
		while (!IsValidPlacement(player, currentShip, pos, orientation));

		PlaceShipOnBoard(player, currentShip, pos, orientation);
	}
}

void Game::DrawBoards(Player* player)
{
	Utility::ClearScreen();

	DrawColumnsRow();
	DrawColumnsRow();
	std::cout << std::endl;

	for (int r = 0; r < 10; ++r)
	{
		DrawLine();
		std::cout << " ";
		DrawLine();
		std::cout << std::endl;

		DrawShipBoardRow(player, r);
		std::cout << " ";
		DrawGuessBoardRow(player, r);
		std::cout << std::endl;
	}

	DrawLine();
	std::cout << " ";
	DrawLine();
	std::cout << std::endl;
}

void Game::DrawColumnsRow()
{
	std::cout << "  ";
	for (int c = 0; c < 10; ++c)
	{
		int columnName = c + 1;
		std::cout << " " << columnName << "  ";
	}
}

void Game::DrawLine()
{
	std::cout << " ";
	for (int c = 0; c < 10; ++c)
		std::cout << "+---";
	std::cout << "+";
}

void Game::DrawShipBoardRow(Player* player, int row)
{
	char rowName = row + 'A';
	std::cout << rowName << "|";
	for (int c = 0; c < 10; ++c)
		std::cout << " " << player->GetShipBoard().GetShipRepresentationAt(row, c) << " |";
}

void Game::DrawGuessBoardRow(Player* player, int row)
{
	char rowName = row + 'A';
	std::cout << rowName << "|";
	for (int c = 0; c < 10; ++c)
		std::cout << " " << player->GetGuessBoard().GetGuessRepresentationAt(row, c) << " |";
}

Position Game::GetShipPosition()
{
	char rowInput;
	int colInput;

	const char validRowInputs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
	const int validColumnInputs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	rowInput = Utility::GetCharacter("Please input a row (A - J): ", "Input error! Please try again.", validRowInputs, 10, CharacterCaseType::UpperCase);
	colInput = Utility::GetInteger("Please input a column (1 - 10): ", "Input error! Please try again.", validColumnInputs, 10);

	return {rowInput - 'A', colInput - 1};
}

ShipOrientation Game::GetShipOrientation()
{
	const char validInput[2] = {'H', 'V'};

	char input = Utility::GetCharacter("Please choose and orientation (H) for Horizontal or (V) for Vertical: ", "Input error! Please try again.", validInput, 2, CharacterCaseType::UpperCase);

	if (input == validInput[0])
		return ShipOrientation::Horizontal;
	else
		return ShipOrientation::Vertical;
}

bool Game::IsValidPlacement(Player* player, const Ship& currentShip, const Position& shipPosition, ShipOrientation orientation) const
{
	if (orientation == ShipOrientation::Horizontal)
	{
		for (int c = shipPosition.col; c < (shipPosition.col + currentShip.GetSize()); ++c)
		{
			if (player->GetShipBoard().GetGrid()[shipPosition.row][c].Type != ShipType::None || c >= 10)
				return false;
		}
	}
	else
	{
		for (int r = shipPosition.row; r < (shipPosition.row + currentShip.GetSize()); ++r)
		{
			if (player->GetShipBoard().GetGrid()[r][shipPosition.col].Type != ShipType::None || r >= 10)
				return false;
		}
	}
	return true;
}

void Game::PlaceShipOnBoard(Player* player, Ship& currentShip, const Position& shipPosition, ShipOrientation orientation)
{
	currentShip.SetPosition(shipPosition);
	currentShip.SetOrientation(orientation);

	if (orientation == ShipOrientation::Horizontal)
	{
		for (int c = shipPosition.col; c < (shipPosition.col + currentShip.GetSize()); ++c)
		{
			player->GetShipBoard().GetGrid()[shipPosition.row][c].Type = currentShip.GetType();
			player->GetShipBoard().GetGrid()[shipPosition.row][c].Hit = false;
		}
	}
	else
	{
		for (int r = shipPosition.row; r < (shipPosition.row + currentShip.GetSize()); ++r)
		{
			player->GetShipBoard().GetGrid()[r][shipPosition.col].Type = currentShip.GetType();
			player->GetShipBoard().GetGrid()[r][shipPosition.col].Hit = false;
		}
	}
}

ShipType Game::UpdateBoards(const Position& guess, Player* currentPlayer, Player* otherPlayer)
{
	if (otherPlayer->GetShipBoard().GetGrid()[guess.row][guess.col].Type != ShipType::None)
	{
		currentPlayer->GetGuessBoard().GetGrid()[guess.row][guess.col] = GuessType::Hit;
		otherPlayer->GetShipBoard().GetGrid()[guess.row][guess.col].Hit = true;
	}
	else
		currentPlayer->GetGuessBoard().GetGrid()[guess.row][guess.col] = GuessType::Miss;

	return otherPlayer->GetShipBoard().GetGrid()[guess.row][guess.col].Type;
}

bool Game::IsGameOver(Player* playerOne, Player* playerTwo)
{
	return AreAllShipsSunk(playerOne) || AreAllShipsSunk(playerTwo);
}

bool Game::AreAllShipsSunk(Player* player)
{
	for (int i = 0; i < 5; ++i)
	{
		if (!IsSunk(player, player->GetShips()[i]))
			return false;
	}
	return true;
}

void Game::DisplayWinner(Player* playerOne, Player* playerTwo)
{
	if (AreAllShipsSunk(playerOne))
		std::cout << "Congratulations " << playerTwo->GetName() << "! You won!" << std::endl;
	else
		std::cout << "Congratulations " << playerOne->GetName() << "! You won!" << std::endl;
}

void Game::Init()
{
	m_Player1->Init();
	m_Player2->Init();
}
