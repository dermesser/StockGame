#include <stockpricehistoryplot.h>

StockPriceHistoryPlot::StockPriceHistoryPlot(QWidget *parent) :
    QCustomPlot(parent)
{
}

void StockPriceHistoryPlot::initCompany(int mx, double my)
{
    i = 0;
    xmax = mx;
    ymax = my;
    current_price = my/2;
    avg_depot_price = 0;

    generator.setRange(ymax);
    ymax = generator.getRange();

    y.fill(0,xmax+1);
    x.resize(xmax+1);
    avg.fill(0,xmax+1);
    update_limit.fill(0,xmax+1);

    for (int i = 0; i < xmax; i++)
    {
        x[i] = i;
    }

    initPlot();

    return;
}

void StockPriceHistoryPlot::initPlot(void)
{
    this->hide();

    this->removeGraph(0);
    this->removeGraph(1);
    this->removeGraph(2);
    this->addGraph();
    this->addGraph();
    this->addGraph();

    this->xAxis->setRange(0,xmax);
    this->xAxis->setTickLabels(false);
    this->yAxis->setRange(0,ymax);
    this->yAxis->setLabel("Stock Price");

    this->graph(0)->setPen(QPen(Qt::red));
    this->graph(0)->setBrush(QBrush(QColor(255,0,0,30)));
    this->graph(1)->setPen(QPen(Qt::green));
    this->graph(2)->setPen(QPen(Qt::blue));

    this->show();

    return;
}

void StockPriceHistoryPlot::setData(void)
{
    if (i > xmax)
        i = 0;

    update_limit[i] = 0;
    update_limit[(i+1)%xmax] = ymax;

    // Random number calculation

    y[i] = current_price = generator.getPrice();
    i++;

    avg.fill(avg_depot_price,xmax+1);

    this->graph(0)->setData(x,y);
    this->graph(1)->setData(x,avg);
    this->graph(2)->setData(x,update_limit);
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
