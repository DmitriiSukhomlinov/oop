#pragma once

#include "Shapes.h"

namespace oop {

class ShapeFactory {
public:
    ShapeFactory(const int randomNumbersRange);

    enum ShapeType {
        Point = 0,
        Circle,
        Rect,
        Square,
        Polyline,
        Polygon
    };

    Shape* createShape(const ShapeType type) const;
    Shape* createRandomShape() const;
    
private:
    oop::Point getPointWithRandomPoints() const;
    Container<oop::Point> getContainerFilledWithRandomPoints(const int size) const;
    int getRandomCoordinate() const;
    int getRandomFracturePointNumber() const;

    int randomNumbersRange;
};

}