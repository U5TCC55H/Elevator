#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->rotate(180);
    ui->graphicsView->setSceneRect(0, 0, 991, 621); // 旋转视口
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timer.setInterval(1.0 / Config::RedrawFreq * 1000);
    QObject::connect(&timer, SIGNAL(timeout()),
                     this, SLOT(onTimeout()));
    QObject::connect(ui->horizontalSliderSpeed, SIGNAL(valueChanged(int)),
                     this, SLOT(onSpeedChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSimulation(Simulation &s) {
    this->sim = &s;
    QObject::connect(ui->pushButtonSwitch, SIGNAL(clicked(bool)),
                     this, SLOT(switchState()));
    floorHeight = ui->graphicsView->geometry().height() / (float)Config::NumFloors;
    initDraw();
}

void MainWindow::switchState() {
    sim->switchState();
    sim->isSimulating()? timer.start(): timer.stop();
}

void MainWindow::onTimeout() {
    timer.start();
    reDraw();
}

void MainWindow::onSpeedChanged(int s) {
    sim->setSpeed(s);
}

void MainWindow::initDraw() {
    for (int i = 0; i < Config::NumFloors; ++i) {
        scene.addRect(0,
                      floorHeight * i,
                      ui->graphicsView->geometry().width(),
                      ui->graphicsView->geometry().height() / 50.0);
        floors[i] = scene.addText("0", QFont("Arial", 20));
        floors[i]->setX(ui->graphicsView->geometry().width() * 0.618);
        floors[i]->setY(floorHeight * i + floorHeight * 0.5);
        floors[i]->setRotation(180);
    }
    elevator = scene.addRect(0,
                             floorHeight * sim->getElevatorPosition(),
                             ui->graphicsView->geometry().width() / 8.0,
                             floorHeight);
    elevatorText = scene.addText("0", QFont("Arial", 20));
    elevatorText->setX(ui->graphicsView->geometry().width() / 8.0 * 0.6);
    elevatorText->setY(floorHeight * sim->getElevatorPosition() +
                       floorHeight * 0.5);
    elevatorText->setRotation(180);

    ui->lineEdit->setText(QString::number(sim->getNumQueued()));
    ui->lineEdit_2->setText(QString::number(sim->getNumQueuing()));
    ui->lineEdit_3->setText(QString::number(sim->getNumServed()));
    ui->lineEdit_4->setText(QString::number(sim->getNumResigned()));
    ui->lineEdit_5->setText("N/A");
}

void MainWindow::reDraw() {
    elevator->setRect(0,
                      floorHeight * sim->getElevatorPosition(),
                      ui->graphicsView->geometry().width() / 8.0,
                      floorHeight);
    elevatorText->setY(floorHeight * sim->getElevatorPosition() +
                       floorHeight * 0.5);
    elevatorText->setPlainText(QString::number(sim->getNumPersonE()));
    for (int i = 0; i < Config::NumFloors; ++i) {
        floors[i]->setPlainText(QString::number(sim->getNumPerson(i)));
    }
    ui->lineEdit->setText(QString::number(sim->getNumQueued()));
    ui->lineEdit_2->setText(QString::number(sim->getNumQueuing()));
    ui->lineEdit_3->setText(QString::number(sim->getNumServed()));
    ui->lineEdit_4->setText(QString::number(sim->getNumResigned()));
    ui->lineEdit_5->setText(QString::number(sim->getAvgWaitTime()));
    scene.update();
}
