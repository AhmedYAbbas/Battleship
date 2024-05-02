#include "ShipBoard.h"

void ShipBoard::Clear()
{
	for (int r = 0; r < 10; ++r)
	{
		for (int c = 0; c < 10; ++c)
		{
			m_ShipBoard[r][c].Type = ShipType::None;
			m_ShipBoard[r][c].Hit = false;
		}
	}
}

char ShipBoard::GetShipRepresentationAt(int row, int col) const
{

	if (m_ShipBoard[row][col].Hit)
		return '*';

	switch (m_ShipBoard[row][col].Type)
	{
		case ShipType::AircraftCarrier:
			return 'A';
			break;
		case ShipType::Battleship:
			return 'B';
			break;
		case ShipType::Cruiser:
			return 'C';
			break;
		case ShipType::Destroyer:
			return 'D';
			break;
		case ShipType::Submarine:
			return 'S';
			break;
		default:
			return ' ';
			break;
	}
}
