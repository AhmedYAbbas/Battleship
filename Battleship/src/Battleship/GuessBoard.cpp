#include "GuessBoard.h"

void GuessBoard::Clear()
{
	for (int r = 0; r < 10; ++r)
		for (int c = 0; c < 10; ++c)
			m_GuessBoard[r][c] = GuessType::None;
}

char GuessBoard::GetGuessRepresentationAt(int row, int col) const
{
	switch (m_GuessBoard[row][col])
	{
		case GuessType::Hit:
			return '*';
			break;
		case GuessType::Miss:
			return 'o';
			break;
		default:
			return ' ';
			break;
	}
}
