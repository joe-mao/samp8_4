#include "qwgraphicsview.h"
#include <QMouseEvent>

QWGraphicsView::QWGraphicsView(QWidget * parent)
    :QGraphicsView (parent)
{

}

void QWGraphicsView::mouseMoveEvent(QMouseEvent *event)
{//鼠标移动事件
    QPoint point = event->pos();//QGraphicsView的坐标
    emit mouseMovePoint(point);//发射信号
    QGraphicsView::mouseMoveEvent(event);

}

void QWGraphicsView::mousePressEvent(QMouseEvent *event)
{
    //鼠标左键按下事件
    if(event->button() == Qt::LeftButton){
        QPoint point = event->pos();//QGraphicsView的坐标
        emit mouseClicked(point);//发射信号
    }
    QGraphicsView::mousePressEvent(event);
}
