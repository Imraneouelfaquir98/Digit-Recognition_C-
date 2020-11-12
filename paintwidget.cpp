
#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#endif
#endif

#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    resizeImage(&image, QSize(260, 260));
}

void PaintWidget::printImage()
{
    FILE * f;
    f = fopen ("image.cpp", "w");
    if(f == NULL)
        printf("Impossible d'ouvrir le fichier en écriture !\n");
    else
    {
        int size = 5;
        for(int i=0; i<image.width()-size; i+=size)
        {
            for(int j=0; j<image.height()-size; j+=size)
            {
//                fprintf(f , " %d",averagePixel(j,i,size));
                int val = averagePixel(j,i,size);
                if(val == 0)
                    fprintf(f , " *");
                else
                    fprintf(f , "  ");
            }
            fprintf(f , " \n");
        }
        fclose(f);
    }
}

void PaintWidget::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void PaintWidget::print()
{
    QPrinter printer(QPrinter::HighResolution);
    QPainter painter(&printer);
    QRect rect = painter.viewport();
    QSize size = image.size();
    size.scale(rect.size(), Qt::KeepAspectRatio);
    painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
    painter.setWindow(image.rect());
    painter.drawImage(0, 0, image);
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        scribbling = false;
    }
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void PaintWidget::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    printf("width = %d, height = %d\n",image.width(),image.height());
    printf("byte per line = %d, depth = %d\n",image.bytesPerLine(),image.depth());
    printf("dot per Meter X = %d, Y = %d\n",image.dotsPerMeterX(),image.dotsPerMeterY());
    painter.setPen(QPen(QColor("black"), 14, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = 9;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void PaintWidget::resizeImage(QImage *image, const QSize &newSize)
{
    QImage newImage(newSize, QImage::Format_Mono);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

int PaintWidget::averagePixel(int x, int y, int size)
{
    int average = 0;
    for(int i = x; i<x+size; i++){
        for(int j=y; j<y+size; j++){
            average += image.pixelIndex(i,j);
        }
    }
    if(average*2 > size)
        return 1;
    else
        return 0;
}
