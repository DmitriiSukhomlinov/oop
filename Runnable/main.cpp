#include "Container.h"
#include "Base.h"
#include "Shapes.h"
#include "ShapeFactory.h"
#include <iostream>

std::ostream& operator << (std::ostream& s, const oop::Printable& print) {
    return s << print.getInfo() << std::endl;
}

int main() {

    oop::ShapeFactory factory(100);
    oop::Container<oop::Shape*> shapeContainer;
    while (shapeContainer.getSize() < 20) {
        oop::Shape* newShape;
        try {
            newShape = factory.createRandomShape();
        } catch (const std::exception& ex) {
            std::cout << ex.what();
            continue;
        }
        shapeContainer.addNew(newShape);
    }
    std::cout << "Shapes were created: " << oop::Shape::getCount() << std::endl;

    for (int i = 0; i < shapeContainer.getSize(); i++) {
        oop::Shape* shape;
        try {
            shape = shapeContainer.getByIndex(i);
        } catch (const std::exception& ex) {
            std::cout << ex.what();
            continue;
        }

        std::cout << i + 1 << ") " << *shape;
    }

    for (int i = 0; i < shapeContainer.getSize(); i++) {
        delete shapeContainer.getByIndex(i);
    }

    std::cout << "Shapes are left: " << oop::Shape::getCount() << std::endl;

    return 0;
}