#include "BaseHelper.h"

#include "opencv2/core.hpp"
#include "opencv2/core/matx.hpp"

QPolygonF BaseHelper::rotatePolygon(const QPolygonF& pts, QPointF center, float angleDeg)
{
    QPolygonF polygonf;
    for (auto& p : pts.toList()) {
        polygonf.append(BaseHelper::rotatePoint(p, center, angleDeg));
    }
    return polygonf;
}

QPointF BaseHelper::rotatePoint(const QPointF& pts, QPointF center, float angleDeg)
{
    float angle = angleDeg * M_PI / 180.0f;
    cv::Matx22f R(cos(angle), -sin(angle), sin(angle), cos(angle));
    cv::Point2f centerPos(center.x(), center.y());
    cv::Point2f roratePos(pts.x(), pts.y());
    cv::Point2f rp = R * (roratePos - centerPos) + centerPos;
    return QPointF(rp.x, rp.y);
}
