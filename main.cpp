#include "videochat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoChat w;
    w.show();

    return a.exec();
}
