#ifndef COMPANY_H
#define COMPANY_H

#include <QObject>
#include <localpricegen.h>

/*
 * Just again a quite misleading name: This class represents the price
 * of a company along with its representation in the user's depot.
 */
class Company : public QObject
{
    Q_OBJECT
public:
    explicit Company(QObject *parent = 0);

    void initCompany(double ymax = 100);

    double getPrice(void);
    void recalcAvg(void);
    void buy(int);
    void sell(int);

signals:
    void priceChanged(int);
    void bankrupt(void);
    void splitted(void);

public slots:
    double updatePrice(void);
    void split(void);

private:
    LocalPriceGen price_generator;

    double current_price;
    int shares_in_depot;
    double total_value;
    double avg_depot_price;
    int ymax;
    bool is_bankrupt;

    friend class StockPriceHistoryPlot;
    friend class SingleStock;
};

#endif // COMPANY_H
