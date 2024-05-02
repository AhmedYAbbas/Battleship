#pragma once

#include <string>

#include "GuessBoard.h"
#include "ShipBoard.h"
#include "Ship.h"

enum class PlayerType
{
	Human = 0,
	AI
};

class Player
{
public:
	Player(const std::string& name);

	const std::string& GetName() const { return m_Name; }

	const ShipBoard& GetShipBoard() const { return m_ShipBoard; }
	const GuessBoard& GetGuessBoard() const { return m_GuessBoard; }
	const Ship* GetShips() const { return m_Ships; }
	const PlayerType GetType() const { return m_Type; }

	ShipBoard& GetShipBoard() { return m_ShipBoard; }
	GuessBoard& GetGuessBoard() { return m_GuessBoard; }
	Ship* GetShips() { return m_Ships; }

	void SetType(PlayerType type) { m_Type = type; }

	void Init();
	void ClearBoards();

private:
	PlayerType m_Type;
	std::string m_Name;
	Ship m_Ships[5];
	GuessBoard m_GuessBoard;
	ShipBoard m_ShipBoard;
};