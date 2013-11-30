#include "singlestock.h"
#include "ui_singlestock.h"
#include "mainwindow.h"

SingleStock::SingleStock(QWidget *parent) :
    QWidget(parent),
    buy_step(1),
    ui(new Ui::SingleStock),
    stocks_in_depot(0), total_value(0)
{
    ui->setupUi(this);

    ui->plot->setRanges(500,100);

    QObject::connect(ui->plot,SIGNAL( priceChanged(int) ),ui->lcdPrice,SLOT( display(int) ));
    QObject::connect(&timer,SIGNAL( timeout() ),ui->plot,SLOT( setData()));
    QObject::connect(&timer,SIGNAL( timeout() ),&timer,SLOT( start() ));
    QObject::connect(ui->buyButton,SIGNAL( clicked() ),this,SLOT( buyStock() ));
    QObject::connect(ui->sellButton,SIGNAL( clicked() ),this,SLOT( sellStock() ));

    timer.setInterval(50);
    timer.start();
}

void SingleStock::buyStock(void)
{
    double current_price = ui->plot->getPrice();
    double order_volume = buy_step * current_price;

    stocks_in_depot += buy_step;

    deposit.changeMoney(deposit.getMoney()-order_volume);

    total_value += order_volume;

    ui->lcdStocks->display(ui->lcdStocks->intValue() + buy_step);

    return;
}

void SingleStock::sellStock(void)
{
    if (stocks_in_depot <= 0)
        return;

    double current_price = ui->plot->getPrice();
    double order_volume = buy_step * current_price;

    stocks_in_depot -= buy_step;

    total_value -= buy_step * (total_value/stocks_in_depot);

    deposit.changeMoney(deposit.getMoney()+order_volume);

    ui->lcdStocks->display(ui->lcdStocks->intValue() - buy_step);

    return;
}

SingleStock::~SingleStock()
{
    delete ui;
}
