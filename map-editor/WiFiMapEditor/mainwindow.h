#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "global.h"
#include <QImage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionExit_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_verticalScrollBar_valueChanged(int value);

    void on_horizontalScrollBar_valueChanged(int value);

    virtual void resizeEvent(QResizeEvent *);
    virtual void wheelEvent(QWheelEvent *e);

    void on_buildingButton_clicked(bool checked);

    void on_createButton_clicked();

    void on_wallButton_clicked(bool checked);

    void on_wifiButton_clicked(bool checked);

    void on_customButton_clicked(bool checked);

    void on_createButton_clicked(bool checked);

    void on_nameEdit_editingFinished();

    void on_actionExport_triggered();

private:
    Ui::MainWindow *ui;

    void initScrollers();
    void loadImage();
    void initUi();
};

#endif // MAINWINDOW_H
