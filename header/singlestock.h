#ifndef SINGLESTOCK_H
#define SINGLESTOCK_H

#include <QWidget>
#include <QTimer>

#include <stockpricehistoryplot.h>

namespace Ui {
class SingleStock;
}

/*
 * This is the UI class consisting the Buy/Sell buttons, the price LCDs,
 * the price diagram and the buy step spin box.
 * The company behind the graph is placed in the plot widget (ui->plot)
 */
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
    void bankrupt(void);
    void reInit(void);
    void split(void); // Only updates LCDs

private:
    Ui::SingleStock *ui;

};

#endif // SINGLESTOCK_H
