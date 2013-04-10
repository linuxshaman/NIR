#ifndef JSONOBJECT_H
#define JSONOBJECT_H

class JSONObject
{
protected:
    float _width;
    float _length;
    string _name;
public:
    JSONObject();

    float getWidth();
    float getLength();
    string getName();
    void setWidth(float width);
    void setLength(float length);
    void setName(string name);

    virtual QString toJSON() = 0;
};

#endif // JSONOBJECT_H
