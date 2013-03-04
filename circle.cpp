#include "circle.h"
#include <math.h>

// Defaule constructor that builds an empty circle, it calls the base class constructor first.
Circle::Circle()
        :Shape()
{
    this->radius = 0;
}

// Constructor that builds a circle with the given attributes.
Circle::Circle(int xStart, int yStart, int xEnd, int yEnd, bool f)
        :Shape(xStart, yStart, xEnd, yEnd, f)
{
    // Calculating the radius of a circle using pythagore.
    int x = this->xEnd - this->xStart;
    int y = this->yEnd - this->yStart;
    this->radius = sqrt(pow(x, 2) + pow(x, 2));
}

// Copy constructor that copies the original circle.
Circle::Circle(const Circle &orig)
        : Shape(orig.xStart, orig.yStart, orig.xEnd, orig.yEnd, orig.filled)
{
    this->radius = orig.radius;
}

// Destructor
Circle::~Circle()
{
}

// Calculates the area of a circle.
double Circle::getArea()
{
    return pow(this->radius, 2) * PI;
}


