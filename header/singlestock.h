#ifndef SINGLESTOCK_H
#define SINGLESTOCK_H

#include <QWidget>
#include <QTimer>

#include <stockpricehistoryplot.h>

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
    void bankrupt();

private:
    Ui::SingleStock *ui;

    void updateAvgLine(void);

    int shares_in_depot;
    double total_value;
};

#endif // SINGLESTOCK_H
