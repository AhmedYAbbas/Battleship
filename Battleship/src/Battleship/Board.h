#pragma once

class Board
{
public:
	Board() = default;
	virtual ~Board() = default;

	virtual void Clear() = 0;
};
