#include "rectangle.h"
#include "stdlib.h"

// Default constructor that calls the base class constructor to build an empty shape.
Rectangle::Rectangle()
        :Shape()
{

}

// Constructor that builds a rectangle with the given attributes, it first calls the base class constructor.
Rectangle::Rectangle(int xStart, int yStart, int xEnd, int yEnd, bool f)
        :Shape(xStart, yStart, xEnd, yEnd, f)
{
    // Calculating the width and the height of the rectangle.
    this->width = this->xEnd - this->xStart;
    this->height = this->yEnd - this->yStart;
}

// Copy constructor that copies the orignial rectangle.
Rectangle::Rectangle(const Rectangle &orig)
        : Shape(orig.xStart, orig.yStart, orig.xEnd, orig.yEnd, orig.filled)
{
    this->width = orig.width;
    this->height = orig.height;
}

// Destructor of a rectangle.
Rectangle::~Rectangle()
{

}

// Sets the width of a rectangle.
void Rectangle::setWidth(int w)
{
    this->width = w;
}

// Sets the height of a rectangle.
void Rectangle::setHeight(int h)
{
    this->height = h;
}

// Gets the width of a rectangle.
int Rectangle::getWidth()
{
    return this->width;
}

// Gets the height of a rectangle.
int Rectangle::getHeight()
{
    return this->height;
}

// Calculates the area of the rectangle.
int Rectangle::getArea()
{
    return abs (this->width * this->height);
}
