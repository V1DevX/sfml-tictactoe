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

// TODO: 
//  Board&
//  currentPlayer
//  state
//  winnerToState
// etc.