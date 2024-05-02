#pragma once

#include <string>

enum class ShipType
{
	None = 0,
	AircraftCarrier,
	Battleship,
	Cruiser,
	Destroyer,
	Submarine
};

enum class ShipTypeSize
{
	AircraftCarrier = 5,
	Battleship = 4,
	Cruiser = 3,
	Destroyer = 3,
	Submarine = 2
};

struct ShipPart
{
	ShipType Type;
	bool Hit;
};

enum class ShipOrientation
{
	Horizontal = 0,
	Vertical
};

struct Position
{
	int row;
	int col;
}; 

class Ship
{
public:
	Ship();
	Ship(int size, ShipType type, ShipOrientation orientation, Position position);

	void Init(ShipTypeSize size, ShipType type);

	const std::string GetName() const;
	const Position& GetPosition() const { return m_Position; }
	const ShipOrientation GetOrientation() const { return m_Orientation; }
	const ShipType GetType() const { return m_Type; }
	int GetSize() const { return m_Size; }

	ShipOrientation GetOrientation() { return m_Orientation; }
	Position& GetPosition() { return m_Position; }
	ShipType GetType() { return m_Type; }

	void SetPosition(const Position& pos) { m_Position = pos; }
	void SetOrientation(ShipOrientation orientation) { m_Orientation = orientation; }

private:
	int m_Size;
	ShipType m_Type;
	ShipOrientation m_Orientation;
	Position m_Position;
};