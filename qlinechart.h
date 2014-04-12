#ifndef QLINECHART_H
#define QLINECHART_H

#include <QWidget>
#include <QVector>

class QLineChart : public QWidget
{
    Q_OBJECT
public:
    explicit QLineChart(QWidget *parent = 0);
    void genArray(int size);
    void setFirst(int value);
    void setSecond(int value);
    void setMax(int max);
    QVector<int>& getArray(){return array;}
    void resizeEvent(QResizeEvent*);
    void resetFlag(){first = -1; second = -1;}
protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    int max;//随机数边界值
    int first;//第一操作数
    int second;//第二操作数
    QVector<int> array;

};

#endif // QLINECHART_H
