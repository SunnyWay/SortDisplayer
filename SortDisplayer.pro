#-------------------------------------------------
#
# Project created by QtCreator 2014-04-06T16:28:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SortDisplayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qlinechart.cpp \
    sorter.cpp

HEADERS  += mainwindow.h \
    qlinechart.h \
    sorter.h

FORMS    += mainwindow.ui
