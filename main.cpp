#include <QtGui/QApplication>
#include "square.h"
#include <QtGui/QPushButton>
#include "paintwidget.h"

// Main method where the program starts.
int main(int argc, char *argv[])
{
    // Start Qt application with the given arguments.
    QApplication a(argc, argv);

    // Create new painting widget.
    PaintWidget *w = new PaintWidget;

    // Show the widget.
    w->show();

    // Return 0 if program finishes with no crashes.
    return a.exec();
}
