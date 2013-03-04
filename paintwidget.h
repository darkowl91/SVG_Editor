#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <drawingarea.h>

// The main widget in the application, it extends the QWidget class.
class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    // Constructor that takes the parent of the widget, which is zero by default.
    PaintWidget(QWidget *parent = 0);

    // Destructor of the main Window.
    ~PaintWidget();

    // Slots that recieve signals to change the values of the shape that the user will start drawing.
private slots:

    // Each slot is called when the user chooses the coreponding shape that he / she wants to draw.
    void drawRectangle();
    void drawSquare();
    void drawCircle();

    // A slot that changes the calculated area of the drawn shape.
    void changeAreaValue(double newArea);

    // A slot that is called when the fill option is changed.
    void drawFilled(int value);

    // A slot that is called when the effects option is changed.
    void enableEffects(int value);

    // Slots that are called when the user moves the sliders that control the color combination of RGB.
    void changeRedColor(int redValue);
    void changeGreenColor(int GreenValue);
    void changeBlueColor(int blueValue);

    // Components that are contained in the main widget
private:

    // Buttons to choose which shape to draw, clear drawing area and close the application
    QPushButton *rectangle;
    QPushButton *square;
    QPushButton *circle;
    QPushButton *close;
    QPushButton *clear;
    QPushButton *save;

    // Labels
    QLabel *showingAreaLabel;
    QLabel *redColorLabel;
    QLabel *greenColorLabel;
    QLabel *blueColorLabel;
    QLabel *colorTest;

    // QLineEdit to show tha area of the drawn shape.
    QLineEdit *showingArea;

    // Check boxes so the user can choose whether to draw filled shapes or using the effects.
    QCheckBox *fillOption;
    QCheckBox *effectsOption;

    // Sliders that control the RGB combination to change the color of the shape.
    QSlider *colorChangerRed;
    QSlider *colorChangerGreen;
    QSlider *colorChangerBlue;

    // An extended QWidget to draw shapes on.
    DrawingArea *paper;
};

#endif // PAINTWIDGET_H
