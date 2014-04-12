#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qlinechart.h"
#include "sorter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QLineChart* getLineChart(){return m_chart;}

private slots:
    void on_actionSize_triggered();

    void on_actionSlowdown_triggered();

    void on_actionStop_triggered();

    void on_actionInsertionSort_triggered();

    void on_actionSelectionSort_triggered();

    void on_actionMergeSort_triggered();

    void on_actionBubleSort_triggered();

    void on_actionShellSort_triggered();

    void on_actionHeapSort_triggered();

    void on_actionQuickSort_triggered();

private:
    void UpdateTitle();
    Ui::MainWindow *ui;
    QLineChart* m_chart;
    Sorter *m_sorter;
};

#endif // MAINWINDOW_H
