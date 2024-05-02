#include "Ship.h"

Ship::Ship()
	: m_Size(0), m_Type(ShipType::None), m_Orientation(ShipOrientation::Horizontal), m_Position({0, 0})
{
}

Ship::Ship(int size, ShipType type, ShipOrientation orientation, Position position)
	: m_Size(0), m_Type(type), m_Orientation(orientation), m_Position(position)
{
}

void Ship::Init(ShipTypeSize size, ShipType type)
{
	m_Size = static_cast<int>(size);
	m_Type = type;
	m_Orientation = ShipOrientation::Horizontal;
	m_Position = {0, 0};
}

const std::string Ship::GetName() const
{
	switch (m_Type)
	{
		case ShipType::AircraftCarrier:
			return "Aircraft Carrier";
			break;
		case ShipType::Battleship:
			return "Battleship";
			break;
		case ShipType::Cruiser:
			return "Cruiser";
			break;
		case ShipType::Destroyer:
			return "Destroyer";
			break;
		case ShipType::Submarine:
			return "Submarine";
			break;
		default:
			return "None";
			break;
	}
}
