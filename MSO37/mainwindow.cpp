#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "main.cpp"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPushButton>
#include <iostream>
#include <thread>
//#include <mutex>

//using std::mutex;


#define NUM_THREADS 4

//mutex lock1;
//mutex lock2;
//mutex lock3;
//mutex lock4;

//int grille[50][50];

int countneig(int i,int j, int width, int height, int grille[50][50]){
    int count = 0;
//    if (i == 24 || i == 25 || j == 24 || j ==25){
//        if (i == 24 && j<25){
//            lock1.lock();//lock 1
//        }
//        else if(i == 24){
//            lock3.lock();//lock 3
//        }
//        if (i == 25 && j<25){
//            lock2.lock();//lock 2
//        }
//        else if (i == 25){
//            lock4.lock();//lock 4
//        }

//        if (j == 24 && i<25){
//            lock1.lock();//lock 1
//        }
//        else if(j == 24){
//            lock2.lock();//lock 2
//        }
//        if (j == 25 && i<25){
//            lock3.lock();//lock 3
//        }
//        else if (j == 25){
//            lock1.lock();//lock 4
//        }
//    }


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

//    if (i == 24 || i == 25 || j == 24 || j ==25){
//        if (i == 24 && j<25){
//            lock1.unlock();//lock 1
//        }
//        else if(i == 24){
//            lock3.unlock();//lock 3
//        }
//        if (i == 25 && j<25){
//            lock2.unlock();//lock 2
//        }
//        else if (i == 25){
//            lock4.unlock();//lock 4
//        }

//        if (j == 24 && i<25){
//            lock1.unlock();//lock 1
//        }
//        else if(j == 24){
//            lock2.unlock();//lock 2
//        }
//        if (j == 25 && i<25){
//            lock3.unlock();//lock 3
//        }
//        else if (j == 25){
//            lock1.unlock();//lock 4
//        }
//    }
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
    this->setFixedSize(500, 550);

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

    btnStart = new QPushButton("Start", this);
    btnStart->setGeometry(0,500,250,50);
    connect(btnStart,SIGNAL(released()),this,SLOT(start()));


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


void calcul(int debut_i,int debut_j, int ssgrille[25][25], int num_thread, int grilletot[50][50]){

    for(int i = debut_i; i < 25+debut_i; i++){
        for(int j = debut_j; j < 25+debut_j; j++){
            ssgrille[i-debut_i][j-debut_j] =
                    apply_rules(countneig(i,j,50,50,grilletot),ssgrille[i][j]);
        }
    }

    for(int i = debut_i; i < 25+debut_i; i++){
        for(int j = debut_j; j < 25+debut_j; j++){
            grilletot[i][j] =  ssgrille[i-debut_i][j-debut_j];
        }
    }


    // copier le 1/4
}


void MainWindow::start()
{
    //std::thread Ids[NUM_THREADS];


    int ssgrille1[25][25];
    int ssgrille2[25][25];
    int ssgrille3[25][25];
    int ssgrille4[25][25];

    for(int i = 0; i < 25; i++){
        for(int j = 0; j < 25; j++){
            ssgrille1[i][j] = grille[i][j];
            ssgrille2[i][j] = grille[i+25][j];
            ssgrille3[i][j] = grille[i][j+25];
            ssgrille4[i][j] = grille[i+25][j+25];
        }
    }

    std::thread vin(calcul,0,0,ssgrille1, grille);
    std::thread france(calcul,25,0,ssgrille2, grille);
    std::thread baguette(calcul,0,25,ssgrille3, grille);
    std::thread fromage(calcul,25,25,ssgrille4, grille);

    QWidget::update();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    painter = new QPainter(this);
    //std::cout<<"paint";

    painter->fillRect(this->rect(), QColor(186, 168, 210));

    QPen borderPen(Qt::white);
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

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    //std::cout<<"clic";
    for(int i = 0; i < 50; i++)
    {
        for(int j = 0; j < 50; j++){
            if(boardRects[50*i+j].contains(e->pos()) && grille[i][j] == 0){
                grille[i][j] = 1;
            }
            else if(boardRects[50*i+j].contains(e->pos()) && grille[i][j] == 1){
                grille[i][j] = 0;
            }
        }
    }
    QWidget::update();
}

