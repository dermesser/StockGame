#ifndef SINGLESTOCK_H
#define SINGLESTOCK_H

#include <QWidget>
#include "stockpricehistoryplot.h"
#include <QTimer>

namespace Ui {
class SingleStock;
}

class SingleStock : public QWidget
{
    Q_OBJECT

public:
    explicit SingleStock(QWidget *parent = 0);
    ~SingleStock();

    int buy_step;

public slots:
    void buyStock();
    void sellStock();
private slots:
    void changeBuyStep(int);

private:
    Ui::SingleStock *ui;

    QTimer timer;

    int stocks_in_depot;
    double total_value;
};

#endif // SINGLESTOCK_H
