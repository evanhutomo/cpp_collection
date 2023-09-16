#include "visitor_pattern.h"

// Definitions for AreaVisitor's visit methods
void AreaVisitor::visit(Circle& circle) {
    double area = 3.14159 * circle.getRadius() * circle.getRadius();
    std::cout << "Area of Circle: " << area << std::endl;
}

void AreaVisitor::visit(Rectangle& rectangle) {
    double area = rectangle.getLength() * rectangle.getWidth();
    std::cout << "Area of Rectangle: " << area << std::endl;
}


