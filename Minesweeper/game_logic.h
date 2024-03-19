#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <iostream>
#include "linked_list.h"
#include "make_map.h"
#include "event_listener.h"
#include "cell.h"

namespace LOGIC {
    class Logic
    {
    private:
        MAP::Map * map_interface;
        DLIST::DbLinkedList* map_list;
        EventListener* listener; 
    public:
        void setEventListener(EventListener* listener) {
            this->listener = listener;
        }

        Logic(DLIST::DbLinkedList* map_list, MAP::Map* map_interface);
        ~Logic();
        void DFS(int row, int column);
        void MakeMap();
        void CleanMap();
        bool GameOver(int row, int column);
        bool GameClear();
    };
}

#endif