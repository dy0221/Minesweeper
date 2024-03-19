#ifndef MAKE_CELL
#define MAKE_CELL

#include <iostream>
namespace CELL {
	class Cell
	{
	private:
		int row; int column;
		int neighbor_mines_count;
		bool has_mine = false;
		bool opened = false;
		bool flagged = false;
	public:
		Cell(int r_val = 0, int c_val = 0) : row(r_val), column(c_val), neighbor_mines_count(0) {}

		void ShowMember() const {
			std::cout << "row : " << row << std::endl;
			std::cout << "column : " << column << std::endl;
			std::cout << "neighbor : " << neighbor_mines_count << std::endl;
			std::cout << "mine : " << has_mine << std::endl;
			std::cout << "opened : " << opened << std::endl;
			std::cout << "flagged : " << flagged << std::endl << std::endl;
		}
		int NumNeighborMinesCount() const { return neighbor_mines_count; }
		bool IsOpend() const { return this->opened; }
		bool IsFlagged() const { return this->flagged; }
		bool IsMined() const { return this->has_mine; }

		void SetOpened() { this->opened = true; }
		void SetFlaged() { this->flagged = true; };
		void SetUnFlaged() { this->flagged = false; }
		void SetMine() { this->has_mine = true; }
		void SetNeighborMinesCount() { this->neighbor_mines_count++; }
	};
}

#endif