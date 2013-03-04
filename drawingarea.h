#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QFileDialog>
#include "shape.h"

// A class that extends QWidget and defines an area where you can draw shapes.
class DrawingArea : public QWidget
{
    Q_OBJECT
public:

    // Constructor that creates a new Drawing area.
    DrawingArea(QWidget *parent = 0);

    // Destructor
    ~DrawingArea();

    // Setters
    void setType(int value);
    void setShapeFilled(bool value);
    void setEffectsEnabled(bool value);
    void setRedColor(int redValue);
    void setGreenColor(int greenValue);
    void setBlueColor(int blueValue);

    // Getters
    int getType();
    bool isShapeFilled();
    bool effectsEnabled();
    int getRedColor();
    int getGreenColor();
    int getBlueColor();

protected:
    // Overriding events to enable drawing.

    // Invoked when mouse is clicked.
    virtual void mousePressEvent(QMouseEvent *event);

    // Invoked when mouse is moving in the widget while pressed.
     virtual void mouseMoveEvent(QMouseEvent *event);

     // Invoked when mouse button is released.
     virtual void mouseReleaseEvent(QMouseEvent *event);

     // Invoked when widget is resized or repainted.
     virtual void paintEvent(QPaintEvent *event);


public slots:
     // Slot that clears the drawing area by destroying the old pixmap and creating a new one.
     void clearPixMap();

     // Slot that saves the drawn pixmap.
     void savePixMap();


signals:
     // A signal that is sent to the line edit that shows the area of the drawn shape.
    void updateArea(double newArea);

private:
    // A pixmap to keep the drawn shapes in it.
    QPixmap *history;

    // A painter that paints in the pixmap
    QPainter *historyPainter;

    // The shape that we draw.
    Shape *s;

    // Boolean that determines whether effects are enabled or not.
    bool enabledEffects;

    // An integer that starts drawing.
    int trigger;

    // Determines the type of the shape that will be drawn
    // 1 = Rectangle
    // 2 = Square
    // 3 = Circle
    int type;

    // Boolean that determines whether a shape is filled or not.
    bool shapeFilled;

    // Integers that represent the value of each color of the RGB.
    int redColor;
    int greenColor;
    int blueColor;
};

#endif // DRAWINGAREA_H
