#include "game_logic.h"

namespace LOGIC {

    Logic::Logic(DLIST::DbLinkedList* map_list, MAP::Map* map_interface) {
        this->map_interface = map_interface;
        this->map_list = map_list;

    }

    Logic::~Logic() {
    }

    void Logic::DFS(int row, int column) {
        int row_size = this->map_interface->ReturnRowSize();
        int column_size = this->map_interface->ReturnColumnSize();

        int list_data = column_size * (row - 1) + column;
        
        int delta_row[] =    { -1, -1, -1, 0, 0, 1, 1, 1 };
        int delta_column[] = { -1,  0,  1, -1, 1, -1, 0, 1 };
        int delta_iter[] = { (-1 - 1 * column_size),(-1 * column_size) , (1 - 1 * column_size), -1, 1, (-1 + column_size), column_size, (1 + column_size) };

        if (row < 1 || row > row_size || column < 1 || column > column_size) {
            return;
        }

        CELL::Cell* cell = this->map_list->GetData(list_data);

        if (cell->IsMined()) {
            return;
        }

        if (cell->IsOpend()) {
            return;
        }

        cell->SetOpened();
        //gui->ButtonHide(gui->FindButton(row, column));
        if (listener != nullptr) {
            listener->onEventOccurred(row, column); 
        }

        if (cell->NumNeighborMinesCount() > 0) {
            return;
        }

        Logic::DFS(row + delta_row[1], column + delta_column[1]);
        Logic::DFS(row + delta_row[3], column + delta_column[3]);
        Logic::DFS(row + delta_row[4], column + delta_column[4]);
        Logic::DFS(row + delta_row[6], column + delta_column[6]);
        for (int i = 0; i < 8; i++) {
            int temp_row = row + delta_row[i];
            int temp_column = column + delta_column[i];

            if (temp_row < 1 || temp_row > row_size || temp_column < 1 || temp_column > column_size) {
                continue;
            }
            cell = this->map_list->GetData(list_data + delta_iter[i]);
            if (cell->IsMined()) {
                return;
            }
        }
        Logic::DFS(row + delta_row[0], column + delta_column[0]);
        Logic::DFS(row + delta_row[2], column + delta_column[2]);
        Logic::DFS(row + delta_row[5], column + delta_column[5]);
        Logic::DFS(row + delta_row[7], column + delta_column[7]);
    }

    void Logic::MakeMap() {
        this->map_interface->MakeMap();
        this->map_interface->MakeMine();
        this->map_interface->CalculateNeighborMines();
    }

    void Logic::CleanMap() {
        this->map_interface->ClearMap();
    }


    bool Logic::GameOver(int row, int column) {
        int row_size = this->map_interface->ReturnRowSize();
        int column_size = this->map_interface->ReturnColumnSize();

        int list_data = column_size * (row - 1) + column;
        CELL::Cell* cell = this->map_list->GetData(list_data);

        if (cell->IsMined()) {
            return true;
        }
        else {
            return false;
        }
    }

    bool Logic::GameClear() {
        int row_size = this->map_interface->ReturnRowSize();
        int column_size = this->map_interface->ReturnColumnSize();

        for (int i = 1; i <= row_size * column_size; i++) {
            CELL::Cell* cell = this->map_list->GetData(i);
            if (cell->IsMined()) continue;

            if (!cell->IsOpend()) return false;
        }
        return true;
    }
};