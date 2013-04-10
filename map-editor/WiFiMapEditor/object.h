#ifndef OBJECT_H
#define OBJECT_H

#include "editor.h"
#include <QPointF>


enum ObjectType{
    WALL_OBJECT,
    WIFI_OBJECT,
    CUSTOM_OBJECT
};

class Object : public JSONObject
{
protected:
    float _x;
    float _y;
    int _z;
public:
    ObjectType type;
    Object(float x, float y, int z);
    Object(float x, float y, float width, float length, int z);
    Object(float x, float y, float width, float length, int z, string name);

    virtual QString toJSON();
    QPointF pos();
};

class Wall : public Object{
public:
    Wall(float x, float y, float width, float length, int z);
};

class WiFiSpot : public Object{
    string _networkName;
public:
    WiFiSpot(float x, float y, int z);
    WiFiSpot(float x, float y, int z, string networkName);
    void setNetworkName(string networkName);
    string getNetworkName();

    virtual QString toJSON();
};

#endif // OBJECT_H
