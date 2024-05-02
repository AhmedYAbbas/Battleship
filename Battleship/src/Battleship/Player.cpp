#include "Player.h"

Player::Player(const std::string& name)
	: m_Type(PlayerType::Human), m_Name(name)
{
	Init();
}

void Player::Init()
{
	m_Ships[0].Init(ShipTypeSize::AircraftCarrier, ShipType::AircraftCarrier);
	m_Ships[1].Init(ShipTypeSize::Battleship, ShipType::Battleship);
	m_Ships[2].Init(ShipTypeSize::Cruiser, ShipType::Cruiser);
	m_Ships[3].Init(ShipTypeSize::Destroyer, ShipType::Destroyer);
	m_Ships[4].Init(ShipTypeSize::Submarine, ShipType::Submarine);
}

void Player::ClearBoards()
{
	m_GuessBoard.Clear();
	m_ShipBoard.Clear();
}
