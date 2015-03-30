#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mDrawMode = false;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mDrawMode = true;
        mDrawBuffer.append(event->pos());
        event->accept();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mDrawMode = false;
        point=(event->pos());
        this->update();
        event->accept();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (!mDrawMode) return;
    point=(event->pos());
    this->update();
    event->accept();
    if (mDrawBuffer.size()<2) return;
    QPainter painter(this);
    painter.setPen(Qt::red);
    QList<QPoint>::const_iterator it = mDrawBuffer.begin();
    QPoint start = *it;
    it++;
    while(it != mDrawBuffer.end()) {
        QPoint end = *it;
        painter.drawLine(start,end);
        start = end;
        it++;
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
     QPainter painterc1(this);
     painterc1.setPen(Qt::blue);
     int radius1 = 80;
     while(radius1>0){
        if(radius1%2==0) { painterc1.setPen(Qt::red);};
        if(radius1%3==0) { painterc1.setPen(Qt::blue);};
        if(radius1%7==0) { painterc1.setPen(Qt::green);};
        painterc1.drawEllipse(point, radius1, radius1);
        radius1=radius1-qrand()%9;
    }
}
