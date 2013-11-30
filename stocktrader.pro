#-------------------------------------------------
#
# Project created by QtCreator 2013-11-30T12:14:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stocktrader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    stockpricehistoryplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    stockpricehistoryplot.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    LICENSE.txt
