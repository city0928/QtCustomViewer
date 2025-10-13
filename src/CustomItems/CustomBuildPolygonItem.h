#pragma once

#include <QBrush>
#include <QGraphicsItem>
#include <QObject>
#include <QPen>
#include <QPolygon>

class CustomBuildPolygonItem : public QGraphicsItem
{
    // Q_OBJECT
    // Q_INTERFACES(QGraphicsItem)
    Q_DISABLE_COPY_MOVE(CustomBuildPolygonItem)
  public:
    CustomBuildPolygonItem(QGraphicsItem* parent = nullptr) noexcept;
    CustomBuildPolygonItem(QPolygonF* polygon, int penWidth, QPen pen = Qt::NoPen, QBrush brush = Qt::NoBrush, QGraphicsItem* parent = nullptr) noexcept;
    CustomBuildPolygonItem(QPolygonF* polygon, int penWidth, QGraphicsItem* parent = nullptr) noexcept;

    virtual QRectF boundingRect() const override;

    void setPen(QPen pen) noexcept { m_Pen = pen; }
    void setPenWidth(int penWidth) noexcept { m_Pen.setWidth(penWidth); }
    void setPenColor(QColor penColor) noexcept { m_Pen.setColor(penColor); }
    void setBrush(QBrush brush) noexcept { m_Brush = brush; }

  protected:
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    // virtual void wheelEvent(QGraphicsSceneWheelEvent* event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    // virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    // virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    // virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    // virtual void keyPressEvent(QKeyEvent* keyEvent) override;
    // virtual void keyReleaseEvent(QKeyEvent* keyEvent) override;

  private:
    QPointF pointOfRotation() const;  // 可旋转标示的位置

  private:
    bool m_IsAdjustModel{false};
    int m_Angle{0};
    int m_PenWidth;
    QPen m_Pen;
    QBrush m_Brush;
    QPolygonF* m_PolygonItem{nullptr};

    friend class CustomBuildPointSeamlessImageItem;
};
