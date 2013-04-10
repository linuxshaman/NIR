#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QResizeEvent>
#include <QErrorMessage>
#include <QWheelEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initScrollers();
    initUi();
    ui->editorWidget->verticalScroller = ui->verticalScrollBar;
    ui->editorWidget->horizontalScroller = ui->horizontalScrollBar;
    ui->editorWidget->nameEdit = ui->nameEdit;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    Global::Save();
    QApplication::quit();
}

void MainWindow::on_actionNew_triggered()
{
    ui->editorWidget->timer.stop();
    QString path = QFileDialog::getSaveFileName(this, tr("Create Project"), QDir::homePath());
    if(path.compare("") != 0){
        QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Image File"), QDir::homePath(), tr("Images (*.png *.jpg)"));
        Global::New(path, imagePath);
        loadImage();
        ui->buildingButton->setEnabled(true);
    }
    ui->editorWidget->timer.start(16);
}

void MainWindow::on_actionOpen_triggered()
{
    ui->editorWidget->timer.stop();
    QString path = QFileDialog::getOpenFileName(this, tr("Open Project"), QDir::homePath(), tr("Project (*.prowfm)"));
    if(path.compare("") != 0){
        Global::Open(path);
        loadImage();
        ui->buildingButton->setEnabled(true);
        if(Global::building()){
            ui->wallButton->setEnabled(true);
            ui->wifiButton->setEnabled(true);
            ui->customButton->setEnabled(true);
        }
    }
    ui->editorWidget->timer.start(16);
    Building* b = Global::building();
    if(b){
        ui->widthEdit->setText(QString::number(b->getWidth()));
        ui->lengthEdit->setText(QString::number(b->getLength()));
        ui->heightEdit->setText(QString::number(b->getHeight()));
    }
}

void MainWindow::on_actionSave_triggered()
{
    Global::Save();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Create Project"), QDir::homePath());
    if(path.compare("") != 0){
        Global::SaveAs(path);
    }
}



void MainWindow::initScrollers(){
    QSize size = QSize(0, 0);
    if(ui->editorWidget->image){
        size = ui->editorWidget->image->size();
        QSize widgetSize = ui->editorWidget->size();
        size-= widgetSize;
    }
    ui->verticalScrollBar->setMinimum(0);
    ui->horizontalScrollBar->setMinimum(0);

    ui->verticalScrollBar->setMaximum(size.height());
    ui->horizontalScrollBar->setMaximum(size.width());
    ui->editorWidget->scrollMaximum = ui->verticalScrollBar->maximum();
}

void MainWindow::loadImage(){
    ui->editorWidget->image = new QImage();
    ui->editorWidget->image->load(Global::imagePath());
    initScrollers();
}

void MainWindow::on_verticalScrollBar_valueChanged(int value)
{

    ui->editorWidget->scrollsPositions.setHeight(value);
}

void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    ui->editorWidget->scrollsPositions.setWidth(value);
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    initScrollers();
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
    QPoint p = ui->editorWidget->mapFromGlobal(QCursor::pos());
    if(p.x() > 0 && p.y() > 0){
        if(p.x() <= ui->editorWidget->size().width() && p.y() <= ui->editorWidget->size().height()){
            int value = ui->verticalScrollBar->value();
            if(e->delta() > 0){
                value-= 10;
            }else{
                value += 10;
            }
            if(value <= ui->verticalScrollBar->minimum()){
                value = ui->verticalScrollBar->minimum();
            }else if(value >= ui->verticalScrollBar->maximum()){
                value = ui->verticalScrollBar->maximum();
            }
            ui->verticalScrollBar->setValue(value);
        }
    }
}

void MainWindow::initUi(){
    ui->buildingButton->setDisabled(true);
    ui->wallButton->setDisabled(true);
    ui->wifiButton->setDisabled(true);
    ui->customButton->setDisabled(true);
    ui->widthEdit->setDisabled(true);
    ui->lengthEdit->setDisabled(true);
    ui->heightEdit->setDisabled(true);
    ui->currentLevelSpinBox->setMaximum(0);
    ui->currentLevelSpinBox->setMinimum(0);
    ui->currentLevelSpinBox->setDisabled(true);
    ui->createButton->setDisabled(true);
}

void MainWindow::on_buildingButton_clicked(bool checked)
{
    ui->wallButton->setChecked(false);
    ui->wifiButton->setChecked(false);
    ui->customButton->setChecked(false);


    ui->widthEdit->setEnabled(checked);
    ui->heightEdit->setEnabled(checked);
    ui->lengthEdit->setEnabled(checked);
    ui->createButton->setEnabled(checked);

    if(checked){
        ui->editorWidget->state = BUILDING_STATE;
        ui->wallButton->setDisabled(true);
        ui->wifiButton->setDisabled(true);
        ui->customButton->setDisabled(true);
    }else{
        ui->wallButton->setEnabled(false);
        ui->wifiButton->setEnabled(false);
        ui->customButton->setEnabled(false);
    }
}

void MainWindow::on_createButton_clicked()
{
    bool result = true;
    float w = ui->widthEdit->text().toFloat(&result);
    float l = 0;
    int h = 0;
    if(result){
        l = ui->lengthEdit->text().toFloat(&result);
        if(result){
            h = ui->heightEdit->text().toInt(&result);
            if(result){
                Global::createBuilding(w, l, h);
                ui->buildingButton->setChecked(false);
                ui->widthEdit->setDisabled(true);
                ui->heightEdit->setDisabled(true);
                ui->lengthEdit->setDisabled(true);
                ui->createButton->setDisabled(true);
                Global::Save();
            }else{
                QErrorMessage* error = new QErrorMessage(this);
                error->showMessage("Height is not integer value!");
            }
        }else{
            QErrorMessage* error = new QErrorMessage(this);
            error->showMessage("Length is not float value!");
        }
    }else{
        QErrorMessage* error = new QErrorMessage(this);
        error->showMessage("Width is not float value");
    }
    Global::createBuilding(w, l, h);
    fxRect rect = ui->editorWidget->getRect();
    Global::setIndent(rect.origin());
    float scaleX = rect.width() / w;
    float scaleY = rect.height() / l;
    Global::setScale(QPointF(scaleX, scaleY));
    ui->editorWidget->state = NO_STATE;
}

void MainWindow::on_wallButton_clicked(bool checked)
{
    if(checked){
        ui->buildingButton->setChecked(false);
        ui->wifiButton->setChecked(false);
        ui->customButton->setChecked(false);
        ui->editorWidget->state = WALL_STATE;
    }else{
        ui->editorWidget->state = NO_STATE;
    }
}

void MainWindow::on_wifiButton_clicked(bool checked)
{
    if(checked){
        ui->buildingButton->setChecked(false);
        ui->wallButton->setChecked(false);
        ui->customButton->setChecked(false);
        ui->nameEdit->setEnabled(true);
        ui->editorWidget->state = WIFI_STATE;
    }else{
        ui->editorWidget->state = NO_STATE;
        ui->nameEdit->setDisabled(true);
    }
}

void MainWindow::on_customButton_clicked(bool checked)
{
    if(checked){
        ui->buildingButton->setChecked(false);
        ui->wallButton->setChecked(false);
        ui->wifiButton->setChecked(false);
        ui->editorWidget->state = CUSTOM_STATE;
        ui->nameEdit->setEnabled(true);
    }else{
        ui->editorWidget->state = NO_STATE;
        ui->nameEdit->setDisabled(true);
    }
}

void MainWindow::on_nameEdit_editingFinished()
{
    if(ui->nameEdit->text().length() != 0){
        QString name = ui->nameEdit->text();
        Building* b = Global::building();
        if(b){
            switch (ui->editorWidget->state) {
            case WIFI_STATE:
            {
                QPointF pos = ui->editorWidget->getRect().origin() + QPointF(25, 25);
                b->levelAt(1)->createWifi(pos.x(), pos.y(), name.toStdString());
                break;
            }
            case CUSTOM_STATE:
            {
                QPointF scale = Global::scale();
                float x = ui->editorWidget->getRect().origin().x();
                float y = ui->editorWidget->getRect().origin().y();
                float width = ui->editorWidget->getRect().width() / scale.x();
                float length = ui->editorWidget->getRect().height() / scale.y();
                b->levelAt(1)->createCustomObject(x, y, width, length, name.toStdString());
                break;
            }
            default:
                break;
            }
        }
        ui->nameEdit->setDisabled(true);
        ui->editorWidget->endEdit();
    }

}

void MainWindow::on_actionExport_triggered()
{
    ui->editorWidget->timer.stop();
    QString path = QFileDialog::getSaveFileName(this, tr("Export"), QDir::homePath());
    if(path.compare("") != 0){
        Global::Export(path);
    }
    ui->editorWidget->timer.start(16);
}
