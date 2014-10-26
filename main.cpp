#include "mainwindow.h"
#include <magick/MagickCore.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    MagickCoreGenesis(*argv, MagickTrue);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int result = a.exec();

    MagickCoreTerminus();

    return result;
}
