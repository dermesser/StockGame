#ifndef STOCKPRICEHISTORYPLOT_H
#define STOCKPRICEHISTORYPLOT_H

#include <QVector>
#include "qcustomplot.h"

class StockPriceHistoryPlot : public QCustomPlot
{
    Q_OBJECT
public:
    explicit StockPriceHistoryPlot(QWidget *parent = 0);

    void setRanges(int xmax = 1000, double ymax = 100);


signals:
    void priceChanged(int);

public slots:
    void setData();

private:
    void initPlot(void);
    double getNewValue(double);

    QVector<double> y,x;
    int i, xmax;
    double ymax, current_value;

};

#endif // STOCKPRICEHISTORYPLOT_H
