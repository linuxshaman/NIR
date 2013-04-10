#include "jsonhelper.h"
#include <QDebug>
#include <iostream>
#include "qtjson.h"


#define BUILDING "building"
#define WIDTH "w"
#define HEIGHT "h"
#define LENGTH "l"
#define WIFI_ARRAY "WiFi"
#define X "x"
#define Y "y"
#define Z "z"
#define CUSTOM_ARRAY "Custom"
#define WALL_ARRAY "Wall"


using namespace std;
using namespace QtJson;

JSONHelper::JSONHelper(QString jsonData)
{
    _jsonData = jsonData;
    _building = NULL;
}


Building* JSONHelper::fromJSON(){
    return _building;
}


void JSONHelper::parse(){
    bool ok;
    QVariantMap result = QtJson::parse(_jsonData, ok).toMap();
    if(ok){
        QVariantMap buildingMap = result[BUILDING].toMap();
        createBuilding(buildingMap);
        createWiFiArray(buildingMap[WIFI_ARRAY].toList());
        createCustomArray(buildingMap[CUSTOM_ARRAY].toList());
        createWallArray(buildingMap[WALL_ARRAY].toList());
    }
}


void JSONHelper::createBuilding(QVariantMap buildingMap){
    float w = buildingMap[WIDTH].toFloat();
    float l = buildingMap[LENGTH].toFloat();
    int h = buildingMap[HEIGHT].toInt();

    _building = new Building(w, l, h, 1);
}

void JSONHelper::createWiFiArray(QList<QVariant> wifiArray){
    for(int i = 0; i < wifiArray.size(); i ++){
        QVariantMap map = wifiArray.at(i).toMap();
        QList<QString> names = map.keys();
        for(int i = 0; i < names.size(); i ++){
            QString networkName = names.at(i);
            QVariantMap networkProps = map[networkName].toMap();
            createWifi(networkProps, networkName);
        }
    }
}

void JSONHelper::createWifi(QVariantMap wifi, QString networkName)
{
    float x = wifi[X].toFloat();
    float y = wifi[Y].toFloat();
    int z = wifi[Z].toInt();
    Level* level =_building->levelAt(z);
    level->createWifi(x, y, networkName.toStdString());
}

void JSONHelper::createCustomArray(QList<QVariant> customArray)
{
    for(int i = 0; i < customArray.size(); i ++){
        QVariantMap map = customArray.at(i).toMap();
        QList<QString> names = map.keys();
        for(int i = 0; i < names.size(); i ++){
            QString objectName = names.at(i);
            QVariantMap objectProps = map[objectName].toMap();
            createCustomObject(objectProps, objectName);
        }
    }
}

void JSONHelper::createCustomObject(QVariantMap custom, QString name)
{
    float x = custom[X].toFloat();
    float y = custom[Y].toFloat();
    int z = custom[Z].toInt();
    float w = custom[WIDTH].toFloat();
    float l = custom[LENGTH].toFloat();
    Level* level =_building->levelAt(z);
    level->createCustomObject(x, y, w, l, name.toStdString());
}

void JSONHelper::createWallArray(QList<QVariant> wallArray)
{
    for(int i = 0; i < wallArray.size(); i ++){
        QVariantMap map = wallArray.at(i).toMap();
        QVariantMap::Iterator it = map.begin();
        while(it != map.end()){
            QVariantMap wallProps = ((QVariant)it.value()).toMap();
            createWall(wallProps);
            ++it;
        }
    }
}

void JSONHelper::createWall(QVariantMap wall)
{
    float x = wall[X].toFloat();
    float y = wall[Y].toFloat();
    int z = wall[Z].toInt();
    float w = wall[WIDTH].toFloat();
    float l = wall[LENGTH].toFloat();
    Level* level =_building->levelAt(z);

    level->createWall(x, y, w, l);
}
