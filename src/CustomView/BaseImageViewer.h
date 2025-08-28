#pragma once

#include <QGraphicsView>
#include <QWidget>

class BaseImageViewer : public QGraphicsView
{
    Q_OBJECT

  public:
    explicit BaseImageViewer(QWidget* parent = nullptr);
    ~BaseImageViewer();

  protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void drawBackground(QPainter* painter, const QRectF& rect) override;
    virtual void drawForeground(QPainter* painter, const QRectF& rect) override;

private:
    QList<QLineF> m_ViewLines;
};
