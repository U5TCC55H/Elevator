#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QString>
#include "simulation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setSimulation(Simulation & s);
    ~MainWindow();

public slots:
    void switchState();
    void onTimeout();
    void onSpeedChanged(int s);
private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    Simulation *sim;
    QTimer timer;

    float floorHeight;

    QGraphicsRectItem *elevator;
    QGraphicsTextItem *elevatorText;
    QGraphicsTextItem *floors[Config::NumFloors];

    void initDraw();
    void reDraw();
};

#endif // MAINWINDOW_H
