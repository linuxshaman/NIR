#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QScrollBar>
#include "fxrect.h"
#include <editor.h>
#include <QLineEdit>

enum WidgetState{
    BUILDING_STATE,
    WIFI_STATE,
    WALL_STATE,
    CUSTOM_STATE,
    EDIT_STATE,
    NO_STATE
};

class GLWidget : public QGLWidget
{
    Q_OBJECT
private:
    fxRect rect;
    bool _drawEdit;
    GLuint texture;
    GLuint wifiTexture;
    GLuint wallTexture;
    GLuint customTexture;
    GLuint buildingTexture;
    void initTextures();
    void initTexture(QString path, GLuint* tex);
    void moveScrollLeft();
    void moveScrolRight();
    void moveScrollTop();
    void moveScrollBottom();
    bool updateRect;
public:
    explicit GLWidget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    QTimer timer;
    bool hasTexture;
    QImage* image;
    QSize scrollsPositions;
    float scrollMaximum;
    WidgetState state;
    QScrollBar* verticalScroller;
    QScrollBar* horizontalScroller;
    fxRect getRect();
    QLineEdit* nameEdit;
    void endEdit();
protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    QPointF translateCoord(QPointF pos);
    QPointF toGlobal(QPointF p);
    void drawObjects();
    void drawEdit();
    void drawRect(QPointF* points);
    QPointF getZero();

    void drawBuilding(Building* b);
    void drawWall(Wall* wall);
    void drawWifi(WiFiSpot* wifi);
    void drawCustom(Object* custom);
};

#endif // GLWIDGET_H
