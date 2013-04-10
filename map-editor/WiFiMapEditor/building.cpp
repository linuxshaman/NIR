#include "editor.h"

Building::Building(float width, float length, int height, int bottomLevel)
{
    _name = "building";
    _width = width;
    _height = height;
    _length = length;
    _bottomLevel = bottomLevel;
    _levels = new LevelsVector();
    for(int i = 0; i < height; i ++){
        int levelNumber = i + _bottomLevel;
        Level* level = new Level(levelNumber);
        _levels->push_back(level);
    }
}


int Building::getHeight(){
    return _height;
}


QString Building::toJSON(){
    vector<Object*>* spots = new vector<Object*>();
    vector<Object*>* walls = new vector<Object*>();
    vector<Object*>* other = new vector<Object*>();

    for(int i = 0; i < _height; i ++){
        Level* level = _levels->at(i);
        vector<Object*>* objects = level->getLevelObjects();
        for(unsigned int i = 0; i < objects->size(); i ++){
            Object* o = objects->at(i);
            if(o->getName().compare(WI_FI) == 0){
                spots->push_back((WiFiSpot*)o);
            }else if(o->getName().compare(WALL) == 0){
                walls->push_back((Wall*)o);
            }else{
                other->push_back(o);
            }
        }
    }
    QString result = QString("{\"%1\":{\"w\":%2,\"l\":%3,\"h\":%4, ").arg(QString::fromStdString(_name), QString::number(_width),  QString::number(_length),  QString::number(_height));
    result.append(objectsToJSONArrays(walls, spots, other));
    result.append("}}");
    return result;
}

Level* Building::levelAt(int i){
    Level* l = _levels->at(i - _bottomLevel);
    return l;
}

QString Building::objectsToJSONArrays(vector<Object *> *walls, vector<Object *> *spots, vector<Object *> *other){
    QString res = QString();
    QString wifiString = ObjectToJSONArray(spots, "WiFi");
    res.append(wifiString);
    res.append(", ");
    QString wallString = ObjectToJSONArray(walls, "Wall");
    res.append(wallString);
    res.append(", ");
    QString otherString = ObjectToJSONArray(other, "Custom");
    res.append(otherString);
    return res;
}

QString Building::ObjectToJSONArray(vector<Object *> *objects, const char *name){
    QString result = QString("\"%1\":[").arg(QString(name));
    for(unsigned int i = 0; i < objects->size(); i ++){
        Object* o = (Object*)objects->at(i);
        if(i > 0){
            result.append(", ");
        }
        result.append(o->toJSON());
    }
    result.append("]");
    return result;
}
