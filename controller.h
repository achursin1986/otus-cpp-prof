#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include "data.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Data& data_, QWidget *parent = 0);
    ~MainWindow();

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void render(QImage* data_);

private slots:
    void on_actionnew_triggered();
    void on_actionopen_triggered();
    void on_actionsave_triggered();
    void on_actionexit_triggered();
    void on_actionclear_triggered();

signals:
    void imageNew(QSize S);
    //void imageCChange();
    void imageOpen(QString Path);
    void imageSave(QString Path);



private:
    Ui::MainWindow *ui;
    QImage* data;
    bool drawing;
    QPoint lastPoint;
};

#endif // CONTROLLER_H
