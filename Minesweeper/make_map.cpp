#include "make_map.h"

namespace MAP {
    Map::Map(DLIST::DbLinkedList* map_list, int row_size, int column_size, int mine_num) {
        this->InitMembers(row_size, column_size, mine_num);
        this->map_list = map_list;
        std::cout << "create heap data" << std::endl;
    };

    Map::~Map() {
        this->ClearMap();
        std::cout << "delete heap data" << std::endl;
    };

    void Map::InitMembers(int row_size, int column_size, int mine_num) {
        this->row_size = row_size;
        this->column_size = column_size;
        this->mine_num = mine_num;
    };

    void Map::MakeMap() {
        for (int i = 1; i <= row_size; i++) {
            for (int j = 1; j <= column_size; j++) {
                CELL::Cell* cell = new CELL::Cell(i, j);
                this->map_list->AddNode(cell);
            }
        }
    };

    void Map::MakeMine() {
        srand((unsigned int)time(NULL)); 


        std::set<int> mine_indices;

        while (mine_indices.size() < mine_num)
        {
            int minePos = rand() % (row_size * column_size) + 1; 
            mine_indices.insert(minePos);
        };

        for (int element : mine_indices) {
            CELL::Cell* cell = this->map_list->GetData(element);
            cell->SetMine();
            std::cout << "mine num : " << element << std::endl;
            //cell->ShowMember();
        }
    };

    void Map::CalculateNeighborMines() {
        int delta_row[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int delta_column[] = { -1,  0,  1, -1, 1, -1, 0, 1 };
        int delta_iter[] = { (-1 - 1 * column_size),(-1 * column_size) , (1 - 1 * column_size), -1, 1, (-1 + column_size), column_size, (1 + column_size) };

        int count_row = 0;
        int count_colum = 0;

        for (int iter = 1; iter <= row_size * column_size; iter++) {
            if ((iter % column_size) == 1) {
                count_row++;
            }
            count_colum = (iter - 1) % column_size + 1;
            for (int i = 0; i < 8; i++) {
                int temp_row = count_row + delta_row[i];
                int temp_column = count_colum + delta_column[i];

                if (temp_row < 1 || temp_row > row_size || temp_column < 1 || temp_column > column_size) {
                    continue;
                }

                CELL::Cell* cell = this->map_list->GetData(iter + delta_iter[i]);
                if (cell->IsMined()) {
                    cell = this->map_list->GetData(iter);
                    cell->SetNeighborMinesCount();
                }
            }
        }
    }


    void Map::ClearMap() {
        this->map_list->DeleteData();
    };


    void Map::ShowMap() {

        for (int iter = 1; iter <= row_size * column_size; iter++) {
            if ((iter % column_size) == 1) {
                std::cout << std::endl;
            }
            CELL::Cell* cell = this->map_list->GetData(iter);
            if (cell->IsMined()) {
                std::cout << "X ";
            }
            else {
                std::cout << cell->NumNeighborMinesCount() << " ";
            }
        }
        std::cout << std::endl;
    };

    int Map::ReturnRowSize() {
        return row_size;
    }

    int Map::ReturnColumnSize() {
        return column_size;
    }
}