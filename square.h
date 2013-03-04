#ifndef SQUARE_H
#define SQUARE_H
#include "rectangle.h"

// A Square class that extends Rectangle Class.
class Square : public Rectangle
{
public:
    // Default constructor that builds an empty square.
    Square();

    // A constructor that builds a square with the given attributes.
    Square(int xStart, int yStart, int xEnd, int yEnd, bool f);

    // Copy constructor.
    Square(const Square &orig);

    // Destructor.
    ~Square();

};

#endif // SQUARE_H
