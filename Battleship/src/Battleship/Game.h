#pragma once

#include <memory>
#include <string>

class Player;
class Ship;
struct Position;

enum class PlayerType;
enum class ShipOrientation;
enum class ShipType;

class Game
{
public:
	Game(const std::string& playerOneName, const std::string& playerTwoName);

	void Init();
	void Start();
	void Run();

private:
	PlayerType GetPlayerTwoType() const;
	Position GetRandomPosition() const;
	bool IsSunk(const Player* player, const Ship& ship);
	void SwitchPlayers(Player*& currentPlayer, Player*& otherPlayer);

	void SetupBoards(Player* player);
	void SetupAIBoards(Player* player);

	void DrawBoards(Player* player);
	void DrawColumnsRow();
	void DrawLine();
	void DrawShipBoardRow(Player* player, int row);
	void DrawGuessBoardRow(Player* player, int row);

	Position GetShipPosition();
	ShipOrientation GetShipOrientation();
	bool IsValidPlacement(Player* player, const Ship& currentShip, const Position& shipPosition, ShipOrientation orientation) const;

	void PlaceShipOnBoard(Player* player, Ship& currentShip, const Position& shipPosition, ShipOrientation orientation);
	ShipType UpdateBoards(const Position& guess, Player* currentPlayer, Player* otherPlayer);

	bool IsGameOver(Player* playerOne, Player* playerTwo);
	bool AreAllShipsSunk(Player* player);
	void DisplayWinner(Player* playerOne, Player* playerTwo);

private:
	std::shared_ptr<Player> m_Player1;
	std::shared_ptr<Player> m_Player2;
};