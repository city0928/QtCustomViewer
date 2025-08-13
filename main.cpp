#include "BaseImageItem.h"
#include "BaseImageViewWidget.h"

#include <QApplication>
#include <QImageReader>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QImageReader::setAllocationLimit(1024);

    QPixmap pix;
    pix.load("D:/123.jpg");
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pix);
    BaseImageViewWidget<QGraphicsPixmapItem> w;
    w.setMainItem(item);
    w.show();

    BaseImageItem* baseitem = new BaseImageItem(pix);
    BaseImageViewWidget<BaseImageItem> baseView;
    baseView.setMainItem(baseitem);
    baseView.show();


    return a.exec();
}
