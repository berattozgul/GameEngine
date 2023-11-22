// LineSegment.cpp

#include "LineSegment.h"

LineSegment::LineSegment(const Point2D& _startPoint, const Point2D& _endPoint)
	: startPoint(_startPoint), endPoint(_endPoint) {}

Point2D LineSegment::getStartPoint() const {
	return startPoint;
}

Point2D LineSegment::getEndPoint() const {
	return endPoint;
}

void LineSegment::setStartPoint(const Point2D& point) {
	startPoint = point;
}

void LineSegment::setEndPoint(const Point2D& point) {
	endPoint = point;
}

void LineSegment::drawIncremental(PrimitiveRenderer& renderer, sf::Color color) {
	int x1 = static_cast<int>(startPoint.getX());
	int y1 = static_cast<int>(startPoint.getY());
	int x2 = static_cast<int>(endPoint.getX());
	int y2 = static_cast<int>(endPoint.getY());
	renderer.drawLineIncremental(x1, y1, x2, y2, color);
	// Connect the last point to the first point to close the polygon
	renderer.drawLineIncremental(x2, y2, x1, y1, color);
}
void LineSegment::drawDefault(PrimitiveRenderer& renderer, sf::Color color) {
	renderer.drawLine(startPoint.getX(), startPoint.getY(), endPoint.getX(), endPoint.getY(), 2.f, color);
}


void LineSegment::draw(PrimitiveRenderer& renderer, sf::Color color, bool useIncrementalAlgorithm) {
	if (useIncrementalAlgorithm) {
		drawIncremental(renderer, color);
	}
	else {
		drawDefault(renderer, color);
	}
}