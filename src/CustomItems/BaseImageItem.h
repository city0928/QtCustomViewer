#pragma once

#include <QGraphicsItem>
#include <QObject>

class IItem : public QObject
{
    Q_OBJECT
public:
    IItem() = default;
    virtual void clearData() noexcept = 0;
    virtual void resetItemData(double newScaleValue) noexcept = 0;
};

class BaseImageItem : public IItem, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
    Q_DISABLE_COPY_MOVE(BaseImageItem)
public:
    BaseImageItem(QGraphicsItem* parent = nullptr) noexcept;
    BaseImageItem(QPixmap pixmap, QGraphicsItem* parent = nullptr) noexcept;

    QPixmap image() const { return m_Img; }

    virtual void clearData() noexcept override;
    virtual void resetItemData(double newScaleValue) noexcept override;
    virtual QRectF boundingRect() const override;

public Q_SLOTS:
    void updateImg(const QPixmap& pixmap) noexcept;

protected:
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    virtual void wheelEvent(QGraphicsSceneWheelEvent* event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* keyEvent) override;
    virtual void keyReleaseEvent(QKeyEvent* keyEvent) override;

private:
    QPixmap m_Img;
    double m_DefaultScale{1.0};
    double m_CurrentScale{1.0};
};
