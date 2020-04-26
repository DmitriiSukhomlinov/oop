#include "ShapeFactory.h"

#include <ctime>

namespace oop {

ShapeFactory::ShapeFactory(const int _randomNumbersRange)
	: randomNumbersRange (_randomNumbersRange) {
	std::srand((unsigned int)std::time(NULL));
}

Shape* ShapeFactory::createShape(const ShapeType type) const {
	Shape* resultShape = nullptr;
	switch (type) {
	case Point: {
		const int x = getRandomCoordinate();
		const int y = getRandomCoordinate();
		resultShape = new oop::Point(x, y);
		break;
		}
	case Circle: {
		const oop::Point center = getPointWithRandomPoints();
		const int radius = getRandomCoordinate();
		resultShape = new oop::Circle(center, radius);
		break;
		}
	case Rect: {
		const oop::Point bottomLeft = getPointWithRandomPoints();
		const oop::Point topRight = getPointWithRandomPoints();
		resultShape = new oop::Rect(bottomLeft, topRight);
		break;
		}
	case Square: {
		const oop::Point bottomLeft = getPointWithRandomPoints();
		const int edge = getRandomCoordinate();
		resultShape = new oop::Square(bottomLeft, edge);
		break;
		}
	case Polyline: {
		const int nodesNumder = getRandomFracturePointNumber();
		oop::Container<oop::Point> nodesContainer
			= getContainerFilledWithRandomPoints(nodesNumder);
		resultShape = new oop::Polyline(nodesContainer);
		break;
		}
	case Polygon: {
		const int anglesNumder = getRandomFracturePointNumber();
		oop::Container<oop::Point> aglesContainer 
			= getContainerFilledWithRandomPoints(anglesNumder);
		resultShape = new oop::Polygon(aglesContainer);
		break;
	}
	default:
		throw std::runtime_error("ShapeFactory::createShape(const ShapeType type): incorrect type.");
		break;
	}

    return resultShape;
}

Shape* ShapeFactory::createRandomShape() const {
	return createShape(static_cast<ShapeType>(std::rand() % 6));
}

oop::Point ShapeFactory::getPointWithRandomPoints() const {
	const int x = getRandomCoordinate();
	const int y = getRandomCoordinate();
	return oop::Point(x, y);
}

Container<oop::Point> ShapeFactory::getContainerFilledWithRandomPoints(const int size) const {
	oop::Container<oop::Point> result;
	for (int i = 0; i < size; i++) {
		const int x = getRandomCoordinate();
		const int y = getRandomCoordinate();
		result.addNew(oop::Point(x, y));
	}

	return result;
}

int ShapeFactory::getRandomCoordinate() const {
	// Из диапазона [-randomNumbersRange; randomNumbersRange], чтобы не получались уж слишком большие числа
	return std::rand() % (randomNumbersRange * 2 + 1) - randomNumbersRange;
}

int ShapeFactory::getRandomFracturePointNumber() const {
	// Не больше 10
	return std::rand() % 10 + 1;
}

}