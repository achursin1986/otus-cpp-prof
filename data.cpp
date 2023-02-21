#include "data.h"


void Data::imageOpen(QString Path) {
    image.load(Path);
    // send signal to controller/viewer that data has changed
     emit imageChange(this->get());
}

void Data::imageSave(QString Path) {
    image.save(Path);
}

void Data::imageNew(QSize S) {
    image = QImage(S, QImage::Format_RGB32);
    image.fill(Qt::white);
     emit imageChange(this->get());
}


