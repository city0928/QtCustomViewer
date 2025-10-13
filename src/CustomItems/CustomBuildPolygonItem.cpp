#include "CustomBuildPolygonItem.h"

#include <QCursor>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "BaseHelper.h"

CustomBuildPolygonItem::CustomBuildPolygonItem(QGraphicsItem* parent) noexcept
    : QGraphicsItem(parent)
{
    m_Pen.setCosmetic(true);

    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton | Qt::MouseButton::RightButton);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

CustomBuildPolygonItem::CustomBuildPolygonItem(QPolygonF* polygon, int penWidth, QPen pen, QBrush brush, QGraphicsItem* parent) noexcept
    : QGraphicsItem(parent),
      m_PolygonItem(polygon),
      m_PenWidth{penWidth},
      m_Pen{pen},
      m_Brush{brush}
{
    m_Pen.setCosmetic(true);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton | Qt::MouseButton::RightButton);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

CustomBuildPolygonItem::CustomBuildPolygonItem(QPolygonF* polygon, int penWidth, QGraphicsItem* parent) noexcept
    : QGraphicsItem(parent),
      m_PolygonItem(polygon),
      m_PenWidth{penWidth},
      m_Pen{Qt::NoPen},
      m_Brush{Qt::NoBrush}
{
    m_Pen.setCosmetic(true);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton | Qt::MouseButton::RightButton);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

QRectF CustomBuildPolygonItem::boundingRect() const
{
    auto offsetPoint = m_PolygonItem->boundingRect().center();
    auto standardPos = QPointF{-m_PolygonItem->boundingRect().width() / 2, -m_PolygonItem->boundingRect().height() / 2};
    return QRectF{standardPos + offsetPoint, m_PolygonItem->boundingRect().size()}.adjusted(-ADJUSTITEM, -ADJUSTITEM, ADJUSTITEM, ADJUSTITEM);
}

void CustomBuildPolygonItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*)
{
    painter->setPen(m_Pen);
    painter->setBrush(m_Brush);
    if (m_PolygonItem and m_PolygonItem->size()) {
        painter->save();
        QPolygonF rotatedPolygon = BaseHelper::rotatePolygon(*m_PolygonItem, boundingRect().center(), m_Angle);
        painter->drawPolygon(rotatedPolygon);
        painter->restore();
    }
    if (option->state & QStyle::State_MouseOver) {
        QPen pen;
        pen.setWidth(1);
        pen.setColor(Qt::green);
        pen.setCosmetic(true);
        painter->setPen(pen);
        if (m_IsAdjustModel)
            painter->setBrush(Qt::green);
        else
            painter->setBrush(Qt::red);
        painter->drawEllipse(pointOfRotation(), 15, 15);
    }
}

void CustomBuildPolygonItem::mousePressEvent(QGraphicsSceneMouseEvent* event) { QGraphicsItem::mousePressEvent(event); }

void CustomBuildPolygonItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_IsAdjustModel and event->buttons() & Qt::LeftButton) {
        prepareGeometryChange();
        qreal rad = qAtan2(event->scenePos().y() - mapToScene(boundingRect().center()).y(),
                           event->scenePos().x() - mapToScene(boundingRect().center()).x()) /* * 180 / M_PI*/;
        qreal deg = qRadiansToDegrees(rad);
        m_Angle = deg;
        update(boundingRect().adjusted(-ADJUSTITEM, -ADJUSTITEM, ADJUSTITEM, ADJUSTITEM));
    }
}

void CustomBuildPolygonItem::mouseReleaseEvent([[maybe_unused]] QGraphicsSceneMouseEvent* event)
{ /*QGraphicsItem::mouseReleaseEvent(event);*/
}

void CustomBuildPolygonItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    QPainterPath topLeftPos;
    topLeftPos.addEllipse(pointOfRotation(), 15, 15);
    if (topLeftPos.contains(event->pos())) {
        m_IsAdjustModel = true;
        setCursor(Qt::CursorShape::SizeAllCursor);
    } else {
        m_IsAdjustModel = false;
        setCursor(Qt::CursorShape::ArrowCursor);
    }
    update(boundingRect().adjusted(-ADJUSTITEM, -ADJUSTITEM, ADJUSTITEM, ADJUSTITEM));
}

QPointF CustomBuildPolygonItem::pointOfRotation() const
{
    auto centerPos = m_PolygonItem->boundingRect().center();
    auto ratatePos = m_PolygonItem->boundingRect().center() +
                     QPointF{boundingRect().adjusted(ADJUSTITEM, ADJUSTITEM, -ADJUSTITEM, -ADJUSTITEM).width() / 2, 0};
    return {BaseHelper::rotatePoint(ratatePos, centerPos, m_Angle)};
}
