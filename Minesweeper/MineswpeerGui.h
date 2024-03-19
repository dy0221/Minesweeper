#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <qicon.h>
#include <qlineedit.h>
#include <QPalette>
#include <QVBoxLayout> 
#include <QHBoxLayout>
#include <vector>
#include "linked_list.h"
#include "cell.h"
#include "right_click.h"
#include "game_logic.h"
#include "make_map.h"

//"https://www.flaticon.com/kr/free-icons/"  mine productor  Freepik 
//"https://www.flaticon.com/kr/free-icons/-" flag productor Pixel perfect

class MineswpeerGui : public QMainWindow, public EventListener
{
    Q_OBJECT

private:
    int row_size = 0;
    int column_size = 0;
    int mine_num = 0;
    int flag_num = 0;

    QWidget* mainWindow = nullptr;
    QGridLayout* gridLayout = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    QHBoxLayout* horizontalLayout = nullptr;
    QHBoxLayout* horizontalLayoutRow = nullptr;
    QHBoxLayout* horizontalLayoutCol = nullptr;
    QHBoxLayout* horizontalLayoutMine = nullptr;
    //start ui
    QLineEdit* row_input = nullptr;
    QLineEdit* col_input = nullptr;
    QLineEdit* mine_input = nullptr;
    QPushButton* start_button = nullptr;
    QLabel* row_label = nullptr;
    QLabel* column_label = nullptr;
    QLabel* mine_label = nullptr;
    QLabel* row_error_label = nullptr;
    QLabel* column_error_label = nullptr;
    QLabel* mine_error_label = nullptr;
    QLabel* game_over_label = nullptr;
    QLabel* mine_num_label = nullptr;
    QLabel* flag_num_label = nullptr;
    QPushButton* restart_button = nullptr;


    std::vector<QPushButton*> buttons;

    DLIST::DbLinkedList* map_list = nullptr;
    LOGIC::Logic* logic = nullptr;

public:
    MAP::Map* map = nullptr;
    void onEventOccurred(int row, int column) override {
        qDebug() << "row: " << row << "column: " << column;
        this->ButtonHide(this->FindButton(row, column));
    }

    MineswpeerGui(QWidget* parent, DLIST::DbLinkedList* map_list);
    ~MineswpeerGui();
    void InitMember(int row_size, int column_size, int mine_num);
    int ReturnRowSize();
    int ReturnColumnSize();
    int ReturnMineSize();
    void InitGame();
    void StartGame();
    void MakeMap();
    void onRightClicked();
    void ButtonClicked();
    void ButtonHide(QPushButton* button);
    void GameOver();
    void ReStartGame();
    void GameClear();
    QPushButton* FindButton(int row_size, int column_size);
    void AdjustWindowSize(int button_size, int spacing);
};