#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"

// A class that defines a circle and extends shape.
class Circle : public Shape
{
public:
    // Default constructor that builds an empty Circle.
    Circle();

    // A constructor that builds a circle with the given arguments.
    Circle(int xStart, int yStart, int xEnd, int yEnd, bool f);

    // Copy Constructor that copies the original Circle.
    Circle(const Circle &orig);

    // Destructor.
    ~Circle();

    // Setter of the radius.
    void setRadius(double r);

    // Getter of the radius.
    double getRadius();

    // Calculates area of the circle.
    double getArea();

private:
    // The PI constant used to calculate the area of any circle.
    double static const PI = 3.1415926535;

    // The radius of a circle.
    double radius;

};

#endif // CIRCLE_H
