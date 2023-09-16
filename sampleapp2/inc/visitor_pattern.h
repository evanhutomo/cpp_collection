#include <iostream>

// Abstract base class for shapes
class Shape {
public:
    virtual void accept(class Visitor& visitor) = 0;
};

// Concrete Circle class
class Circle;

// Concrete Rectangle class
class Rectangle;

// Abstract base class for the Visitor
class Visitor {
public:
    virtual void visit(Circle& circle) = 0;
    virtual void visit(Rectangle& rectangle) = 0;
};

// Concrete visitor class for area calculation
class AreaVisitor : public Visitor {
public:
    void visit(Circle& circle) override;
    void visit(Rectangle& rectangle) override;
};

// Concrete Circle class
class Circle : public Shape {
public:
    Circle(double radius) : radius(radius) {}

    double getRadius() const {
        return radius;
    }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

private:
    double radius;
};

// Concrete Rectangle class
class Rectangle : public Shape {
public:
    Rectangle(double length, double width) : length(length), width(width) {}

    double getLength() const {
        return length;
    }

    double getWidth() const {
        return width;
    }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

private:
    double length;
    double width;
};