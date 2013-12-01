#-------------------------------------------------
#
# Project created by QtCreator 2013-11-30T12:14:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stocktrader
TEMPLATE = app


SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/qcustomplot.cpp \
    src/stockpricehistoryplot.cpp \
    src/singlestock.cpp \
    src/moneyavailable.cpp \
    src/localpricegen.cpp \
    src/genericpricegenerator.cpp

HEADERS  +=\
    header/mainwindow.h \
    header/qcustomplot.h \
    header/stockpricehistoryplot.h \
    header/singlestock.h \
    header/moneyavailable.h \
    header/localpricegen.h \
    header/genericpricegenerator.h

FORMS    += mainwindow.ui \
    singlestock.ui

OTHER_FILES += \
    LICENSE.txt

INCLUDEPATH += header/
