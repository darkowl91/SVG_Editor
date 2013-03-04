#include "shape.h"

// Default constructor of shape.
Shape::Shape()
{
    this->xStart = 0;
    this->yStart = 0;
    this->xEnd = 0;
    this->yEnd = 0;
    this->filled = false;
}

// Constructor that builds a shape with the given values.
Shape::Shape(int xStart, int yStart, int xEnd, int yEnd, bool f)
{
    this->xStart = xStart;
    this->yStart = yStart;
    this->xEnd = xEnd;
    this->yEnd = yEnd;
    this->filled = f;
}

// Copy Constructor that copies values from the original shape.
Shape::Shape(const Shape &orig)
{
    this->xStart = orig.xStart;
    this->yStart = orig.yStart;
    this->xEnd = orig.xEnd;
    this->yEnd = orig.yEnd;
    this->filled = orig.filled;
}

// Destructor.
Shape::~Shape()
{

}

// Sets the x coordinate of the starting point of the shape.
void Shape::setXStart(int x)
{
    this->xStart = x;
}

// Sets the y coordinate of the starting point of the shape.
void Shape::setYStart(int y)
{
    this->yStart = y;
}

// Sets the x coordinate of the ending point of the shape.
void Shape::setXEnd(int x)
{
    this->xEnd = x;
}

// Sets the y coordinate of the ending point of the shape.
void Shape::setYEnd(int y)
{
    this->yEnd = y;
}

// Fill or unfill the shape.
void Shape::setFilled(bool f)
{
    this->filled = f;
}

// Gets the x coordinate of the starting point of the shape.
int Shape::getXStart()
{
    return this->xStart;
}

// Gets the y coordinate of the starting point of the shape.
int Shape::getYStart()
{
    return this->yStart;
}

// Gets the x coordinate of the ending point of the shape.
int Shape::getXEnd()
{
    return this->xEnd;
}

// Gets the y coordinate of the ending point of the shape.
int Shape::getYEnd()
{
    return this->yEnd;
}

// Shows if the shape is filled or not.
bool Shape::isFilled()
{
    return this->filled;
}
