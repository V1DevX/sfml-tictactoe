#pragma once
#include "Board.hpp"

enum class GameState : unsigned char {
	Playing,
	Draw,
	X_wins,
	O_wins
};

class Game {
	public:
		Game();

		void reset();
		bool handleMove(int row, int col);

		const Board& board() const;
		Cell currentPlayer() const;
		GameState state() const;

	private:
		Board board_;
		Cell current_ = Cell::X;
		GameState state_ = GameState::Playing;
		
		void advanceStateAfterMove();
		static GameState winnerToState(Cell player);
};
