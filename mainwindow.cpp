#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(&timer,SIGNAL( timeout() ), ui->mainPlot, SLOT( setData() ));
    QObject::connect(&timer,SIGNAL( timeout() ), &timer, SLOT( start() ));

    QObject::connect(ui->startPlot,SIGNAL( clicked() ),&timer,SLOT( start() ));

    QObject::connect(ui->mainPlot,SIGNAL( priceChanged(int) ), ui->currentPrice, SLOT( display(int) ));

    ui->mainPlot->setRanges(500,50);
    ui->currentPrice->setDigitCount(4);

    timer.setInterval(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}
