#ifndef STOCKPRICEHISTORYPLOT_H
#define STOCKPRICEHISTORYPLOT_H

#include <QVector>
#include <qcustomplot.h>
#include <company.h>

/* This class does not only display the history of the stock price,
   but also looks for bankrupcy and price changes.

   The current price is fetched from a price generator, e.g. LocalPriceGen
   but maybe also some multi-player network price generator.
*/
class StockPriceHistoryPlot : public QCustomPlot
{
    Q_OBJECT
public:
    explicit StockPriceHistoryPlot(QWidget *parent = 0);

    void initCompanyPlot(int xmax = 1000, double ymax = 100);

signals:
    void priceChanged(int);
    void bankrupt(void);

public slots:
    void setData();

private:
    void initPlot(void);

    Company company;

    QVector<double> y,x,avg,update_limit,update_limitx,avgx;
    int i, xmax, ymax;

    friend class SingleStock;
};

#endif // STOCKPRICEHISTORYPLOT_H
