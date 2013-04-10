#ifndef BUILDING_H
#define BUILDING_H

#include "editor.h"

class Building: public JSONObject
{
    int _height;
    LevelsVector* _levels;
    int _bottomLevel;
private:
     QString objectsToJSONArrays(vector<Object*>* walls, vector<Object*>* spots, vector<Object*>* other);
     QString ObjectToJSONArray(vector<Object*>* objects, const char* name);
public:
    int getHeight();
    Building(float width, float length, int height, int bottomLevel);
    virtual QString toJSON();

    Level* levelAt(int i);

    int size(){
        return _levels->size();
    }
};

#endif // BUILDING_H
