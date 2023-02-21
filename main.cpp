#include "controller.h"
#include <QApplication>


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);


    Data data; // allocate on heap with std::unique_ptr
    MainWindow controller(data);

    QObject::connect(&controller, &MainWindow::imageNew,
                         &data, &Data::imageNew);
    QObject::connect(&controller, &MainWindow::imageOpen,
                         &data, &Data::imageOpen);
    QObject::connect(&controller, &MainWindow::imageSave,
                         &data, &Data::imageSave);
    QObject::connect(&data, &Data::imageChange,
                        &controller, &MainWindow::render);

    controller.show();
    return app.exec();
}

