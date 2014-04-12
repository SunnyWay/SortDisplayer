#include "qlinechart.h"
#include <QPainter>
#include <QTime>
#include <QRect>
#include <QPalette>

QLineChart::QLineChart(QWidget *parent) :
    QWidget(parent)
{
    max = 1000;
    setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255,255,255));
    setPalette(palette);

    resetFlag();
}

void QLineChart::paintEvent(QPaintEvent * ){
    QPainter painter;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    QRect rect = this->geometry();
    float lineWidth = (float)rect.width() / (array.size());
    float lineHeight;
    int lineMaxHeight = rect.height();
    float curX;
    painter.begin(this);
    curX = 1;

    for (int i = 0; i < array.size(); ++i){
        if (i == first)
            brush.setColor(Qt::red);
        else if (i == second)
            brush.setColor(Qt::green);
        else
            brush.setColor(Qt::black);
        lineHeight = array[i] / (float)max * lineMaxHeight;
        painter.fillRect(curX, lineMaxHeight- lineHeight, lineWidth-(int)(lineWidth*0.2), lineHeight, brush);
        curX += lineWidth;
    }
    painter.end();
}

void QLineChart::genArray(int size){
    array.resize(size);
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second()*1000);
    for (int i = 0; i != size; ++i){
        array[i] = qrand() % max;
    }
    update();
}
void QLineChart::setFirst(int value){
    first = value;
}
void QLineChart::setSecond(int value){
    second = value;
}
void QLineChart::setMax(int max){
    this->max = max;
}

void QLineChart::resizeEvent(QResizeEvent*){
    if (width() < array.size()){
        genArray(width());
    }
}
