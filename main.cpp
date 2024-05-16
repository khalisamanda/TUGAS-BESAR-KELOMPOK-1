#include "siperpustakaan.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SiPerpustakaan w;
    w.show();
    return a.exec();
}
