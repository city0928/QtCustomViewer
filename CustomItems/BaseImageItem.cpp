#include "BaseImageItem.h"

#include <QPixmap>
#include <QPainter>
#include <QGraphicsSceneWheelEvent>

BaseImageItem::BaseImageItem(QGraphicsItem* parent) noexcept
    : QGraphicsItem(parent)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton | Qt::MouseButton::RightButton);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

BaseImageItem::BaseImageItem(QPixmap pixmap, QGraphicsItem* parent) noexcept
    : QGraphicsItem(parent), m_Img{pixmap}
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton | Qt::MouseButton::RightButton);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

void BaseImageItem::updateImg(const QPixmap &pixmap) noexcept
{
    m_Img = pixmap;
}

void BaseImageItem::clearData() noexcept
{
    QPixmap img;
    m_Img.swap(std::ref(img));
}

void BaseImageItem::resetItemData(double newScaleValue) noexcept
{
    m_DefaultScale = newScaleValue;
    m_CurrentScale = newScaleValue;
    setPos(0, 0);
}

QRectF BaseImageItem::boundingRect() const
{
    if(m_Img.isNull()){
        QRectF{0,0,0,0};
    }
    QRectF rect{m_Img.rect()};
    return {-rect.width()/2, -rect.height()/2, rect.width(), rect.height()};
}

void BaseImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(m_Img.isNull()) return;
    painter->drawPixmap(boundingRect().toRect(), m_Img);

}

void BaseImageItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    auto copyLastScale = m_CurrentScale;
    auto zoomRate = 0.1;
    if (event->delta() > 0){
        m_CurrentScale *= 1 + zoomRate;
    }else{
        m_CurrentScale *= 1 - zoomRate;
    }
    setScale(m_CurrentScale);
    if (event->delta() > 0){
        moveBy(-event->pos().x() * copyLastScale * zoomRate, -event->pos().y() * copyLastScale * zoomRate);
    }else{
        moveBy(event->pos().x() * copyLastScale * zoomRate, event->pos().y() * copyLastScale * zoomRate);
    }
}

void BaseImageItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::RightButton){
        resetItemData(m_DefaultScale);
        setScale(m_DefaultScale);
    }
}

void BaseImageItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->buttons() & Qt::LeftButton){
        moveBy(event->scenePos().x() - event->lastScenePos().x(), event->scenePos().y() - event->lastScenePos().y());
    }
}

void BaseImageItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

}

void BaseImageItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{

}

void BaseImageItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{

}

void BaseImageItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
}

void BaseImageItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{

}

void BaseImageItem::keyPressEvent(QKeyEvent* keyEvent)
{
}

void BaseImageItem::keyReleaseEvent(QKeyEvent* keyEvent)
{

}

