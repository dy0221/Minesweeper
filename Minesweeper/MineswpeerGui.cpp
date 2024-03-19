#include "MineswpeerGui.h"

MineswpeerGui::MineswpeerGui(QWidget* parent, DLIST::DbLinkedList* map_list)
    : QMainWindow(parent)
{
    mainWindow = new QWidget(this);
    this->setWindowIcon(QIcon(":/new/prefix1/image/mine.ico"));
    setCentralWidget(mainWindow);
    mainWindow->setStyleSheet("background-color: #E4E4E5;");
    this->setFixedSize(400, 300);
    this->resize(400, 300);
    mainLayout = new QVBoxLayout(mainWindow);

    this->map_list = map_list;
    this->InitMember(0, 0, 0);
    this->InitGame();

}

MineswpeerGui::~MineswpeerGui()
{}

int MineswpeerGui::ReturnRowSize() {
    return row_size;
}

int MineswpeerGui::ReturnColumnSize() {
    return column_size;
}

int MineswpeerGui::ReturnMineSize() {
    return mine_num;
}

void MineswpeerGui::InitMember(int row_size, int column_size, int mine_num) {
    this->row_size = row_size;
    this->column_size = column_size;
    this->mine_num = mine_num;
}

void MineswpeerGui::InitGame() {

    row_input = new QLineEdit(mainWindow);
    col_input = new QLineEdit(mainWindow);
    mine_input = new QLineEdit(mainWindow);
    start_button = new QPushButton("game start\n", mainWindow);

  
    row_label = new QLabel("row", mainWindow);
    column_label = new QLabel("column", mainWindow);
    mine_label = new QLabel("mine", mainWindow);

    row_error_label = new QLabel("", mainWindow);
    column_error_label = new QLabel("", mainWindow);
    mine_error_label = new QLabel("", mainWindow);

    row_error_label->setStyleSheet("color: red");
    column_error_label->setStyleSheet("color: red");
    mine_error_label->setStyleSheet("color: red");

    horizontalLayoutRow = new QHBoxLayout(mainWindow);
    horizontalLayoutCol = new QHBoxLayout(mainWindow);
    horizontalLayoutMine = new QHBoxLayout(mainWindow);

    horizontalLayoutRow->addWidget(row_label);
    horizontalLayoutRow->addWidget(row_error_label);
    horizontalLayoutCol->addWidget(column_label);
    horizontalLayoutCol->addWidget(column_error_label);
    horizontalLayoutMine->addWidget(mine_label);
    horizontalLayoutMine->addWidget(mine_error_label);

    mainLayout->addLayout(horizontalLayoutRow);
    mainLayout->addWidget(row_input);
    mainLayout->addLayout(horizontalLayoutCol);
    mainLayout->addWidget(col_input);
    mainLayout->addLayout(horizontalLayoutMine);
    mainLayout->addWidget(mine_input);
    mainLayout->addWidget(start_button);

    connect(start_button, &QPushButton::clicked, this, &MineswpeerGui::StartGame);
}

void MineswpeerGui::StartGame() {
    bool ok;
    bool error1 = true, error2 = true, error3 = true;
    row_error_label->setText("");
    column_error_label->setText("");
    mine_error_label->setText("");

    row_size = row_input->text().toInt(&ok);
    if (!ok || row_size <= 0) {
        row_error_label->setText("row error!");
        error1 = false;
    }
    column_size = col_input->text().toInt(&ok);
    if (!ok || column_size <= 0) {
        column_error_label->setText("column error!");
        error2 = false;
    }
    mine_num = mine_input->text().toInt(&ok);
    if (!ok || mine_num <= 0 || mine_num >= row_size * column_size) {
        mine_error_label->setText("mine error!");
        error3 = false;;
    }

    if (!error1 || !error2 || !error3) {
        return;
    }

    delete row_input;
    delete col_input;
    delete mine_input;
    delete row_label;
    delete column_label;
    delete mine_label;
    delete start_button;
    delete row_error_label;
    delete column_error_label;
    delete mine_error_label;
    delete horizontalLayoutRow;
    delete horizontalLayoutCol;
    delete horizontalLayoutMine;

    gridLayout = new QGridLayout(mainWindow);
    mainLayout->addLayout(gridLayout);

    map = new MAP::Map(map_list, ReturnRowSize(), ReturnColumnSize(), ReturnMineSize());

    logic = new LOGIC::Logic(map_list, map);
    logic->setEventListener(this);
    this->MakeMap();
}

void MineswpeerGui::MakeMap() {
    gridLayout->setSpacing(1);

    logic->MakeMap();

    int button_size = 37;

    for (int row = 1; row <= row_size; row++) {
        for (int col = 1; col <= column_size; col++) {
            QRightClickButton* button = new QRightClickButton(mainWindow);
            button->setStyleSheet("QPushButton {"
                "background-color: #949494;"
                "}"
                "QPushButton:hover {"          
                "background-color: #808080;"
                "}");
            button->setFixedSize(button_size, button_size);
            gridLayout->addWidget(button, row, col);
            buttons.push_back(button);

            button->setProperty("row", row);
            button->setProperty("col", col);

            CELL::Cell* cell = this->map_list->GetData((row - 1) * column_size + col);

            connect(button, &QRightClickButton::rightClicked, this, &MineswpeerGui::onRightClicked);
            connect(button, &QPushButton::clicked, this, &MineswpeerGui::ButtonClicked);

        }
    }
    horizontalLayout = new QHBoxLayout(mainWindow);

    mine_num_label = new QLabel(QString("Mines: %1").arg(mine_num), mainWindow);
    flag_num_label = new QLabel(QString("Flags: %1").arg(flag_num), mainWindow);
    restart_button = new QPushButton("Restart", mainWindow);

    horizontalLayout->addWidget(mine_num_label);
    horizontalLayout->addWidget(flag_num_label);
    horizontalLayout->addWidget(restart_button);

    mainLayout->addLayout(horizontalLayout);

    connect(restart_button, &QPushButton::clicked, this, &MineswpeerGui::ReStartGame);

    this->AdjustWindowSize(37, 3);
}

void MineswpeerGui::onRightClicked()
{
    QRightClickButton* button = qobject_cast<QRightClickButton*>(sender());
    QString iconPath = ":/new/prefix1/image/flag.png";

    int row = button->property("row").toInt();
    int col = button->property("col").toInt();

    CELL::Cell* cell = this->map_list->GetData((row - 1) * column_size + col);
    if (cell->IsFlagged()) {
        button->setIcon(QIcon());
        cell->SetUnFlaged();
        this->flag_num--;
    }
    else {
        QIcon icon(iconPath);
        button->setIcon(icon);
        cell->SetFlaged();
        this->flag_num++;
    }
    flag_num_label->setText(QString("Flags: %1").arg(this->flag_num));
}

void MineswpeerGui::ButtonClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    int row = button->property("row").toInt();
    int col = button->property("col").toInt();
    qDebug() << "click" << " row: " << row << " col: " << col;
    CELL::Cell* cell = this->map_list->GetData((row - 1) * column_size + col);
    if (cell->IsFlagged()) {
        return;
    }
    if (logic->GameOver(row, col)) {
        this->GameOver();
    }

    logic->DFS(row, col);

    if (logic->GameClear()) {
        this->GameClear();
    }
}

void MineswpeerGui::ButtonHide(QPushButton* button) {
    int row = button->property("row").toInt();
    int col = button->property("col").toInt();
    CELL::Cell* cell = this->map_list->GetData((row - 1) * column_size + col);

    int cell_size = 37;

    button->hide();

    QLabel* label = new QLabel("", mainWindow);
    label->setFixedSize(cell_size, cell_size);
    label->setAlignment(Qt::AlignCenter);

    QFont font = label->font();
    font.setPointSize(cell_size * 0.4); 
    label->setFont(font);

    if (cell->IsMined()) {
        QString iconPath = ":/new/prefix1/image/mine.png";
        QPixmap iconPixmap(iconPath);
        QPixmap scaledPixmap = iconPixmap.scaled(QSize(cell_size, cell_size));
        label->setPixmap(scaledPixmap);
        label->setStyleSheet("background-color: #F05650;");
        gridLayout->addWidget(label, row, col);
        return;
    }

    if (cell->NumNeighborMinesCount() == 1) {
        label->setStyleSheet("color: blue");
        label->setText("1");
    }
    else if (cell->NumNeighborMinesCount() == 2) {
        label->setStyleSheet("color: green");
        label->setText("2");
    }
    else if (cell->NumNeighborMinesCount() == 3) {
        label->setStyleSheet("color: red");
        label->setText("3");
    }
    else if (cell->NumNeighborMinesCount() == 4) {
        label->setStyleSheet("color: purple");
        label->setText("4");
    }
    else if (cell->NumNeighborMinesCount() == 5) {
        label->setStyleSheet("color: brown");
        label->setText("5");
    }
    else if (cell->NumNeighborMinesCount() == 6) {
        label->setStyleSheet("color: gray");
        label->setText("6");
    }
    else if (cell->NumNeighborMinesCount() == 7) {
        label->setStyleSheet("color: magenta");
        label->setText("7");
    }
    else if (cell->NumNeighborMinesCount() == 8) {
        label->setText("8");

    }
    gridLayout->addWidget(label, row, col);

}

QPushButton* MineswpeerGui::FindButton(int row, int col) {
    for (QPushButton* button : buttons) {
        if (button->property("row").toInt() == row && button->property("col").toInt() == col) {
            return button;
        }
    }
    return nullptr;
}

void MineswpeerGui::GameOver() {
    int count_row = 0;
    int count_colum = 0;

    for (int i = 1; i <= row_size * column_size; i++) {

        CELL::Cell* cell = this->map_list->GetData(i);

        if ((i % column_size) == 1) {
            count_row++;
        }
        count_colum = (i - 1) % column_size + 1;
        if (cell->IsMined()) {
            qDebug() << " count_row: " << count_row << " count_colum: " << count_colum;
            this->ButtonHide(this->FindButton(count_row, count_colum));
        }
        QPushButton* button = this->FindButton(count_row, count_colum);
        button->setDisabled(true);
    }

}

void MineswpeerGui::ReStartGame() {

    delete map;
    delete logic;
    delete mainWindow;
    this->flag_num = 0;
    buttons.clear();

    mainWindow = new QWidget(this);
    setCentralWidget(mainWindow);
    mainWindow->setStyleSheet("background-color: #E4E4E5;");
    mainWindow->resize(800, 600);
    mainLayout = new QVBoxLayout(mainWindow);
    
    this->setFixedSize(400, 300);
    this->resize(400, 300);
    
    this->InitMember(0, 0, 0);
    this->InitGame();
}  

void MineswpeerGui::GameClear() {
    int count_row = 0;
    int count_colum = 0;

    for (int i = 1; i <= row_size * column_size; i++) {
        if ((i % column_size) == 1) {
            count_row++;
        }
        count_colum = (i - 1) % column_size + 1;

        QPushButton* button = this->FindButton(count_row, count_colum);
        button->setDisabled(true);
    }
    mainWindow->setStyleSheet("background-color: #A0D468;");
}

void MineswpeerGui::AdjustWindowSize(int button_size, int spacing) {
    int totalWidth = column_size * (button_size + spacing) + spacing;
    int totalHeight = row_size * (button_size + spacing) + spacing;

    totalHeight += 50; 

    this->setFixedSize(totalWidth, totalHeight);
    this->resize(totalWidth, totalHeight);
}