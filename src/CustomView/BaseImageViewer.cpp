#include "BaseImageViewer.h"

#include <QPainter>
#include <QSize>
#include <QResizeEvent>

BaseImageViewer::BaseImageViewer(QWidget* parent)
    : QGraphicsView(parent)
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

BaseImageViewer::~BaseImageViewer() {}

void BaseImageViewer::resizeEvent(QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);
}

void BaseImageViewer::drawBackground(QPainter* painter, const QRectF& rect)
{
    QList<QLineF> lines;
    const int grid = 25;
    int startX = std::floor(rect.left() / grid) * grid;
    int endX = std::ceil(rect.right() / grid) * grid;
    int startY = std::floor(rect.top() / grid) * grid;
    int endY = std::ceil(rect.bottom() / grid) * grid;
    for (int x = startX; x <= endX; x += grid) {
        QLineF line(x, rect.top(), x, rect.bottom());
        lines << line;
    }
    for (int y = startY; y <= endY; y += grid) {
        QLineF line(rect.left(), y, rect.right(), y);
        lines << line;
    }

    QGraphicsView::drawBackground(painter, rect);
    painter->fillRect(sceneRect(), {30, 30, 30});
    QPen pen;
    pen.setColor({70, 70, 70, 90});
    painter->setPen(pen);
    painter->drawLines(lines);
}

void BaseImageViewer::drawForeground(QPainter* painter, const QRectF& rect) { QGraphicsView::drawForeground(painter, rect); }
