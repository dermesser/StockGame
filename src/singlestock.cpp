#include <singlestock.h>
#include <ui_singlestock.h>
#include <mainwindow.h>
#include <QTimer>

int xmax = 600;

SingleStock::SingleStock(QWidget *parent) :
    QWidget(parent),
    buy_step(1),
    ui(new Ui::SingleStock),
    shares_in_depot(0), total_value(0),
    isBankrupt(false)
{
    ui->setupUi(this);

    ui->plot->initCompany(xmax,100);

    QObject::connect(ui->plot,SIGNAL( priceChanged(int) ),ui->lcdPrice,SLOT( display(int) ));
    QObject::connect(&main_timer,SIGNAL( timeout() ),ui->plot,SLOT( setData()));
    QObject::connect(ui->buyButton,SIGNAL( clicked() ),this,SLOT( buyStock() ));
    QObject::connect(ui->sellButton,SIGNAL( clicked() ),this,SLOT( sellStock() ));
    QObject::connect(ui->orderStep,SIGNAL( valueChanged(int) ),this,SLOT( changeBuyStep(int) ));

    QObject::connect(ui->plot,SIGNAL( bankrupt() ),this,SLOT( bankrupt() ));

    QPalette Pal;
    Pal.setColor(QPalette::Background,Qt::red);
    ui->lcdPrice->setAutoFillBackground(false);
    ui->lcdPrice->setPalette(Pal);
}

void SingleStock::changeBuyStep(int n)
{
    buy_step = n;

    return;
}

void SingleStock::buyStock(void)
{
    double current_price = ui->plot->getPrice();
    double order_volume = buy_step * current_price;

    if (isBankrupt || ! main_timer.isActive() || deposit.getMoney() - order_volume < 0)
        return;

    shares_in_depot += buy_step;

    deposit.changeMoney(deposit.getMoney()-order_volume);

    total_value += order_volume;

    ui->lcdStocks->display(shares_in_depot);

    updateAvgLine();

    return;
}

void SingleStock::sellStock(void)
{

    if (isBankrupt || ! main_timer.isActive() || shares_in_depot - buy_step < 0)
        return;

    double current_price = ui->plot->getPrice();
    double order_volume = buy_step * current_price;

    total_value -= buy_step * (total_value/shares_in_depot);
    shares_in_depot -= buy_step;

    deposit.changeMoney(deposit.getMoney()+order_volume);

    ui->lcdStocks->display(shares_in_depot);

    updateAvgLine();

    return;
}

void SingleStock::bankrupt(void)
{
    shares_in_depot = 0;
    total_value = 0;

    ui->lcdStocks->display(0);
    ui->lcdPrice->display(0);
    ui->lcdPrice->setAutoFillBackground(true);

    QObject::disconnect(&main_timer,SIGNAL( timeout() ),ui->plot,SLOT( setData()));

    // A QTimer object would be destructed before firing!
    QTimer::singleShot(5000,this,SLOT( reInit()));

    return;
}

void SingleStock::reInit(void)
{
    ui->plot->initCompany(xmax,100);
    ui->lcdPrice->setAutoFillBackground(false);

    QObject::connect(&main_timer,SIGNAL( timeout() ),ui->plot,SLOT( setData()));

    updateAvgLine();

    return;
}

void SingleStock::updateAvgLine(void)
{
    if (shares_in_depot > 0)
        ui->plot->avg_depot_price = total_value / shares_in_depot;
    else ui->plot->avg_depot_price = 0;

    return;
}

SingleStock::~SingleStock()
{
    delete ui;
}
