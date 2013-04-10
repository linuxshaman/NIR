#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QFile>
#include <QTextStream>

static void saveToFile(QString fileName, QString data){
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out<<data;
    file.close();
}

static QString readFile(QString fileName){
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString text = in.readAll();
    file.close();
    return text;
}

#endif // FILEHELPER_H
