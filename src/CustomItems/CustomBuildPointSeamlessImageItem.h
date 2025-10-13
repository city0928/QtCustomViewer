#pragma once

#include "CustomBuildPolygonItem.h"

class CustomBuildPointSeamlessImageItem : public /*BaseImageItem*/CustomBuildPolygonItem
{
    // Q_OBJECT
  public:
    explicit CustomBuildPointSeamlessImageItem(QGraphicsItem* parent = nullptr);
    ~CustomBuildPointSeamlessImageItem();

    void setPos(const QPointF pos);

    QPointF offsetValue() const { return m_OffsetPointf; }
    virtual QRectF boundingRect() const override;

    QPolygonF polygonf() { return *m_PolygonItem; }

  protected:
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    virtual void wheelEvent(QGraphicsSceneWheelEvent* event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    // virtual void focusInEvent(QFocusEvent* event) override;
    // virtual void focusOutEvent(QFocusEvent* event) override;
    // virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    // virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    // virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

  private:
    QPointF m_InitPos{0, 0};
    QPointF m_OffsetPointf{0, 0};

  private:
    QPixmap m_ItemPixmap;
};
