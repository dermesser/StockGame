#include "mainwindow.h"
#include "ui_mainwindow.h"

MoneyAvailable deposit;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(&deposit,SIGNAL(moneyChanged(int)),ui->lcdMoney,SLOT(display(int)));

    deposit.changeMoney(10000);
}

MainWindow::~MainWindow()
{
    delete ui;
}
