#include "editor.h"

JSONObject::JSONObject()
{
}

float JSONObject::getWidth(){
    return _width;
}

float JSONObject::getLength(){
    return _length;
}

string JSONObject::getName(){
    return _name;
}

void JSONObject::setWidth(float width){
    _width = width;
}

void JSONObject::setLength(float length){
    _length = length;
}

void JSONObject::setName(string name){
    _name = name;
}
