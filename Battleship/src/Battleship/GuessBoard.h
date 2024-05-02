#pragma once

#include "Board.h"

enum class GuessType
{
	None = 0,
	Miss,
	Hit
};

class GuessBoard : public Board
{
public:
	virtual void Clear() override;

	using GuessTypes = GuessType[10][10];
	const GuessTypes& GetGrid() const { return m_GuessBoard; }
	GuessTypes& GetGrid() { return m_GuessBoard; }

	char GetGuessRepresentationAt(int row, int col) const;

private:
	GuessType m_GuessBoard[10][10];
};