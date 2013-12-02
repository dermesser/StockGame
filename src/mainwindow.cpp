#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <iostream>

MoneyAvailable deposit;
QTimer main_timer;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdMoney->hide();
    ui->initialMoney->setValue(default_initial_money);

    deposit.changeMoney(default_initial_money);

    QObject::connect(&deposit,SIGNAL( moneyChanged(int) ),ui->lcdMoney,SLOT(display(int)));
    QObject::connect(ui->startButton,SIGNAL( clicked() ),this,SLOT( startGame() ));
    QObject::connect(&reseed_timer,SIGNAL( timeout() ),this,SLOT( seed() ));

    reseed_timer.setSingleShot(false);
    reseed_timer.setInterval(5e3);

    seed();

    reseed_timer.start();

    main_timer.setSingleShot(false);
    main_timer.setInterval(main_timer_interval);
}

void MainWindow::seed(void)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());

    //std::cout << "Reseed: " << QDateTime::currentMSecsSinceEpoch() << "\n";
    return;
}

void MainWindow::startGame(void)
{
    deposit.changeMoney(ui->initialMoney->value());
    ui->initialMoney->hide();
    ui->lcdMoney->show();

    ui->startButton->setText("Pause");
    QObject::disconnect(ui->startButton,SIGNAL( clicked() ),this,SLOT( startGame() ));
    QObject::connect(ui->startButton,SIGNAL( clicked() ),this,SLOT( pauseGame() ));

    main_timer.start();

    return;
}

void MainWindow::pauseGame(void)
{
    main_timer.stop();

    ui->startButton->setText("Continue");

    QObject::disconnect(ui->startButton,SIGNAL( clicked() ),this,SLOT( pauseGame() ));
    QObject::connect(ui->startButton,SIGNAL( clicked() ),this,SLOT( continueGame() ));

}


void MainWindow::continueGame(void)
{
    main_timer.start();
    ui->startButton->setText("Pause");
    QObject::disconnect(ui->startButton,SIGNAL( clicked() ),this,SLOT( continueGame() ));
    QObject::connect(ui->startButton,SIGNAL( clicked() ),this,SLOT( pauseGame() ));
}

MainWindow::~MainWindow()
{
    if ( deposit.getMoney() - default_initial_money > 0 )
        std::cout << "Congratulations! You earned " << deposit.getMoney() - default_initial_money << " units of liquid capital!\n";
    else if ( deposit.getMoney() - default_initial_money == 0)
    {}
    else
        std::cout << "Congratulations! You lost " << ((-1) * (deposit.getMoney() - default_initial_money)) << " units of liquid capital!\n";

    delete ui;
}

