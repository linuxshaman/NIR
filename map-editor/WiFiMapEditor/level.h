#ifndef LEVEL_H
#define LEVEL_H

#include "editor.h"

class Level
{
    int _z;
    vector<Object*>* _levelObjects;
public:
    Level(int z);
    vector<Object*>* getLevelObjects();

    Wall* createWall(float x, float y, float width, float length);
    WiFiSpot* createWifi(float x, float y);
    WiFiSpot* createWifi(float x, float y, string networkName);
    Object* createCustomObject(float x, float y);
    Object* createCustomObject(float x, float y, float width, float length);
    Object* createCustomObject(float x, float y, float width, float length, string name);
private:
    Object* createObject(Object* o);
};

#endif // LEVEL_H
