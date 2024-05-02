#pragma once

#include "Board.h"
#include "Ship.h"

class ShipBoard : public Board
{
public:
	virtual void Clear() override;

	using ShipParts = ShipPart[10][10];
	const ShipParts& GetGrid() const { return m_ShipBoard; }
	ShipParts& GetGrid() { return m_ShipBoard; }

	char GetShipRepresentationAt(int row, int col) const;

private:
	ShipParts m_ShipBoard;
};