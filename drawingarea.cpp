#include <QPainter>
#include "rectangle.h"
#include "square.h"
#include "circle.h"
#include "drawingarea.h"
#include <QSvgGenerator>

// Constructor that builds a drawing area that we draw in it.
DrawingArea::DrawingArea(QWidget *parent)
        :QWidget(parent)
{
        // Create a pixmap that we keep history of drawing in it.
        this->history = new QPixmap(1000, 1000);

        // Initialize the pixmap.
        this->history->fill(Qt::transparent);

        // Create a painter that paints in the pixmap.
        this->historyPainter = new QPainter(this->history);

        // Drawing the background.
        this->historyPainter->setBrush(QColor(205, 201, 201));
        this->historyPainter->drawRect(0, 0, 1000, 1000);

        // Creating the shape that will be drawn.
        s = new Shape;

        // Set the shape to be unfilled and with no effects at the beginning.
        shapeFilled = false;
        enabledEffects = false;

        // Set the beginning color as black.
        this->redColor = 0;
        this->blueColor = 0;
        this->greenColor = 0;
}

// Destructor.
DrawingArea::~DrawingArea()
{
    delete s;
    delete history;
    delete historyPainter;
}

// Set the type of the shape that will be drawn.
void DrawingArea::setType(int value)
{
    this->type = value;
}

// Get the type of the shape that is being drawn.
int DrawingArea::getType()
{
    return this->type;
}

// Set if the shape if filled or not.
void DrawingArea::setShapeFilled(bool value)
{
    this->shapeFilled = value;
    this->s->setFilled(value);
}

// Check if the shape is filled or not.
bool DrawingArea::isShapeFilled()
{
    return this->shapeFilled;
}

// Set if the drawing with effects is enabled or not.
void DrawingArea::setEffectsEnabled(bool value)
{
    this->enabledEffects = value;
}

// Check if effects are enabled or not.
bool DrawingArea::effectsEnabled()
{
    return this->enabledEffects;
}

// Set the of the red color.
void DrawingArea::setRedColor(int redValue)
{
    this->redColor = redValue;
}

// Get the value of the red color.
int DrawingArea::getRedColor()
{
    return this->redColor;
}

// Set the value of the green color.
void DrawingArea::setGreenColor(int greenValue)
{
    this->greenColor = greenValue;
}

// Get the value of the green color.
int DrawingArea::getGreenColor()
{
    return this->greenColor;
}

// Set the value of the blue color.
void DrawingArea::setBlueColor(int blueValue)
{
    this->blueColor = blueValue;
}

// Get the value of the blue color.
int DrawingArea::getBlueColor()
{
    return this->blueColor;
}

// When the mouse is clicked, the starting point of the shape is captured.
void DrawingArea::mousePressEvent(QMouseEvent *event)
{
    // Set the starting x and y.
    this->s->setXStart(event->pos().x());
    this->s->setYStart(event->pos().y());
    // Set the initial area to zero.
    emit updateArea(0);
}

// When the mouse is moved, the ending point of the shape is captured and the new shape is drawn.
void DrawingArea::mouseMoveEvent(QMouseEvent *event)
{
    // Allow drawing.
    this->trigger = 1;
    // Set the ending x and y.
    this->s->setXEnd(event->pos().x());
    this->s->setYEnd(event->pos().y());
    // Repaint the drawing area and adding the new shape.
    this->repaint();
}

// When mouse button is released the drawn shape will be drawn in the history pixmap.
void DrawingArea::mouseReleaseEvent(QMouseEvent *event)
{
    // Setting the pen of the painter to the chosen color.
    this->historyPainter->setPen(QColor(this->getRedColor(), this->getGreenColor(), this->getBlueColor()));
    // If shape is filled then we use no pen and use a colored brush.
    if(shapeFilled)
        {
            this->historyPainter->setPen(QColor(this->getRedColor(), this->getGreenColor(), this->getBlueColor()));
            this->historyPainter->setBrush(QColor(this->getRedColor(), this->getGreenColor(), this->getBlueColor()));
        }
    // If type is 1 = rectangle, draw rectangle.
    if(type == 1)
        {
            // Create a rectangle that is drawn.
            Rectangle *rect =  new Rectangle(s->getXStart(), s->getYStart(), s->getXEnd(), s->getYEnd(), s->isFilled());;

            // Draw in the history pixmap.
            this->historyPainter->drawRect(rect->getXStart(), rect->getYStart(), rect->getXEnd() - rect->getXStart(), rect->getYEnd() - rect->getYStart());

            // Calculate the area and update it.
            emit updateArea(rect->getArea());

            // Delete the rectangle as it is of no use.
            delete rect;
        }
    // Else if type is 2 = square, draw square.
        else if(type == 2)
        {
            // Create a square that is drawn.
            Square *sqr = new Square(s->getXStart(), s->getYStart(), s->getXEnd(), s->getYEnd(), s->isFilled());
            // Determine which way the square will be drawn (top left, top right, bottom left or bottom right).

            // Bottom right.
               if(sqr->getYEnd() > sqr->getYStart() && sqr->getXEnd() > sqr->getXStart())
                   // Draw in the history pixmap.
            this->historyPainter->drawRect(sqr->getXStart(), sqr->getYStart(), sqr->getXEnd() - sqr->getXStart(), sqr->getXEnd() - sqr->getXStart());

               // Top right.
            else if(sqr->getYEnd() < sqr->getYStart() && sqr->getXEnd() > sqr->getXStart())
                // Draw in the history pixmap.
                this->historyPainter->drawRect(sqr->getXStart(), sqr->getYStart(), sqr->getXEnd() - sqr->getXStart(), sqr->getXStart() - sqr->getXEnd());

            // Top Left.
            else if(sqr->getYEnd() < sqr->getYStart() && sqr->getXEnd() < sqr->getXStart())
                // Draw in the history pixmap.
                this->historyPainter->drawRect(sqr->getXStart(), sqr->getYStart(),  sqr->getXEnd() - sqr->getXStart(), sqr->getXEnd() - sqr->getXStart());

            // Bottom Left.
            // Draw in the history pixmap.
            else this->historyPainter->drawRect(sqr->getXStart(), sqr->getYStart(), sqr->getXEnd() - sqr->getXStart(), sqr->getXStart() - sqr->getXEnd());

            // Calculate the area and update it.
            emit updateArea(sqr->getArea());

            // Delete the square as it is of no use.
            delete sqr;
        }

        // Else if the type = 3 = Circle, draw circle.
        else if(type == 3)
        {
            // Create a circle that is drawn.
            Circle *cir = new Circle(s->getXStart(), s->getYStart(), s->getXEnd(), s->getYEnd(), s->isFilled());

            // draw in the history pixmap.
            this->historyPainter->drawEllipse(QPoint(cir->getXStart(), cir->getYStart()), cir->getXEnd() - cir->getXStart(), cir->getXEnd() - cir->getXStart());

            // Calculate the area and update it.
            emit updateArea(cir->getArea());

            // Delete the circle as it is of no use.
            delete cir;
        }
        // Repaint the old shapes adding the new one.
    this->repaint();

    // Reseting the painter to have pen and no brush (Default).
    this->historyPainter->setPen(QColor(this->getRedColor(), this->getGreenColor(), this->getBlueColor()));
    this->historyPainter->setBrush(Qt::NoBrush);
}

// Called whenever the widget is created, resized or repainted.
void DrawingArea::paintEvent(QPaintEvent *event)
{
    // Creating a painter.
        QPainter w(this);

        // Drawing the back ground of the drawin area.
        w.setBrush(QColor(205, 201, 201));
        w.drawRect(0, 0, 1000, 1000);

        // Setting the pen to the chosen color.
        w.setPen(QColor(this->getRedColor(), this->getGreenColor(), this->getBlueColor()));

        // Draw the pixmap history.
        w.drawPixmap(0, 0, *(this->history));

        // Setting the pen to the chosen color.
        this->historyPainter->setPen(QColor(this->getRedColor(),this->getGreenColor(),this->getBlueColor()));

        // If drawing is enabled.
    if(this->trigger == 1)
    {
        // If shape is filled enable brush other wise use no brush.
        if(shapeFilled)
            w.setBrush(QColor(this->getRedColor(),this->getGreenColor(),this->getBlueColor()));
        else
            w.setBrush(Qt::NoBrush);

        // If type is 1 = rectangle, draw rectangle.
        if(type == 1)
        {
            // Draw rectangle on the drawing area.
            w.drawRect(s->getXStart(), s->getYStart(), s->getXEnd() - s->getXStart(), s->getYEnd() - s->getYStart());

            // If effects enabled draw them in the history to keep them.
            if(enabledEffects)
                this->historyPainter->drawRect(s->getXStart(), s->getYStart(), s->getXEnd() - s->getXStart(), s->getYEnd() - s->getYStart());
        }
        // If type is 2 = square, draw square.
        else if(type == 2)
        {
            // Determine which way the square will be drawn (top left, top right, bottom left or bottom right).

            // Bottom right.
            if(s->getYEnd() > s->getYStart() && s->getXEnd() > s->getXStart())
            {
                // Draw square on the drawing area.
                w.drawRect(s->getXStart(), s->getYStart(), s->getXEnd() - s->getXStart(), s->getXEnd() - s->getXStart());

                // If effects enabled draw them in the history to keep them.
            if(enabledEffects)
                this->historyPainter->drawRect(s->getXStart(), s->getYStart(), s->getXEnd() - s->getXStart(), s->getXEnd() - s->getXStart());
            }

            // Top right.
            else if(s->getYEnd() < s->getYStart() && s->getXEnd() > s->getXStart())
               {
                // Draw square on the drawing area.
                w.drawRect(s->getXStart(), s->getYStart(), s->getXEnd() - s->getXStart(), s->getXStart() - s->getXEnd());

                // If effects enabled draw them in the history to keep them.
                if(enabledEffects)
                    this->historyPainter->drawRect(s->getXStart(), s->getYStart(), s->getXEnd() - s->getXStart(), s->getXStart() - s->getXEnd());
            }

            // Top left.
            else if(s->getYEnd() < s->getYStart() && s->getXEnd() < s->getXStart())
            {
                // Draw square on the drawing area.
                w.drawRect(s->getXStart(), s->getYStart(),  s->getXEnd() - s->getXStart(), s->getXEnd() - s->getXStart());

                // If effects enabled draw them in the history to keep them.
                if(enabledEffects)
                    this->historyPainter->drawRect(s->getXStart(), s->getYStart(),  s->getXEnd() - s->getXStart(), s->getXEnd() - s->getXStart());
            }

            // Bottom left.
            else
            {
                // Draw square on the drawing area.
                w.drawRect(s->getXStart(), s->getYStart(), s->getXEnd() - s->getXStart(), s->getXStart() - s->getXEnd());

                // If effects enabled draw them in the history to keep them.
                if(enabledEffects)
                    this->historyPainter->drawRect(s->getXStart(), s->getYStart(), s->getXEnd() - s->getXStart(), s->getXStart() - s->getXEnd());
            }
        }

        // If type is 2 = circle, draw circle.
        else if(type == 3)
        {
            // Draw circle on the drawing area.
           w.drawEllipse(QPoint(s->getXStart(), s->getYStart()), s->getXEnd() - s->getXStart(), s->getXEnd() - s->getXStart());

           // If effects enabled draw them in the history to keep them.
                if(enabledEffects)
                    this->historyPainter->drawEllipse(QPoint(s->getXStart(), s->getYStart()), s->getXEnd() - s->getXStart(), s->getXEnd() - s->getXStart());
        }
    }
    // Disable drawing after drawing.
    this->trigger = 0;
}

// Clears the history pixmap so the drawing area is empty.
void DrawingArea::clearPixMap()
{
    // Destroy the history painter.
    this->historyPainter->~QPainter();

    // Destroy the history pixmap.
    this->history->~QPixmap();

    // Create a new history pixmap.
    this->history = new QPixmap(1000, 1000);

    // Initialize.
    this->history->fill(Qt::transparent);

    // Create a new history painter.
    this->historyPainter = new QPainter(this->history);

    // Repaint the drawin area.
    this->repaint();
}

// Saves the drawing in jpg format in the given path supplied by the file chooser.
void DrawingArea::savePixMap()
{
    // Get the path of the saving destination.
////    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"), "/SuperPicture",
       //                                          tr("Images (*.jpg)"));

    // Saving the pixmap.
//    this->history->save(fileName, "jpg", 50);





    QString newPath = QFileDialog::getSaveFileName(this, tr("Save SVG"),
             "/SuperPicture", tr("SVG files (*.svg)"));

         if (newPath.isEmpty())
             return;

         //path = newPath;

         QSvgGenerator generator;
         generator.setFileName(newPath);
         generator.setSize(QSize(1000,1000));
         generator.setViewBox(QRect(0, 0, 1000, 1000));
         generator.setTitle(tr("SVG Generator Example Drawing"));
         generator.setDescription(tr("An SVG drawing created by the SVG Generator "
                                     "Example provided with Qt."));
         QPainter painter;
         painter.begin(&generator);

        // displayWidget->paint(painter);
         painter.drawPixmap(0, 0, *(this->history));
         //DrawingArea->paintEvent(painter);
         painter.end();








}
