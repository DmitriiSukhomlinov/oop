#pragma once

#include "Base.h"

#include "Container.h"

namespace oop {

class Shape : public virtual Printable {
public:
    Shape();
    Shape(const Shape& other);
    virtual ~Shape();
    Shape& operator=(const Shape& other);

   static int getCount();
   static void increment();
   static void decrement();

private:
    static int SHAPES_COUNT;
};

class Point : public Named, public Shape {
public:
    Point(const int x, const int y);
    virtual ~Point();

    int getX() const;
    int getY() const;

private:
    std::string getInfo() const override;
    std::string getAdditionaInfo() const override;

    int x;
    int y;
};

class Circle : public Named, public Shape {
public:
    Circle(const Point& center, const int radius);
    virtual ~Circle();

private:
    std::string getInfo() const override;
    std::string getAdditionaInfo() const override;

    Point center;
    int radius;
};

class Rect : public Named, public Shape {
public:
    Rect(const Point& bottomLeft, const Point& topRight);
    virtual ~Rect();

private:
    std::string getInfo() const override;
    std::string getAdditionaInfo() const override;

    Point bottomLeft;
    Point topRight;
};

class Square : public Named, public Shape {
public:
    Square(const Point& bottomLeft, const int edge);
    virtual ~Square();

private:
    std::string getInfo() const override;
    std::string getAdditionaInfo() const override;

    Point bottomLeft;
    int edge;
};

class Polyline : public Named, public Shape {
public:
    Polyline(const Container<Point>& nodes);
    virtual ~Polyline();

    void addPoint(Point const& point);

private:
    std::string getInfo() const override;
    std::string getAdditionaInfo() const override;

    Container<Point> nodes;
};

class Polygon : public Named, public Shape {
public:
    Polygon(const Container<Point>& anglePositions);
    virtual ~Polygon();

private:
    std::string getInfo() const override;
    std::string getAdditionaInfo() const override;

    Container<Point> anglePositions;
};

}
