#include "square.h"

// Default constructor that creates and empty square, it calls the base class constructor first.
Square::Square()
        :Rectangle()
{
}

// Constructor that builds a square with the given parameters.
Square::Square(int xStart, int yStart, int xEnd, int yEnd, bool f)
        :Rectangle(xStart, yStart, xEnd, yEnd, f)
{
    // Calculating the width.
    this->width = (this->xEnd - this->xStart);
    // The height equals the width.
    this->height = (this->width);
}

// Copy constructors that makes a copy of the original square.
Square::Square(const Square &orig)
        : Rectangle(orig.xStart, orig.yStart, orig.xEnd, orig.yEnd, orig.filled)
{
    this->width = orig.width;
    this->height = orig.height;
}

// Destructor of a square.
Square::~Square()
{
}


