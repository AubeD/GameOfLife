#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.cpp"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

int countneig(int i,int j, int width, int height, int grille[width][height]){
    int count = 0;
    if (i>0 && j>0){
        count+= grille[i-1][j-1];
    }
    if (i>0 && j<height-1){
        count+= grille[i-1][j+1];
    }
    if (i<width-1 && j>0){
        count+= grille[i+1][j-1];
    }
    if (i<width-1 && j<height-1){
        count+= grille[i+1][j+1];
    }
    if (i>0){
        count+= grille[i-1][j];
    }
    if (j>0){
        count+= grille[i][j-1];
    }
    if (j<height-1){
        count+= grille[i][j+1];
    }
    if (i<width-1){
        count+= grille[i+1][j];
    }
return(count);
}

int apply_rules(int nb_voisins, int state){
    if (nb_voisins<2 && state == 1){
        return 0;
    }
    else if ((nb_voisins == 2 && state == 1) || (nb_voisins == 3 && state == 1)){
        return 1;
    }
    else if (nb_voisins > 3 && state == 1){
        return 0;
    }
    else if (nb_voisins == 3 && state == 0){
        return 1;
    }
    else{
        return 0;
    }
}

MainWindow::MainWindow(QWidget *parent) : QDialog(parent)
{
    // Set window title and fixed size
    this->setWindowTitle("Jeu de la vie");
    this->setFixedSize(500, 500);

    // Create the gameboard as a matrix of
    // 50*50 rects each of 10 x 10 size
    QSize size(10, 10);
    int width = 50;
    int height = 50;

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            boardRects[i*width+j] = QRect(QPoint(10*i, 10*j), size);
        }
    }

    int grille[50][50];
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; ++j) {
            grille[i][j] = 0;
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e, int grille[50][50])
{
    painter = new QPainter(this);

    painter->fillRect(this->rect(), QColor(186, 168, 210));

    QPen borderPen(Qt::yellow);
    borderPen.setWidth(4);

    painter->setPen(borderPen);
    painter->drawRects(boardRects, 2500);

    for(int i = 0; i < 50; i++)
    {
        for(int j = 0; j < 50; j++){
            if (grille[i][j] == 0)
            {
                painter->fillRect(boardRects[50*i+j], QColor(0,0,0));
            }
            else {
                painter->fillRect(boardRects[50*i+j], QColor(255, 255, 255));
            }
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e, int grille[50][50])
{
    for(int i = 0; i < 50; i++)
    {
        for(int j = 0; j < 50; j++){
            if(boardRects[50*i+j].contains(e->pos()) && grille[i][j] == 0){
                grille[i][j] = 1;
            }
            else if(boardRects[50*i+j].contains(e->pos()) && grille[i][j] == 0){
                grille[i][j] = 0;
            }
        }
    }
}

