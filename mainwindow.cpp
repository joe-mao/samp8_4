#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QRectF>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labViewCord = new QLabel("View 坐标:");
    labViewCord->setMinimumWidth(150);
    this->ui->statusBar->addWidget(labViewCord);

    labSceneCord = new QLabel("Scene 坐标");
    labSceneCord->setMinimumWidth(150);
    this->ui->statusBar->addWidget(labSceneCord);

    labItemCord = new QLabel("Item 坐标");
    labItemCord->setMinimumWidth(150);
    this->ui->statusBar->addWidget(labItemCord);

    this->ui->view->setCursor(Qt::CrossCursor);
    this->ui->view->setMouseTracking(true);
    this->ui->view->setDragMode(QGraphicsView::RubberBandDrag);

    QObject::connect(this->ui->view, SIGNAL(mouseMovePoint(QPoint)), this, SLOT(on_mouseMovePoint(QPoint)));
    QObject::connect(this->ui->view, SIGNAL(mouseClicked(QPoint)), this, SLOT(on_mouseClicked(QPoint)));

    iniGraphicsSystem();




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    //窗口变化大小时的事件
    this->ui->labViewSize->setText(QString::asprintf("Graphics View坐标,左上角总是(0, 0),宽度 = %d, 高度 = %d", this->ui->view->width(), this->ui->view->height()));
    QRectF rectF = this->ui->view->sceneRect();//Scene的矩形区
    this->ui->LabSceneRect->setText(QString::asprintf("QGraphicsView::sceneRect = (Left, Top, Width, Height) = %.0f, %.0f, %.0f, %.0f", rectF.left(), rectF.top(), rectF.width(), rectF.height()));
}

void MainWindow::on_mouseMovePoint(QPoint point)
{
    //鼠标移动事件，point是GraphicView的坐标,物理坐标
    labViewCord->setText(QString::asprintf("View 坐标: %d, %d", point.x(), point.y()));
    QPointF pointScene = this->ui->view->mapToScene(point);//转到scene坐标
    labSceneCord->setText(QString::asprintf("Scene 坐标: %.0f, %.0f", pointScene.x(), pointScene.y()));
}

void MainWindow::on_mouseClicked(QPoint point)
{
    //鼠标单击事件
    QPointF pointScene = this->ui->view->mapToScene(point);//转换到scene坐标
    QGraphicsItem * item = nullptr;
    item = scene->itemAt(pointScene, this->ui->view->transform());//获取光标下的图形项
    if(item != nullptr){
        //有图形项
        QPointF pointItem = item->mapFromScene(pointScene);//图形项局部坐标
        labItemCord->setText(QString::asprintf("Item 坐标; %.0f, %.0f", pointItem.x(), pointItem.y()));
    }
}

void MainWindow::iniGraphicsSystem()
{
    //构造Graphics View的各项
    QRectF rect(-200, -100, 400, 200);//左上角坐标,宽度，高度
    scene = new QGraphicsScene(rect);//scene逻辑坐标定义
    this->ui->view->setScene(scene);

    //画一个矩形框， 大小等于scene
    QGraphicsRectItem * item = new QGraphicsRectItem(rect);
    item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);//设置flags
    QPen pen;
    pen.setWidth(2);
    item->setPen(pen);
    scene->addItem(item);

    //画一个位于Scene中心的椭圆，测试局部坐标
    QGraphicsEllipseItem * item2 = new QGraphicsEllipseItem(-100, -50, 200, 100);
    item2->setPos(0, 0);//设置在场景中的坐标
    item2->setBrush(QBrush(Qt::blue));
    item2->setFlags(QGraphicsItem::ItemIsMovable |
                        QGraphicsItem::ItemIsSelectable |
                        QGraphicsItem::ItemIsFocusable);
    scene->addItem(item2);

    //画一个圆，中心位于Scene的边缘
    QGraphicsEllipseItem * item3 = new QGraphicsEllipseItem(-50, -50, 100, 100);
    item3->setPos(rect.right(), rect.bottom());
    item3->setBrush(QBrush(Qt::red));
    item3->setFlags(QGraphicsItem::ItemIsMovable |
                        QGraphicsItem::ItemIsSelectable |
                        QGraphicsItem::ItemIsFocusable);
    scene->addItem(item3);


}
