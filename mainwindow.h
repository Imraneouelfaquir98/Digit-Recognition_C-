#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintwidget.h"

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
    void on_pushButton_clicked();

    void on_clearPaintWidget_clicked();

private:
    Ui::MainWindow *ui;
    PaintWidget * paintwidget;
};

#endif // MAINWINDOW_H
