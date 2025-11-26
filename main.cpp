#include <QApplication>
#include "MainWindow.h"
#include "PageFactoryImpl.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PageFactory* factory = createFactory();
    MainWindow w(factory);
    w.show();
    return a.exec();
}