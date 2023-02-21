#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QPainter>



class Data : public QObject
{
    Q_OBJECT

public:
    explicit Data(QObject *parent = nullptr)
        : QObject{parent},image(QImage(QSize(800,600), QImage::Format_RGB32))
    {  }
    QImage* get() {
        return &image;
    }

public slots:
    void imageOpen(QString Path);
    void imageSave(QString Path);
    void imageNew(QSize S);

signals:
    void imageChange(QImage* image_);

private:
   QImage image;
};


#endif // DATA_H
