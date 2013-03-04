#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"

// Rectangle class that extends shape adding extra attributes and methods.
class Rectangle : public Shape
{
public:
    // Default constructor that creates and an empty shape.
    Rectangle();

    // A constructor that builds a rectangle with the given attributes.
    Rectangle(int xStart, int yStart, int xEnd, int yEnd, bool f);

    // Copy Constructor that copies the original Rectangle.
    Rectangle(const Rectangle &orig);

    // Destructor of a rectangle.
    ~Rectangle();

    // Setters of width and height.
    void setWidth(int w);
    void setHeight(int h);

    // Getters of width and height.
    int getWidth();
    int getHeight();

    // A virtual method that calculates the area of the rectangle.
    virtual int getArea();
    
    
protected:
    // Width and height of rectangle.
    int width;
    int height;
    
};

#endif // RECTANGLE_H
