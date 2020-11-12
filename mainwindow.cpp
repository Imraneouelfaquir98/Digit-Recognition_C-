#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include<cstdio>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    paintwidget = new PaintWidget;
//    ui->paintWidget = paintwidget;
    ui->stackedWidget->insertWidget(0,paintwidget);
    ui->stackedWidget->setCurrentIndex(0);
//    ui->paintWidget->setCentralWidget(paintwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    paintwidget->printImage();
}

void MainWindow::on_clearPaintWidget_clicked()
{
    paintwidget->clearImage();
}
