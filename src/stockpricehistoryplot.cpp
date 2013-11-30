#include <stockpricehistoryplot.h>

StockPriceHistoryPlot::StockPriceHistoryPlot(QWidget *parent) :
    QCustomPlot(parent),
    y(1001,0), x(1001),
    i(0), xmax(1000),
    ymax(100), current_price(50)
{
    setRanges(xmax,ymax);
}

void StockPriceHistoryPlot::setRanges(int mx, double my)
{
    i = 0;
    xmax = mx;
    ymax = my;
    current_price = my/2;

    QVector<double> ny(xmax+1), nx(xmax+1);

    y = ny;
    x = nx;

    for (int i = 0; i < xmax; i++)
        x[i] = i;

    initPlot();

    return;
}

void StockPriceHistoryPlot::initPlot(void)
{
// We only have a single graph here (id 0).
    this->removeGraph(0);
    this->addGraph();

    this->xAxis->setRange(0,xmax);
    this->xAxis->setTickLabels(false);
    this->yAxis->setRange(0,ymax);
    this->yAxis->setLabel("Stock Price/EUR");

    this->graph(0)->setPen(QPen(Qt::red));

    this->show();

    return;
}

double getNewValue(double);

void StockPriceHistoryPlot::setData(void)
{
    if (i > xmax)
        i = 0;

    // Clamp graph to the ground (before replotting it; gives a nicer limit between new and old)
    y[(i+1)%xmax] = 0;
    y[(i+2)%xmax] = ymax;

    // Random number calculation

    y[i] = current_price = getNewValue(current_price);
    i++;

    this->graph(0)->setData(x,y);
    this->replot();

    emit priceChanged(current_price);
    if ( current_price < 0.02 * ymax )
        emit bankrupt();

    return;
}

double getDivisor(void)
{
    return 1 + (qrand() % 5);
}

double StockPriceHistoryPlot::getNewValue(double value)
{
    int threshold = 0.05 * ymax;

    if ( value < threshold )
        value += ((qrand() % 10) - 3)/getDivisor();
    else if ( value > (ymax - threshold) )
        value += ((qrand() % 10) - 7)/getDivisor();
    else value += ((qrand() % 10) - 4.5)/getDivisor();

    return value;
}

double StockPriceHistoryPlot::getPrice(void)
{
    return current_price;
}
