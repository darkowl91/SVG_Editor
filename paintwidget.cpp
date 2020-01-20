#include <QLayout>
#include "paintwidget.h"
#include <QSplitter>


// Constructor that builds the main the widget with no parent and adds the components to it in the appropriate layouts.
PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
{
    // Creating buttons with shortcuts.
    this->rectangle = new QPushButton("&Rectangle");
    this->square = new QPushButton("&Square");
    this->circle = new QPushButton("&Circle");
    this->close = new QPushButton("C&lose");
    this->clear = new QPushButton("Cle&ar");
    this->save = new QPushButton("Sa&ve");
    //set icon to button
    this->rectangle->setIcon(QIcon(":icon/resources/rectangle"));
    this->square->setIcon(QIcon(":icon/resources/square"));
    this->circle->setIcon(QIcon(":icon/resources/circle"));
    this->close->setIcon(QIcon(":icon/resources/close"));
    this->clear->setIcon(QIcon(":icon/resources/clear"));
    this->save->setIcon(QIcon(":icon/resources/save"));

    // Creating the options to fill or to draw with effects.
    this->fillOption = new QCheckBox("&Filled");

    // Creating the area where the components will be drawn.
    this->paper = new DrawingArea(this);

    // Creating the colors sliders and labels.
    this->redColorLabel = new QLabel("R");
    this->colorChangerRed = new QSlider(Qt::Horizontal);
    this->colorChangerRed->setRange(0, 255);
    this->colorChangerRed->setTickInterval(1);
    this->greenColorLabel = new QLabel("G");
    this->colorChangerGreen = new QSlider(Qt::Horizontal);
    this->colorChangerGreen->setRange(0, 255);
    this->colorChangerGreen->setTickInterval(1);
    this->blueColorLabel = new QLabel("B");
    this->colorChangerBlue = new QSlider(Qt::Horizontal);
    this->colorChangerBlue->setRange(0, 255);
    this->colorChangerBlue->setTickInterval(1);
    // Creating the area to show how the chosen color looks like.
    this->colorTest = new QLabel();
    // Resizing the main window.
    this->resize(500, 500);

//Creating layouts.///////////////////////////////////////////////
    QWidget *topWidget = new QWidget;                           //
    QHBoxLayout *topWidgetLayout = new QHBoxLayout(topWidget);  //
    topWidgetLayout->addWidget(this->rectangle);                //
    topWidgetLayout->addWidget(this->square);                   //
    topWidgetLayout->addWidget(this->circle);                   //
    topWidgetLayout->addWidget(this->save);                     //
    topWidgetLayout->addWidget(this->clear);                    //
    topWidgetLayout->addWidget(this->close);                    //
    topWidgetLayout->addWidget(this->fillOption);               //
    topWidget->setFixedHeight(50);                              //
 /////////////////////////////////////////////////////////////////
    QVBoxLayout *vLayout = new QVBoxLayout;                     //
    vLayout->addWidget(this->paper);                            //
    vLayout->addStretch(1);                                     //
    this->paper->setMinimumSize(QSize(500, 500));               //
//////////////////////////////////////////////////////////////////
    QHBoxLayout *hLayout = new QHBoxLayout;                     //
    hLayout->addWidget(this->redColorLabel);                    //
    hLayout->addWidget(this->colorChangerRed);                  //
    hLayout->addWidget(this->greenColorLabel);                  //
    hLayout->addWidget(this->colorChangerGreen);                //
    hLayout->addWidget(this->blueColorLabel);                   //
    hLayout->addWidget(this->colorChangerBlue);                 //
//////////////////////////////////////////////////////////////////
    vLayout->addWidget(this->colorTest);                        //
//////////////////////////////////////////////////////////////////
    vLayout->addLayout(hLayout,1);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(topWidget,1);
    mainLayout->addLayout(vLayout,2);
    this->setMaximumSize(QSize(1050, 1010));
    this->setLayout(mainLayout);

// Connecting signals with their corresponding signals.

    // Connecting the close button with the closing of the widget.
    connect(this->close, SIGNAL(clicked()), this, SLOT(close()));

    // Each buttong changes the type of the shape that will be drawn in the drawing area.
    connect(this->rectangle, SIGNAL(clicked()), this, SLOT(drawRectangle()));
    connect(this->square, SIGNAL(clicked()), this, SLOT(drawSquare()));
    connect(this->circle, SIGNAL(clicked()), this, SLOT(drawCircle()));

    // The clear button clears the drawing area, destroying the old pixmap and creating a new one.
    connect(this->clear, SIGNAL(clicked()), this->paper, SLOT(clearPixMap()));

    connect(this->save, SIGNAL(clicked()), this->paper, SLOT(savePixMap()));

    // The area tells the line edit where the area is shown about the area of the newly drawn shape.
    connect(this->paper, SIGNAL(updateArea(double)), this, SLOT(changeAreaValue(double)));

    // Check boxes notify their status to change the way the shapes are drawn.
    connect(this->fillOption, SIGNAL(stateChanged(int)), this, SLOT(drawFilled(int)));

    // Color sliders change the grade of the color that will be used to draw the shape.
    connect(this->colorChangerRed, SIGNAL(valueChanged(int)), this, SLOT(changeRedColor(int)));
    connect(this->colorChangerGreen, SIGNAL(valueChanged(int)), this, SLOT(changeGreenColor(int)));
    connect(this->colorChangerBlue, SIGNAL(valueChanged(int)), this, SLOT(changeBlueColor(int)));
}

// Destructor
PaintWidget::~PaintWidget()
{

}

// Slot that is called when the Rectangle button is clicked to start drawing a rectangle.
void PaintWidget::drawRectangle()
{
    // Sets the type of the shape that will be drawn to "1" which means a rectangle.
    this->paper->setType(1);

}

// Slot that is called when the Square button is clicked to start drawing a square.
void PaintWidget::drawSquare()
{
    // Sets the type of the shape that will be drawn to "2" which means a square.
    this->paper->setType(2);


}

// Slot that is called when the Circle button is clicked to start drawing a circle.
void PaintWidget::drawCircle()
{
    // Sets the type of the shape that will be drawn to "3" which means a circle.
    this->paper->setType(3);


}

// Slot that determines whether the shape will be filled or not depending on the state of the check box.
void PaintWidget::drawFilled(int value)
{
    // If the box is checked.
    if(value == 2)
    {
        this->paper->setShapeFilled(true);
    }
    else this->paper->setShapeFilled(false);
}

// Slot that determines whether the effects will be drawn or not depending on the state of the check box.
void PaintWidget::enableEffects(int value)
{
    // If the box is checked.
    if(value == 2)
    {
        this->paper->setEffectsEnabled(true);

        // Uncheck the filled option.
        this->fillOption->setChecked(false);
    }
    else this->paper->setEffectsEnabled(false);
}

// Slot that changes the value of the red percentage of the color that will be used to draw the shape.
void PaintWidget::changeRedColor(int redValue)
{
    // Setting the value.
    this->paper->setRedColor(redValue);

    // Showing the effect of the change on the color testing label.
    this->colorTest->setStyleSheet("* { background-color: rgb(" + QString::number(redValue) + "," + QString::number(this->paper->getGreenColor()) + "," + QString::number(this->paper->getBlueColor()) + "); }");
}

// Slot that changes the value of the green percentage of the color that will be used to draw the shape.
void PaintWidget::changeGreenColor(int greenValue)
{
    // Setting the value.
    this->paper->setGreenColor(greenValue);

    // Showing the effect of the change on the color testing label.
    this->colorTest->setStyleSheet("* { background-color: rgb(" + QString::number(this->paper->getRedColor()) + "," + QString::number(greenValue) + "," + QString::number(this->paper->getBlueColor()) + "); }");
}// Setting the value.

// Slot that changes the value of the blue percentage of the color that will be used to draw the shape.
void PaintWidget::changeBlueColor(int blueValue)
{
    // Setting the value.
    this->paper->setBlueColor(blueValue);

    // Showing the effect of the change on the color testing label.
    this->colorTest->setStyleSheet("* { background-color: rgb(" + QString::number(this->paper->getRedColor()) + "," + QString::number(this->paper->getGreenColor()) + "," + QString::number(blueValue) + "); }");
}
