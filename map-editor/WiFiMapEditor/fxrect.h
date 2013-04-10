#ifndef FXRECT_H
#define FXRECT_H

#include <QPoint>

#define QPoint_zero QPoint(0,0)
#define fxRect_points_count 4

class fxRect
{
private:
    QPointF _startPos;
    QPointF _endPos;
    QPointF _origin;
    float _width;
    float _height;
    void _update();
public:
    fxRect();
    fxRect(QPointF startPos);
    fxRect(QPointF startPos, QPointF endPos);
    void update(QPointF p);
    void create(QPointF p);
    QPointF *points();
    float width();
    float height();
    QPointF origin();
};

#endif // FXRECT_H
