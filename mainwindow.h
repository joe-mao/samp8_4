#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent * event);

private slots:
    void on_mouseMovePoint(QPoint point);
    void on_mouseClicked(QPoint point);

private:
    QGraphicsScene * scene;
    QLabel * labViewCord;
    QLabel * labSceneCord;
    QLabel * labItemCord;
    void iniGraphicsSystem();//创建GraphicsView的各项

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
