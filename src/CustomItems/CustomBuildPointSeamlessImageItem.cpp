#include "CustomBuildPointSeamlessImageItem.h"

#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "BaseHelper.h"

CustomBuildPointSeamlessImageItem::CustomBuildPointSeamlessImageItem(QGraphicsItem* parent)
    : CustomBuildPolygonItem(parent) /*BaseImageItem(info->dstPixmap.second, parent)*/,
      m_OffsetPointf(QPointF(parent->boundingRect().width() / 2, parent->boundingRect().height() / 2))
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton | Qt::MouseButton::RightButton);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

CustomBuildPointSeamlessImageItem::~CustomBuildPointSeamlessImageItem() {}

void CustomBuildPointSeamlessImageItem::setPos(const QPointF pos)
{
    m_InitPos = pos;
    QGraphicsItem::setPos(pos);
}

QRectF CustomBuildPointSeamlessImageItem::boundingRect() const
{
    // auto offsetPoint = m_ItemDataInfo->dstPolygonf.boundingRect().center();
    // return QRectF{-offsetValue() + offsetPoint, QSize(offsetValue().x() * 2, offsetValue().y() * 2)}.adjusted(-ADJUSTITEM, -ADJUSTITEM, ADJUSTITEM,
    // ADJUSTITEM);
    return CustomBuildPolygonItem::boundingRect();
}

void CustomBuildPointSeamlessImageItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    // draw polygon
    CustomBuildPolygonItem::paint(painter, option, widget);
    if (m_PolygonItem) {
        // draw pixmap
        painter->save();
        painter->translate(boundingRect().center());
        painter->rotate(m_Angle);
        painter->translate(-boundingRect().center());
        QPainterPath pixmapPath;
        pixmapPath.addPolygon(*m_PolygonItem);
        painter->setClipPath(pixmapPath);
        painter->drawPixmap(boundingRect().adjusted(ADJUSTITEM, ADJUSTITEM, -ADJUSTITEM, -ADJUSTITEM).toRect(), m_ItemPixmap);
        painter->restore();
    }
}

void CustomBuildPointSeamlessImageItem::wheelEvent(QGraphicsSceneWheelEvent* event) { event->ignore(); }

void CustomBuildPointSeamlessImageItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::RightButton) {
        // resetScale(1.0);
        setPos(m_InitPos);
    }
}

void CustomBuildPointSeamlessImageItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_IsAdjustModel and event->buttons() & Qt::LeftButton) {
        CustomBuildPolygonItem::mouseMoveEvent(event);
    } else if (event->buttons() & Qt::LeftButton) {
        QPointF parentCurrentPos = parentItem()->mapFromScene(event->scenePos());
        QPointF parentLastPos = parentItem()->mapFromScene(event->lastScenePos());
        QPointF delta = parentCurrentPos - parentLastPos;
        // moveBy(delta.x(), delta.y());
    }
}

void CustomBuildPointSeamlessImageItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_IsAdjustModel and event->button() == Qt::LeftButton) {
    }
}

void CustomBuildPointSeamlessImageItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event) { CustomBuildPolygonItem::hoverMoveEvent(event); }
