#include "editor.h"

Level::Level(int z)
{
    _z = z;
    _levelObjects = new vector<Object*>();
}


vector<Object *> *Level::getLevelObjects(){
    return _levelObjects;
}


Object* Level::createObject(Object *o){
    _levelObjects->push_back(o);
    return o;
}

Object* Level::createCustomObject(float x, float y){
    Object* o = new Object(x, y, _z);
    return createObject(o);
}

Object* Level::createCustomObject(float x, float y, float width, float length){
    Object* o = new Object(x, y, width, length, _z);
    return createObject(o);
}

Object* Level::createCustomObject(float x, float y, float width, float length, string name){
    Object* o = new Object(x, y, width, length, _z, name);
    return createObject(o);
}

Wall* Level::createWall(float x, float y, float width, float length){
    Wall* w = new Wall(x, y, width, length, _z);
    return (Wall*)createObject(w);
}

WiFiSpot *Level::createWifi(float x, float y)
{
    WiFiSpot* w = new WiFiSpot(x, y, _z);
    return (WiFiSpot*)createObject(w);
}


WiFiSpot *Level::createWifi(float x, float y, string networkName)
{
    WiFiSpot* w = new WiFiSpot(x,y, _z, networkName);
    return (WiFiSpot*)createObject(w);
}
