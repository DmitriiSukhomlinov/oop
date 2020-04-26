#include "Shapes.h"

#include <complex>

namespace oop {

static const double pi = 3.14159265358979323846;

/***************************/
/*          Shape          */
/***************************/

int Shape::SHAPES_COUNT = 0;

Shape::Shape() {
    increment();
}

Shape::Shape(const Shape& ) {
    increment();
}

Shape::~Shape() {
    decrement();
}

Shape& Shape::operator=(const Shape& ) {
    increment();
    return *this;
}

int Shape::getCount() {
    return SHAPES_COUNT;
}

void Shape::increment() {
    SHAPES_COUNT++;
}

void Shape::decrement() {
    SHAPES_COUNT--;
}


/***************************/
/*          Point          */
/***************************/

Point::Point(const int _x, const int _y) 
    : Named("Point"), x(_x), y(_y) {}

Point::~Point() {}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return x;
}

std::string Point::getInfo() const {
    return Named::getInfo();
}

std::string Point::getAdditionaInfo() const {
    return "Coordinates: X = " + std::to_string(x) + ", Y = " + std::to_string(y) + ".";
}

/***************************/
/*          Circle         */
/***************************/

Circle::Circle(const Point& _center, const int _radius)
    : Named("Circle"), center(_center), radius(_radius) {}

Circle::~Circle() {}

std::string Circle::getInfo() const {
    return Named::getInfo();
}

std::string Circle::getAdditionaInfo() const {
    return "The center coordinate: X = " + std::to_string(center.getX()) + " Y = "
        + std::to_string(center.getY()) + ", radius = " + std::to_string(radius) 
        + ", area = " + std::to_string(radius * radius * pi) + ".";
}

/***************************/
/*           Rect          */
/***************************/

Rect::Rect(const Point& _bottomLeft, const Point& _topRight)
    : Named("Rect"), bottomLeft(_bottomLeft), topRight(_topRight) {}

Rect::~Rect() {}

std::string Rect::getInfo() const {
    return Named::getInfo();
}

std::string Rect::getAdditionaInfo() const {
    const int bottomLeftX = bottomLeft.getX();
    const int bottomLeftY = bottomLeft.getY();
    const int topRightX = topRight.getX();
    const int topRightY = topRight.getY();
    const int area = std::abs(bottomLeftY - topRightY) * std::abs(bottomLeftX - topRightX);
    return "The bottom-left point coordinate:  X = " + std::to_string(bottomLeftX) + " Y = "
        + std::to_string(bottomLeftY) + ", the top-right point coordinate:  X = "
        + std::to_string(topRightX) + " Y = " + std::to_string(topRightY) +
        ", area = " + std::to_string(area) + ".";
}

/***************************/
/*          Square         */
/***************************/

Square::Square(const Point& _bottomLeft, const int _edge)
    : Named("Square"), bottomLeft(_bottomLeft), edge(_edge) {}

Square::~Square() {}

std::string Square::getInfo() const {
    return Named::getInfo();
}

std::string Square::getAdditionaInfo() const {
    return "The bottom-left point coordinate:  X = " + std::to_string(bottomLeft.getX()) + " Y = "
        + std::to_string(bottomLeft.getY()) + ", the edge length = " + std::to_string(edge) +
        ", area = " + std::to_string(edge * edge) + ".";
}

/***************************/
/*        Polyline         */
/***************************/

Polyline::Polyline(const Container<Point>& _nodes)
    : Named("Polyline"), nodes(_nodes) {}

Polyline::~Polyline() {}

void Polyline::addPoint(Point const& point) {
    nodes.addNew(point);
}

std::string Polyline::getInfo() const {
    return Named::getInfo();
}

std::string Polyline::getAdditionaInfo() const {
    std::string result =  "The following points are connected with lines:";
    double length = 0;
    for (int i = 0; i < nodes.getSize(); i++) {
        const Point currentPoint = nodes.getByIndex(i);
        result += " " + std::to_string(i + 1) + ") X = " + std::to_string(currentPoint.getX()) 
            + ", Y = " + std::to_string(currentPoint.getY()) + ";";
        if (i != 0) {
            const Point previousPoint = nodes.getByIndex(i - 1);
            const int deltaX = previousPoint.getX() - currentPoint.getX();
            const int deltaY = previousPoint.getY() - currentPoint.getY();
            length += std::sqrt(pow(deltaX, 2) + pow(deltaY, 2));
        }
    }
    result += " length = " + std::to_string(length) + ".";
    return result;
}

/***************************/
/*         Polygon         */
/***************************/

Polygon::Polygon(const Container<Point>& _anglePositions)
    : Named("Polygon"), anglePositions(_anglePositions) {}

Polygon::~Polygon() {}

std::string Polygon::getInfo() const {
    return Named::getInfo();
}

std::string Polygon::getAdditionaInfo() const {
    std::string result = "Angles have the following coordinates:";
    for (int i = 0; i < anglePositions.getSize(); i++) {
        const Point& point = anglePositions.getByIndex(i);
        result += " " + std::to_string(i + 1) + ") X = " + std::to_string(point.getX()) + ", Y = " + std::to_string(point.getY()) + ";";
    }
    result.pop_back();
    result += ".";
    return result;
}

}