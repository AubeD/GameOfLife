#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDialog>
#include <QPainter>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPainter *painter;
    QRect boardRects[50*50];

    void paintEvent(QPaintEvent *e, int grille[50][50]);
    void mousePressEvent(QMouseEvent *e, int grille[50][50]);
};

#endif // MAINWINDOW_H
