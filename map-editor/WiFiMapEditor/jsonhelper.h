#ifndef JSONHELPER_H
#define JSONHELPER_H

#include "editor.h"
#include <QVariantMap>

class JSONHelper{
    Building* _building;
    QString _jsonData;
public:
    JSONHelper(QString jsonData);
    Building* fromJSON();
    void parse();
private:
    void createBuilding(QVariantMap buildingMap);
    void createWiFiArray(QList<QVariant> wifiArray);
    void createWifi(QVariantMap wifi, QString networkName);
    void createCustomArray(QList<QVariant> customArray);
    void createCustomObject(QVariantMap custom, QString name);
    void createWallArray(QList<QVariant> wallArray);
    void createWall(QVariantMap wall);
};

#endif // JSONHELPER_H
