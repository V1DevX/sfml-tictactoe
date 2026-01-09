#include "Game.hpp"

static Cell other(Cell c) {
	return (c == Cell::X) ? Cell::O : Cell::X;
}

Game::Game() {
	reset();
}

void Game::reset() {
	board_.reset();
	current_ = Cell::X;
	state_ = GameState::Playing;
}

const Board& Game::board() const { return board_; }
Cell Game::currentPlayer() const { return current_; }
GameState Game::state() const { return state_; }

GameState Game::winnerToState(Cell player) {
	return (player == Cell::X) ? GameState::X_wins : GameState::O_wins;
}

bool Game::handleMove(int row, int col) {
	if (state_ != GameState::Playing) return false;
	if (!board_.place(row, col, current_)) return false;

	advanceStateAfterMove();

	if (state_ == GameState::Playing) {
		current_ = other(current_);
	}

	return true;
}

void Game::advanceStateAfterMove() {
	// Check lines: 3 rows, 3 cols, 2 diags
	auto cell = [&](int r, int c) { return board_.at(r,c); };

	const int lines[8][3][2] {
		{{0,0}, {0,1}, {0,2}}, // Rows
		{{1,0}, {1,1}, {1,2}}, //
		{{2,0}, {2,1}, {2,2}}, //

		{{0,0}, {1,0}, {2,0}}, // Cols
		{{0,1}, {1,1}, {2,1}}, //
		{{0,2}, {1,2}, {2,2}}, //

		{{0,0}, {1,1}, {2,2}}, // Diags
		{{0,2}, {1,1}, {2,0}}, //
	};

	for (const auto& ln : lines) {
		Cell a = cell(ln[0][0], ln[0][1]); // {{0,0}, {0,1}, {0,2}}
		Cell b = cell(ln[1][0], ln[1][1]); //  a      b      c
		Cell c = cell(ln[2][0], ln[2][1]); //

		if (a != Cell::Empty && a==b && b==c) {
			state_ = winnerToState(a);
			return;
		}
	}
	
	if (board_.isFull()) state_ = GameState::Draw;
}