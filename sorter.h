#ifndef SORTER_H
#define SORTER_H
#include "qlinechart.h"
#include <QElapsedTimer>

class Sorter
{
public:
    Sorter(QLineChart* chart):m_chart(chart){}
    void stop(){m_interrupt = true;}
    void setSlowdown(qint64 slowdown){m_slowdown = slowdown;}
    qint64 getSlowdown(){return m_slowdown;}
    void insertionSort();
    void selectionSort();
    void mergeSort();
    void bubleSort();
    void shellSort();
    void heapSort();
    void quickSort();

private:
    bool m_interrupt; //打断标识，若置true，排序将在适当的位置停止
    qint64 m_slowdown;  //延迟时间，排序每进行一次操作，停留 m_slowdown 毫秒
    QLineChart *m_chart;  //显示排序过程的 UI

    void goAway(qint64 ms);
    void swap(QVector<int>& array, int idx_a, int idx_b);

    //插入排序用到的子函数
    void insertionSort(QVector<int>& array, int left, int right);

    //归并排序用到的子函数
    int merge(QVector<int> &a, QVector<int> &temparray, int left, int mid, int right);
    void mergeSort(QVector<int> &a, QVector<int> &temparray, int left, int right);

    //堆排序用到的子函数
    int perlocateDown(QVector<int> &array, int hole, int lastOne);
    void buildHeap(QVector<int> &array);

    //快速排序用到的子函数
    void median(QVector<int> &array, int left, int right);
    int partition(QVector<int> &array, int left, int right);
    void quickSort(QVector<int>& array, int left, int right);
};

#endif // SORTER_H
