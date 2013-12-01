#include <mainwindow.h>
#include <ui_mainwindow.h>

MoneyAvailable deposit;
QTimer main_timer;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdMoney->hide();
    ui->initialMoney->setValue(default_initial_money);

    QObject::connect(&deposit,SIGNAL( moneyChanged(int) ),ui->lcdMoney,SLOT(display(int)));
    QObject::connect(ui->startButton,SIGNAL( clicked() ),this,SLOT( startGame() ));
    QObject::connect(&reseed_timer,SIGNAL( timeout() ),this,SLOT( seed() ));

    reseed_timer.setSingleShot(false);
    reseed_timer.setInterval(5e3);

    main_timer.setSingleShot(false);
    main_timer.setInterval(main_timer_interval);
}

void MainWindow::seed(void)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());

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
    delete ui;
}
