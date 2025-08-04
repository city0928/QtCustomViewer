#include "BaseImageItem.h"
#include "BaseImageViewWidget.h"

#include <QApplication>
#include <QImageReader>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QImageReader::setAllocationLimit(1024);

    BaseImageViewWidget<BaseImageItem> w;
    QPixmap pix;
    pix.load("D:/123.jpg");
    w.updateShowImage(pix);

    w.show();
    return a.exec();
}
