#ifndef MAKE_MAP_H
#define MAKE_MAP_H

#include <iostream>
#include <set>
#include "linked_list.h"
#include<cstdlib> 
#include<ctime>

namespace MAP {
	class Map
	{
	private:
		int row_size;
		int column_size;
		int mine_num;
		DLIST::DbLinkedList* map_list;

	public:
		Map(DLIST::DbLinkedList* map_list, int row_size, int column_size, int mine_num);
		~Map();
		void InitMembers(int row_size, int column_size, int mine_num);
		void MakeMap();
		void MakeMine();
		void CalculateNeighborMines();
		void ClearMap();
		void ShowMap();
		int ReturnRowSize();
		int ReturnColumnSize();
	};

}



#endif