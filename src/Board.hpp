#pragma once 
#include <array>

enum class Cell : unsigned char { Empty, X, O };

class Board {
	public:
		Board();

		void reset();
		bool place(int row, int col, Cell value);

		Cell at(int row, int col) const;
		bool isFull() const;
	
	private:
		std::array<Cell, 9> cells; // index: row*3 + col
		
		static bool inRange(int row, int col);
		static int index(int row, int col);
};