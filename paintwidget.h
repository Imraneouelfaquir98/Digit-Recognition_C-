#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    PaintWidget(QWidget *parent = nullptr);

    bool isModified() const { return modified; }
    void printImage();

public slots:
    void clearImage();
    void print();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    int  averagePixel(int x, int y, int size);

    bool modified;
    bool scribbling;
    QImage image;
    QPoint lastPoint;

};

#endif // PAINTWIDGET_H
