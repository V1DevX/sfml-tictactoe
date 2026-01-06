#include "Board.hpp"

Board::Board() {
	reset();
}

void Board::reset() {
	cells.fill(Cell::Empty);
}

bool Board::inRange(int row, int col) {
	return row>=0 && row<3 && col>=0 && col<3;
}

int Board::index (int row, int col) {
	return row*3 + col;
}

bool Board::place (int row, int col, Cell value) {
	if( !inRange(row,col) ) return false;
	
	const int i = index(row,col);
	if( cells[i] != Cell::Empty) return false;
	cells[i] = value;
	
	return true;
}

Cell Board::at(int row, int col) const {
	if( !inRange(row,col) ) return Cell::Empty;
	return cells[index(row,col)];
}

bool Board::isFull() const {
	for (Cell c : cells){
		if( c == Cell::Empty ) return false;
	}
	return true;
}