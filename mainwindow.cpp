#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qlinechart.h"
#include <QVBoxLayout>
#include <QInputDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVBoxLayout *vBox = new QVBoxLayout;
    m_chart = new QLineChart();
    vBox->addWidget(m_chart);
    ui->centralWidget->setLayout(vBox);
    m_chart->genArray(100);

    m_sorter = new Sorter(m_chart);
    m_sorter->setSlowdown(50);
    UpdateTitle();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_sorter;
}

void MainWindow::on_actionInsertionSort_triggered()
{
    m_sorter->insertionSort();
}

void MainWindow::on_actionSize_triggered()
{
    bool ok;
    int num = QInputDialog::getInt(this, "Input Array Size", "Array Size:", m_chart->getArray().size(),
                                   1, m_chart->width(), 1, &ok);
    if (ok){
        m_chart->genArray(num);
        UpdateTitle();
    }
}

void MainWindow::on_actionSlowdown_triggered()
{
    bool ok;
    int num = QInputDialog::getInt(this, "Input Slowdown", "Slowdown:", m_sorter->getSlowdown(),
                                   1, 1000, 1, &ok);
    if (ok){
        m_sorter->setSlowdown(num);
        UpdateTitle();
    }
}

inline void MainWindow::UpdateTitle(){
    QString size, slowdown;
    size.setNum(m_chart->getArray().size());
    slowdown.setNum(m_sorter->getSlowdown());
    setWindowTitle("size: " + size + " slowdown:" + slowdown);
}

void MainWindow::on_actionStop_triggered()
{
    m_sorter->stop();
}

void MainWindow::on_actionSelectionSort_triggered()
{
    m_sorter->selectionSort();
}

void MainWindow::on_actionMergeSort_triggered()
{
    m_sorter->mergeSort();
}

void MainWindow::on_actionBubleSort_triggered()
{
    m_sorter->bubleSort();
}

void MainWindow::on_actionShellSort_triggered()
{
    m_sorter->shellSort();
}

void MainWindow::on_actionHeapSort_triggered()
{
    m_sorter->heapSort();
}

void MainWindow::on_actionQuickSort_triggered()
{
    m_sorter->quickSort();
}
