#include "right_click.h"

QRightClickButton::QRightClickButton(QWidget* parent) :
    QPushButton(parent)
{
}

void QRightClickButton::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::RightButton) {
        qDebug() << "Right button pressed!";
        emit rightClicked(); 
    }
    QPushButton::mousePressEvent(e);
    
}