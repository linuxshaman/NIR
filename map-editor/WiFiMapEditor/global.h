#ifndef GLOBAL_H
#define GLOBAL_H

#include "editor.h"
#include "jsonhelper.h"
#include "fileHelper.h"
#include <QPoint>

class Global
{
    Building* _building;
    QString* _path;
    QString* _imagePath;
    float _indentX;
    float _indentY;
    float _scaleX;
    float _scaleY;
private:
    Global();
    static Global* instance();
    void open();
    void save();
public:
    static void Open(QString path);
    static void SaveAs(QString path);
    static void Save();
    static void New(QString path, QString imagePath);
    static void Export(QString path);
    static Building* building();
    static QString imagePath();
    static Building* createBuilding(float w, float l, int h);
    static QPointF indent();
    static QPointF scale();
    static void setIndent(QPointF indent);
    static void setScale(QPointF scale);
};

#endif // GLOBAL_H
