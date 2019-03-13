#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include "window.h"

Game::Game(QWidget *parent) : QDialog(parent)
{
    // Set window title and fixed size
    this->setWindowTitle("Tic Tac Toe");
    this->setFixedSize(300, 300);

    // Create the gameboard as a matrix of
    // 9 rects each of 100 x 100 size
    QSize size(100, 100);
    boardRects[0] = QRect(QPoint(0, 0), size);
    boardRects[1] = QRect(QPoint(0, 100), size);
    boardRects[2] = QRect(QPoint(0, 200), size);
    boardRects[3] = QRect(QPoint(100, 0), size);
    boardRects[4] = QRect(QPoint(100, 100), size);
    boardRects[5] = QRect(QPoint(100, 200), size);
    boardRects[6] = QRect(QPoint(200, 0), size);
    boardRects[7] = QRect(QPoint(200, 100), size);
    boardRects[8] = QRect(QPoint(200, 200), size);

}

