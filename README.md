# Battleship

A classic text-based implementation of Battleship for the console, written entirely in C++. Place your fleet, take turns firing on your opponent's grid, and sink every ship to win — play against a friend locally or test your luck against a simple AI opponent.

[![Watch the video](https://img.youtube.com/vi/rx_0r-vypxQ/hqdefault.jpg)](https://www.youtube.com/embed/rx_0r-vypxQ)

***

## Features

- **Two game modes** — play Human vs. Human on the same machine, or Human vs. AI.
- **Manual fleet placement** — choose the position and orientation (horizontal/vertical) for each of your 5 ships.
- **Classic fleet composition** — Aircraft Carrier (5), Battleship (4), Cruiser (3), Destroyer (3), and Submarine (2).
- **Dual-board console rendering** — your own fleet board and your tracking (guess) board are drawn side by side each turn on a 10x10 grid (A–J, 1–10).
- **Turn-based combat** — call out coordinates, get instant hit/miss/sunk feedback, and see who wins when a full fleet is destroyed.
- **Input validation** — guards against invalid coordinates, out-of-bounds or overlapping ship placement, and repeated guesses.

## Building the project

**Requirements:** Windows with Visual Studio 2022 (or later), using the MSVC v143 toolset.

1. Open `Battleship.sln` in Visual Studio.
2. Build and run with `F5` (or `Ctrl+F5` to run without debugging).
3. Enjoy!

## How to play

1. Choose whether Player 2 is a Human or an AI opponent.
2. Each human player places their 5 ships by entering a starting position (row `A`–`J`, column `1`–`10`) and an orientation (`H` or `V`).
3. Players take turns entering coordinates to fire at the opponent's fleet.
4. The console reports each shot as a **hit**, **miss**, or a **sunk** ship.
5. The first player to sink their opponent's entire fleet wins.
