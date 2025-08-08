#include "Viewer.h"

Viewer::Viewer(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

Viewer::~Viewer() {}
