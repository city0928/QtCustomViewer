#pragma once

#include <QPolygonF>
#include <QVariant>

#define ADJUSTITEM 100

class BaseHelper
{
  public:
    static QPolygonF rotatePolygon(const QPolygonF& pts, QPointF center, float angleDeg);
    static QPointF rotatePoint(const QPointF& pts, QPointF center, float angleDeg);
};
