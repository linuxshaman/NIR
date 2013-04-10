#include "editor.h"

//Object

Object::Object(float x, float y, int z){
    _x = x;
    _y = y;
    _z = z;
    type = CUSTOM_OBJECT;
}

Object::Object(float x, float y, float width, float length, int z):
    Object(x, y, z)
{
    _width = width;
    _length = length;
}

Object::Object(float x, float y, float width, float length, int z,  string name):
    Object(x, y, width, length, z)
{
    _name = name;
}

QString Object::toJSON(){
    QString result = QString("{\"%1\":{\"x\":%2, \"y\":%3, \"z\":%4, \"w\":%5,\"l\":%6}}").arg(QString::fromStdString(_name), QString::number(_x), QString::number(_y), QString::number(_z), QString::number(_width),  QString::number(_length));
    return result;
}

QPointF Object::pos(){
    return QPointF(_x, _y);
}


//Wall

Wall::Wall(float x, float y, float width, float length, int z):
    Object(x, y, width, length, z)
{
    _name = WALL;
    type = WALL_OBJECT;
}


//WiFiSpot

WiFiSpot::WiFiSpot(float x, float y, int z):
    Object(x, y, z)
{
    _name = WI_FI;
    _width = 0;
    _length = 0;
    type = WIFI_OBJECT;
}

WiFiSpot::WiFiSpot(float x, float y, int z, string networkName):
    WiFiSpot(x, y, z)
{
    _networkName = networkName;
}


void WiFiSpot::setNetworkName(string networkName){
    _networkName = networkName;
}

string WiFiSpot::getNetworkName(){
    return _networkName;
}


QString WiFiSpot::toJSON(){
    QString result = QString("{\"%1\":{\"x\":%2, \"y\":%3, \"z\":%4}}").arg(QString::fromStdString(_networkName), QString::number(_x), QString::number(_y), QString::number(_z));
    return result;
}
