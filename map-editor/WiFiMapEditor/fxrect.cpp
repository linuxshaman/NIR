#include "fxrect.h"
#include <algorithm>


using namespace std;

fxRect::fxRect(QPointF startPos, QPointF endPos)
{
    _startPos = startPos;
    _endPos = endPos;
    _update();
}

fxRect::fxRect():
    fxRect(QPoint_zero, QPoint_zero){}

fxRect::fxRect(QPointF startPos):
    fxRect(startPos, startPos){}

void fxRect::update(QPointF p){
    _endPos = p;
    _update();
}

void fxRect::create(QPointF p){
    _startPos = p;
    _endPos = p;
}

QPointF *fxRect::points()
{
    QPointF* points = new QPointF[fxRect_points_count];
    points[0] = _origin;
    points[1] =_origin + QPointF(_width, 0);
    points[2] = points[1] + QPointF(0, _height);
    points[3] = _origin + QPointF(0, _height);
    return points;
}

void fxRect::_update()
{
    _origin = QPointF(min(_startPos.x(), _endPos.x()), min(_startPos.y(), _endPos.y()));
    QPointF maxPoint = QPointF(max(_startPos.x(), _endPos.x()), max(_startPos.y(), _endPos.y()));
    _width = maxPoint.x() - _origin.x();
    _height = maxPoint.y() - _origin.y();
}

float fxRect::width(){
    return _width;
}

float fxRect::height(){
    return _height;
}

QPointF fxRect::origin(){
    return _origin;
}
