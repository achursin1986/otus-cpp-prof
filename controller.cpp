#include "controller.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Data& data_, QWidget *parent)
    :  QMainWindow(parent)
    ,  ui(new Ui::MainWindow)
    , data(data_.get())
{
    ui->setupUi(this);
    drawing = false;
    data->fill(Qt::gray);
    this->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::render(QImage* data_) {
    data = data_;
    this->update();

}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        drawing = true;
        lastPoint = event->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing)
    {
        QPainter painter(data);
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        this->update();


    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        drawing = false;
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter canvasPainter(this);
    canvasPainter.drawImage(this->rect(), *data, data->rect());
}


void MainWindow::on_actionopen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Image", "", "PNG (*.png);;JPEG (*.jpg *.jpeg);;All files (*.*)");
    if (filePath == "")
        return;
    emit imageOpen(filePath);
}



void MainWindow::on_actionsave_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG (*.png);;JPEG (*.jpg *.jpeg);;All files (*.*)");

    if (filePath == "")
        return;
    emit imageSave(filePath);
}

void MainWindow::on_actionexit_triggered()
{
    QApplication::quit();

}

void MainWindow::on_actionclear_triggered()
{

    data->fill(Qt::white);
    this->update();


}


void MainWindow::on_actionnew_triggered()
{
    emit imageNew(this->size());


}



