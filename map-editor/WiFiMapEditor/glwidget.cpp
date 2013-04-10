#include "glwidget.h"
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include "global.h"
#include "mainwindow.h"

#define SCROLLABLE_PART (1.0f / 4.0f)
#define SCROLL_STEP 10

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    image(NULL),
    hasTexture(false),
    scrollsPositions(QSize(0,0)),
    scrollMaximum(0),
    _drawEdit(false)
{
    state = NO_STATE;
    updateRect = false;
}

void GLWidget::initializeGL()
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
    initTextures();
}

void GLWidget::paintGL()
{
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    if(!hasTexture){
        if(image){
            QImage im(image->width(), image->height(), QImage::Format_ARGB32);

            QPainter painter(&im);
            painter.setCompositionMode(QPainter::CompositionMode_Source);
            painter.fillRect(im.rect(), Qt::transparent);
            painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
            painter.drawImage( 0, 0, *image);
            painter.end();

            QImage ima = QGLWidget::convertToGLFormat(im);


            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, 4, ima.width(), ima.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, ima.bits());
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

            hasTexture = true;
        }
    }else{

        QSize imageSize = image->size();
        QSize widgetSize = this->size();


        float x = ((float)scrollsPositions.width() / (float)imageSize.width());
        float y = ((scrollMaximum -  (float)scrollsPositions.height()) / (float)imageSize.height());

        float w = x + ((float)widgetSize.width() / (float)imageSize.width());
        float h = y + ((float)widgetSize.height() / (float)imageSize.height());

        glEnable(GL_ALPHA_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindTexture(GL_TEXTURE_2D, texture);

        glEnable(GL_TEXTURE_2D);


        glBegin(GL_QUADS);
            glTexCoord2f(x, y); glVertex2f(-1, -1);
            glTexCoord2f(w, y); glVertex2f(1, -1);
            glTexCoord2f(w, h); glVertex2f(1, 1);
            glTexCoord2f(x, h); glVertex2f(-1, 1);
        glEnd();

        drawObjects();
        if(_drawEdit){
            drawEdit();
        }

        glDisable(GL_TEXTURE_2D);

        glDisable(GL_ALPHA_TEST);
        glDisable(GL_BLEND);
    }
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWidget::mousePressEvent(QMouseEvent *)
{
    _drawEdit = true;
    QPoint pos = mapFromGlobal(QCursor::pos());
    rect = fxRect(toGlobal(pos));
    if(state == WIFI_STATE){
        updateRect = true;
    }
}


void GLWidget::mouseMoveEvent(QMouseEvent *)
{
    if(state == WIFI_STATE) return;
    QPoint pos = mapFromGlobal(QCursor::pos());
    rect.update(toGlobal(pos));
    float areaWidth = size().width() * SCROLLABLE_PART;
    if(pos.x() <= areaWidth){
        moveScrollLeft();
    }else if(pos.x() >= size().width() - areaWidth){
        moveScrolRight();
    }
    float areaHeight = size().height() * SCROLLABLE_PART;
    if(pos.y() <= areaHeight){
        moveScrollTop();
    }else if(pos.y() >= size().height() - areaHeight){
        moveScrollBottom();
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *)
{
    if(state == WIFI_STATE)return;
    QPointF pos = mapFromGlobal(QCursor::pos());
    rect.update(toGlobal(pos));
    if(state == WALL_STATE){
        _drawEdit = false;
        Building* b = Global::building();
        QPointF scale = Global::scale();
        switch (state) {
        case WALL_STATE:
            b->levelAt(1)->createWall(rect.origin().x(), rect.origin().y(), rect.width() / scale.x(), rect.height() / scale.y());
            break;
        default:
            break;
        }
    }
}

QPointF GLWidget::translateCoord(QPointF pos)
{
    float hx = this->size().width() / 2.0f;
    float hy = this->size().height() / 2.0f;

    float x = pos.x();
    float y = pos.y();

    QPointF zero = getZero();

    x = (x - zero.x()) / hx;
    y = (y - zero.y()) / hy;

    return QPointF(x, y);
}

void GLWidget::initTextures()
{
    initTexture(":/img/building.png", &buildingTexture);
    initTexture(":/img/wifi.png", &wifiTexture);
    initTexture(":/img/wall.png",&wallTexture);
    initTexture(":/img/custom.png", &customTexture);
}

void GLWidget::initTexture(QString path, GLuint* tex)
{
    QImage baseImage;
    baseImage.load(path, "PNG");

    QImage imageDrawTo(baseImage.width(), baseImage.height(), QImage::Format_ARGB32);
    QPainter painter(&imageDrawTo);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(imageDrawTo.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage( 0, 0, baseImage);
    painter.end();

    QImage textureImage = QGLWidget::convertToGLFormat(imageDrawTo);

    glGenTextures(1, tex);
    glBindTexture(GL_TEXTURE_2D, *tex);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, textureImage.width(), textureImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.bits());
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}

void GLWidget::moveScrollLeft()
{
    int value = horizontalScroller->value();
    value -= SCROLL_STEP;
    if(value <= horizontalScroller->minimum()){
        value = horizontalScroller->minimum();
    }
    horizontalScroller->setValue(value);
}

void GLWidget::moveScrolRight()
{
    int value = horizontalScroller->value();
    value += SCROLL_STEP;
    if(value >= horizontalScroller->maximum()){
        value = horizontalScroller->maximum();
    }
    horizontalScroller->setValue(value);
}

void GLWidget::moveScrollTop()
{
    int value = verticalScroller->value();
    value -= SCROLL_STEP;
    if(value <= verticalScroller->minimum()){
        value = verticalScroller->minimum();
    }
    verticalScroller->setValue(value);
}

void GLWidget::moveScrollBottom()
{
    int value = verticalScroller->value();
    value += SCROLL_STEP;
    if(value >= verticalScroller->maximum()){
        value = verticalScroller->maximum();
    }
    verticalScroller->setValue(value);
}

QPointF GLWidget::toGlobal(QPointF p){
    if(!image)return QPointF(0,0);
    float x =  p.x() + scrollsPositions.width();
    float y = ((scrollMaximum -  (float)scrollsPositions.height())) + (this->size().height() - p.y());
    return QPointF(x, y);
}

void GLWidget::drawObjects(){
    Building* b = Global::building();
    if(b){
        drawBuilding(b);
        Level* l =  b->levelAt(1);
        vector<Object*>* objects = l->getLevelObjects();
        for(unsigned int i = 0; i < objects->size(); i ++){
            Object* o = objects->at(i);
            switch (o->type) {
            case WALL_OBJECT:
                drawWall(dynamic_cast<Wall*>(o));
                break;
            case WIFI_OBJECT:
                drawWifi(dynamic_cast<WiFiSpot*>(o));
                break;
            case CUSTOM_OBJECT:
                drawCustom(o);
                break;
            default:
                break;
            }
        }
    }
}

void GLWidget::drawEdit(){
    switch(state){
    case BUILDING_STATE:
        glBindTexture(GL_TEXTURE_2D, buildingTexture);
        break;
    case WALL_STATE:
        glBindTexture(GL_TEXTURE_2D, wallTexture);
        break;
    case CUSTOM_STATE:
        glBindTexture(GL_TEXTURE_2D, customTexture);
        break;
    case WIFI_STATE:
    {
        glBindTexture(GL_TEXTURE_2D, wifiTexture);
        if(updateRect){
            QPointF pos = rect.origin();
            rect = fxRect(pos - QPointF(25, 25), pos + QPointF(25, 25));
            updateRect = false;
        }
        break;
    }
    default:
        return;
    }
    drawRect(rect.points());
}

QPointF GLWidget::getZero(){
    QPointF zero = QPointF(this->size().width() / 2.0f, this->size().height() / 2.0f);
    return toGlobal(zero);
}

void GLWidget::drawRect(QPointF *points){
    QPointF* drawPoints = new QPointF[4];
    for(int i = 0; i < 4; i ++){
        drawPoints[i] = translateCoord(points[i]);
    }
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);glVertex2f(drawPoints[0].x(), drawPoints[0].y());
        glTexCoord2f(1, 0);glVertex2f(drawPoints[1].x(), drawPoints[1].y());
        glTexCoord2f(1, 1);glVertex2f(drawPoints[2].x(), drawPoints[2].y());
        glTexCoord2f(0, 1);glVertex2f(drawPoints[3].x(), drawPoints[3].y());
    glEnd();
}

fxRect GLWidget::getRect(){
    return rect;
}

void GLWidget::drawBuilding(Building* b){
    glBindTexture(GL_TEXTURE_2D, buildingTexture);
    QPointF scale = Global::scale();
    QPointF bSize = QPointF(b->getWidth() * scale.x(), b->getLength() * scale.y());
    fxRect r = fxRect(Global::indent(), Global::indent() + QPointF(bSize.x(), bSize.y()));
    drawRect(r.points());
}

void GLWidget::drawWall(Wall *wall)
{
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    QPointF scale = Global::scale();
    QPointF bSize = QPointF(wall->getWidth() * scale.x(), wall->getLength() * scale.y());
    fxRect r = fxRect(wall->pos(), wall->pos() + QPointF(bSize.x(), bSize.y()));
    drawRect(r.points());
}

void GLWidget::drawWifi(WiFiSpot *wifi)
{
    glBindTexture(GL_TEXTURE_2D, wifiTexture);
    QPointF qpoint25 = QPointF(25, 25);
    fxRect r = fxRect(wifi->pos() - qpoint25, wifi->pos() + qpoint25);
    drawRect(r.points());
}

void GLWidget::drawCustom(Object *custom)
{
    glBindTexture(GL_TEXTURE_2D, customTexture);
    QPointF scale = Global::scale();
    QPointF bSize = QPointF(custom->getWidth() * scale.x(), custom->getLength() * scale.y());
    fxRect rect = fxRect(custom->pos(), custom->pos() + QPointF(bSize.x(), bSize.y()));
    drawRect(rect.points());
}

void GLWidget::endEdit(){
    _drawEdit = false;
}

