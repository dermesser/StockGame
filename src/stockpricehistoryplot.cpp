#include <stockpricehistoryplot.h>

StockPriceHistoryPlot::StockPriceHistoryPlot(QWidget *parent) :
    QCustomPlot(parent),
    y(1001,0), x(1001), avg(1001,0),
    i(0), xmax(1000),
    ymax(100), current_price(50), avg_depot_price(0)
{
    initCompany(xmax,ymax);
}

void StockPriceHistoryPlot::initCompany(int mx, double my)
{
    i = 0;
    xmax = mx;
    ymax = my;
    current_price = my/2;

    generator.setRange(ymax);
    ymax = generator.getRange();

    QVector<double> ny(xmax+1), nx(xmax+1), na(xmax+1);

    y = ny;
    x = nx;
    avg = na;

    for (int i = 0; i < xmax; i++)
        x[i] = i;

    initPlot();

    return;
}

void StockPriceHistoryPlot::initPlot(void)
{
    this->removeGraph(0);
    this->removeGraph(1);
    this->addGraph();
    this->addGraph();

    this->xAxis->setRange(0,xmax);
    this->xAxis->setTickLabels(false);
    this->yAxis->setRange(0,ymax);
    this->yAxis->setLabel("Stock Price/EUR");

    this->graph(0)->setPen(QPen(Qt::red));
    this->graph(1)->setPen(QPen(Qt::green));

    this->show();

    return;
}

void StockPriceHistoryPlot::setData(void)
{
    if (i > xmax)
        i = 0;

    // Clamp graph to the ground (before replotting it; gives a nicer limit between new and old)
    y[(i+1)%xmax] = 0;
    y[(i+2)%xmax] = ymax;

    // Random number calculation

    y[i] = current_price = generator.getPrice();
    i++;

    avg.fill(avg_depot_price,xmax+1);

    this->graph(0)->setData(x,y);
    this->graph(1)->setData(x,avg);
    this->replot();

    emit priceChanged(current_price);
    if ( current_price < 0.02 * ymax )
        emit bankrupt();

    return;
}

double StockPriceHistoryPlot::getPrice(void)
{
    return current_price;
}