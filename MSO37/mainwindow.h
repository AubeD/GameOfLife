#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDialog>
#include <QPainter>
#include <QPushButton>



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
    int grille[50][50];
    QPushButton *btnStart;

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
private slots:
    void start();

};

#endif // MAINWINDOW_H
