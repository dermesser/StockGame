#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include <unistd.h>

#include "stockpricehistoryplot.h"
#include "moneyavailable.h"

const int main_timer_interval = 50;
const int default_initial_money = 10000;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void startGame(void);
    void pauseGame(void);
    void continueGame(void);

private slots:

private:
   Ui::MainWindow *ui;

};

extern QTimer main_timer;

#endif // MAINWINDOW_H
