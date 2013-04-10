#-------------------------------------------------
#
# Project created by QtCreator 2013-03-07T05:00:14
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WiFiMapEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    building.cpp \
    level.cpp \
    object.cpp \
    jsonobject.cpp \
    jsonhelper.cpp \
    qtjson.cpp \
    global.cpp \
    glwidget.cpp \
    fxrect.cpp

HEADERS  += mainwindow.h \
    editor.h \
    building.h \
    level.h \
    object.h \
    jsonobject.h \
    fileHelper.h \
    jsonhelper.h \
    qtjson.h \
    global.h \
    glwidget.h \
    fxrect.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
