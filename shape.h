#ifndef SHAPE_H
#define SHAPE_H

// A class that defines the main attributes of any shape.
class Shape
{
public:
    // Constructs a shape with zero values.
    Shape();

    // Constructs a shape with the given arguments.
    Shape(int xStart, int yStart, int xEnd, int yEnd, bool f);

    // Copy Constructor.
    Shape(const Shape &orig);

    // Destroyes a shape.
    ~Shape();

    // Setters for the shape attributes.
    void setXStart(int x);
    void setYStart(int y);
    void setXEnd(int x);
    void setYEnd(int y);
    void setFilled(bool f);

    // Getters for the shape attributes.
    int getXStart();
    int getYStart();
    int getXEnd();
    int getYEnd();
    bool isFilled();

protected:
    // The x and y indicies where the shape starts.
    int xStart;
    int yStart;

    // The x and y indicies where the shape ends.
    int xEnd;
    int yEnd;

    // Determines whether the shape is filled or not.
    bool filled;
};

#endif // SHAPE_H

