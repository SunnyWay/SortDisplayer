#include "sorter.h"
#include <QCoreApplication>

/*
    停留 ms 毫秒，QCoreApplication::processEvents()可以保持界面响应
*/
void Sorter::goAway(qint64 ms){
    QElapsedTimer t;
    t.start();
    while (t.elapsed() < ms)
        QCoreApplication::processEvents();
}

/*
    交换 array 数组中 idx_a 和 idx_b 处的元素
*/
void Sorter::swap(QVector<int>& array, int idx_a, int idx_b){
    int temp = array[idx_a];
    array[idx_a] = array[idx_b];
    array[idx_b] = temp;
}
//////////////////////////插入排序////////////////////////////////
/*
    插入排序
    将 array 中 [left, right] 区间内的元素进行排序
*/
void Sorter::insertionSort(QVector<int>& array, int left, int right){
    int temp, i, j;
    m_interrupt = false;
    ++right;
    for (i = left+1; i < right; ++i)
    {
        temp = array[i];
        for (j = i-1; j >= left; --j)
        {
            if (temp >= array[j])
                break;
            else{
                array[j+1] = array[j];
                array[j] = 0;  //控制界面显示效果
            }
            goAway(m_slowdown);
            m_chart->update();
            if (m_interrupt){
                array[j] = array[j+1];  //恢复 array[j] = 0
                array[j+1] = temp;
                return ;
            }
        }
        array[j+1] = temp;
        m_chart->update();
    }
}

void Sorter::insertionSort(){
    QVector<int>& array = m_chart->getArray();
    if (array.size() <= 1)
        return ;
    insertionSort(array, 0, array.size()-1);
}

////////////////////////选择排序////////////////////////////////
void Sorter::selectionSort(){
    QVector<int> &array = m_chart->getArray();
    int i, j, min;
    m_interrupt = false;
    for (i = 0; i < array.size(); ++i){
        min = i;
        m_chart->setFirst(min);
        for (j = i+1; j < array.size(); ++j){
            m_chart->setSecond(j);
            if (array[j] < array[min]){
                min = j;
                m_chart->setFirst(min);
            }
            goAway(m_slowdown);
            m_chart->update();
            if (m_interrupt){
                m_chart->resetFlag();
                return ;
            }
        }
        swap(array, i, min);
    }
    m_chart->resetFlag();
    m_chart->update();
}

/////////////////////////归并排序////////////////////////////

void Sorter::mergeSort(){
    QVector<int> &array = m_chart->getArray();
    QVector<int> temparray(array.size());
    m_interrupt = false;
    mergeSort(array, temparray, 0, array.size()-1);
    m_chart->resetFlag();
    m_chart->update();
}

/*
    对 a 数组中 [left, right] 区间内的元素进行归并排序
    temparray 是排序过程中用到的临时数组
*/
void Sorter::mergeSort(QVector<int> &a, QVector<int> &temparray, int left, int right){
    if (left < right){
        int mid = (left+right)/2;
        if (m_interrupt) return;
        mergeSort(a, temparray, left, mid);
        mergeSort(a, temparray, mid+1, right);
        if (merge(a, temparray, left, mid, right) == -1) return ;  //-1 表示 merge()被打断
    }
}

/*
    对 a 数组中 [left, mid] 和 [mid+1, right] 区间中的元素进行归并
    temparray 是归并过程中用到的临时数组
*/
int Sorter::merge(QVector<int> &a, QVector<int> &temparray, int left, int mid, int right){
    int leftpos = left, rightpos = mid+1;
    int i = 0;
    while (leftpos <= mid && rightpos <= right){
        m_chart->setFirst(leftpos);
        m_chart->setSecond(rightpos);
        if (a[leftpos] < a[rightpos]){
            temparray[i++] = a[leftpos++];
        }else
            temparray[i++] = a[rightpos++];
        goAway(m_slowdown);
        m_chart->update();
        if (m_interrupt){
            m_chart->resetFlag();
            return -1;
        }
    }
    while (leftpos <= mid){
        m_chart->setFirst(leftpos);
        temparray[i++] = a[leftpos++];
        goAway(m_slowdown);
        m_chart->update();
        if (m_interrupt){
            m_chart->resetFlag();
            return -1;
        }
    }
    while (rightpos <= right){
        m_chart->setSecond(rightpos);
        temparray[i++] = a[rightpos++];
        goAway(m_slowdown);
        m_chart->update();
        if (m_interrupt){
            m_chart->resetFlag();
            return -1;
        }
    }

    i = 0, leftpos = left;
    while (leftpos <= right){
        a[leftpos++] = temparray[i++];
    }
    m_chart->update();
    return 0;
}

//////////////////////////冒泡排序///////////////////////////////////////

void Sorter::bubleSort(){
    QVector<int> &array = m_chart->getArray();
    m_interrupt = false;
    for (int i = array.size() - 1; i > 0; --i){
        for (int j = 0; j < i; ++j){
            if (array[j] > array[j+1]){
                swap(array, j, j+1);
            }
            goAway(m_slowdown);
            m_chart->update();
            if (m_interrupt)
                return ;
        }
    }
    m_chart->update();
}

////////////////////Shell排序/////////////////////////////////
void Sorter::shellSort(){
    QVector<int> &array = m_chart->getArray();
    int gap, i, j, temp;
    m_interrupt = false;
    for (gap = array.size()/2; gap > 0; gap/=2){
        for (i = gap; i < array.size(); ++i){
            temp = array[i];
            for (j = i; j >= gap && temp < array[j-gap]; j -= gap){
                m_chart->setFirst(j);
                m_chart->setSecond(j-gap);
                array[j] = array[j-gap];
                goAway(m_slowdown);
                m_chart->update();
                if (m_interrupt){
                    m_chart->resetFlag();
                    return ;
                }
            }
            array[j] = temp;
        }
    }
    m_chart->resetFlag();
    m_chart->update();
}

/////////////////////////////堆排序/////////////////////////////////////
/*
    下滤操作
    将 hole位置的元素移到何时的位置，hole 的子树均应为大顶堆
    lastOne 标识堆末尾元素的位置
*/
int Sorter::perlocateDown(QVector<int> &array, int hole, int lastOne){
    int temp, child;
    temp = array[hole];
    while (2*hole <= lastOne){ //空穴还有儿子节点
        child = 2*hole;
        m_chart->setFirst(hole);
        m_chart->setSecond(child);

        if (child+1 <= lastOne && array[child] < array[child+1]){
            ++child; //右儿子比较大
            m_chart->setSecond(child);
        }
        m_chart->update();
        if (temp < array[child])
            array[hole] = array[child];
        else
            break;
        hole = child; //移动空穴
        goAway(m_slowdown);
        if (m_interrupt){
            m_chart->resetFlag();
            m_chart->update();
            array[hole] = temp;
            return -1;
        }
    }
    array[hole] = temp;
    m_chart->resetFlag();
    m_chart->update();
    return 0;
}
/*
    建立大顶堆
*/
void Sorter::buildHeap(QVector<int> &array){
    for (int i = (array.size()-1)/2; i > 0; --i)
        if (perlocateDown(array, i, array.size()-1) == -1) // -1 表示 perlocateDown() 被打断
            return;
}

void Sorter::heapSort(){
    QVector<int> &array = m_chart->getArray();
    if (array.size() < 0)
        return ;
    array[0] = 0;
    m_interrupt = false;
    buildHeap(array);
    if (m_interrupt)return ;
    int lastOne = array.size()-1, temp;
    while (lastOne > 1){
        swap(array, 1, lastOne);
        if (perlocateDown(array, 1, --lastOne) == -1) return ; // -1 表示 perlocateDown() 被打断
    }
    m_chart->resetFlag();
    m_chart->update();
}

/////////////////////////快速排序//////////////////////////////////

/*
    比较left，mid，right，取中值放在right，最小值放在left，最大值放在right-1
*/
void Sorter::median(QVector<int> &array, int left, int right){
    int mid = (left+right)/2;
    if (array[mid] < array[left])
        swap(array, mid, left);
    if (array[right] < array[left])
        swap(array, right, left);
    if (array[mid] < array[right])
        swap(array, mid, right);
    swap(array, mid, right-1);

}

/*
    以 array[right] 为枢纽元，对数组 array 中 [left, right]区间中的元素进行 partition
    partition() 应在 median() 之后调用，因为 median() 保证 array[left] < array[right]
    且 array[right-1] > array[right]，而 partition() 是基于这样的前提进行的。
    并且，[left, right] 区间中的元素应多于 2 个元素
*/
int Sorter::partition(QVector<int> &array, int left, int right){
    int i = left, j = right-1;
    while (i < j){
        while (array[++i] < array[right]){
            if (m_interrupt){
                m_chart->resetFlag();
                return -1;
            }
            m_chart->setFirst(i);
            m_chart->update();
            goAway(m_slowdown);
        }
        m_chart->setFirst(i);
        m_chart->update();
        goAway(m_slowdown);
        while (array[--j] > array[right]){
            if (m_interrupt){
                m_chart->resetFlag();
                return -1;
            }
            m_chart->setSecond(j);
            m_chart->update();
            goAway(m_slowdown);
        }
        m_chart->setSecond(j);
        m_chart->update();
        goAway(m_slowdown);
        if (i < j)
            swap(array, i, j);
    }
    swap(array, i, right);
    m_chart->resetFlag();
    m_chart->update();
    return i;
}

/*
    对数组 array 在 [left, right] 区间中的元素进行快速排序
*/
void Sorter::quickSort(QVector<int>& array, int left, int right){
    if (left >= right)
        return ;
    if (left+10 >= right){
       insertionSort(array, left, right);
       return ;
    }
    median(array, left, right);
    int mid = partition(array, left, right);
    if (mid == -1)
        return ;
    quickSort(array, left, mid-1);
    quickSort(array, mid+1, right);
}

void Sorter::quickSort(){
    QVector<int>& array = m_chart->getArray();
    if (array.size() == 0)
        return ;
    m_interrupt = false;
    quickSort(array, 0, array.size()-1);
    m_chart->update();
}
