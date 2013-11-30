#ifndef STOCKPRICEHISTORYPLOT_H
#define STOCKPRICEHISTORYPLOT_H

#include <QVector>
#include <qcustomplot.h>
#include <localpricegen.h>

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

    void setRanges(int xmax = 1000, double ymax = 100);

    double getPrice(void);

signals:
    void priceChanged(int);
    void bankrupt(void);

public slots:
    void setData();

private:
    void initPlot(void);

    // this should be a member of the GenericPriceGenerator class so the same
    // functions can be used!
    LocalPriceGen generator;

    QVector<double> y,x;
    int i, xmax, ymax;
    int current_price;

};

#endif // STOCKPRICEHISTORYPLOT_H
