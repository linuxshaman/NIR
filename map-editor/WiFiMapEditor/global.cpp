#include <QStringList>
#include "global.h"

#define SUFFIX  "prowfm"
#define MAP "wfm"
#include <QDebug>

Global* __instance = NULL;

Global* Global::instance(){
    if(!__instance){
        __instance = new Global();
    }
    return __instance;
}


Global::Global(){
    _path = NULL;
    _imagePath = NULL;
    _building = NULL;
    _indentX =  _indentY = 0;
    _scaleX = _scaleY = 1;
}

void Global::Open(QString path){
    instance()->_path = new QString(path);
    instance()->open();
}

void Global::Save(){
    if(instance()->_path){
        instance()->save();
    }
}

void Global::SaveAs(QString path){
    if(instance()->_path){
        if(instance()->_path->compare(path) != 0){
            instance()->_path = new QString(path);
        }
    }else{
        instance()->_path = new QString(path);
    }
    instance()->save();
}

void Global::Export(QString path){
    Building* b = instance()->building();
    if(b){
        QPointF indent = instance()->indent();
        QPointF scale = instance()->scale();
        Building* exportB = new Building(b->getWidth(), b->getLength(), b->getHeight(), 1);
        vector<Object*>* currentObjects = b->levelAt(1)->getLevelObjects();
        Level* l = exportB->levelAt(1);
        for(int i = 0; i < currentObjects->size();i ++){
            Object* o = currentObjects->at(i);
            QPointF pos = o->pos() - indent;
            pos.setX(pos.x() / scale.x());
            pos.setY(pos.y() / scale.y());
            switch (o->type) {
            case WALL_OBJECT:
            {
                l->createWall(pos.x(), pos.y(), o->getWidth(), o->getLength());
                break;
            }
            case CUSTOM_OBJECT:
            {
                l->createCustomObject(pos.x(), pos.y(), o->getWidth(), o->getLength(), o->getName());
                break;
            }
            case WIFI_OBJECT:
            {
                WiFiSpot* spot = dynamic_cast<WiFiSpot*>(o);
                l->createWifi(pos.x(), pos.y(), spot->getNetworkName());
                break;
            }
            default:
                break;
            }
        }
        saveToFile(path, exportB->toJSON());
    }
}

void Global::New(QString path, QString imagePath){
    instance()->_path = &path;
    instance()->_imagePath = &imagePath;
    instance()->_building = NULL;
    instance()->save();
}

Building* Global::building(){
    return instance()->_building;
}


void Global::open(){
    QString projectData = readFile(*instance()->_path);
    QStringList parts = projectData.split("\n");
    instance()->_imagePath = new QString(parts[0]);
    instance()->_indentX = parts[2].toFloat();
    instance()->_indentY = parts[3].toFloat();
    instance()->_scaleX = parts[4].toFloat();
    instance()->_scaleY = parts[5].toFloat();
    QString mapPath = QString(parts[1]);
    QString data = readFile(mapPath);
    if(data.size() != 0){
        JSONHelper* helper = new JSONHelper(data);
        helper->parse();
        _building = helper->fromJSON();
    }
}

void Global::save(){
    QString* path = instance()->_path;
    QString mapPath = QString(path->toStdString().c_str());
    QString projectPath = QString(path->toStdString().c_str());
    if(path->endsWith(SUFFIX)){
        mapPath.replace(SUFFIX, MAP);
    }else{
        mapPath.append(".").append(MAP);
        projectPath.append(".").append(SUFFIX);
    }
    QString data = QString("");
    if(instance()->building()){
        data = instance()->building()->toJSON();
    }
    saveToFile(mapPath, data);
    QString projectData = QString("%1\n%2\n%3\n%4\n%5\n%6").arg(*instance()->_imagePath, mapPath, QString::number(_indentX),QString::number(_indentY),QString::number(_scaleX),QString::number(_scaleY));
    saveToFile(projectPath, projectData);
}

QString Global::imagePath(){
    return *instance()->_imagePath;
}

Building* Global::createBuilding(float w, float l, int h){
    instance()->_building = new Building(w, l, h, 1);
    return instance()->_building;
}

QPointF Global::indent(){
    return QPointF(instance()->_indentX, instance()->_indentY);
}

QPointF Global::scale(){
    return QPointF(instance()->_scaleX, instance()->_scaleY);
}

void Global::setIndent(QPointF indent){
    instance()->_indentX = indent.x();
    instance()->_indentY = indent.y();
}

void Global::setScale(QPointF scale){
    instance()->_scaleX = scale.x();
    instance()->_scaleY = scale.y();
}

