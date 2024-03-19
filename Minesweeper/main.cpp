#include "MineswpeerGui.h"
#include "make_map.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
       
    DLIST::DbLinkedList* list = new DLIST::DbLinkedList();
    MineswpeerGui gui(nullptr, list);

    gui.show();
    return app.exec(); 

}
