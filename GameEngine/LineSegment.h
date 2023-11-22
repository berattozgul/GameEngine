// LineSegment.h

#pragma once

#include "Point2D.h"
#include "PrimitiveRenderer.h"

class LineSegment {
private:
	Point2D startPoint;
	Point2D endPoint;

public:
	LineSegment(const Point2D& _startPoint, const Point2D& _endPoint);

	Point2D getStartPoint() const;
	Point2D getEndPoint() const;
	void setStartPoint(const Point2D& point);
	void setEndPoint(const Point2D& point);

	void draw(PrimitiveRenderer& renderer, sf::Color color, bool useIncrementalAlgorithm = false);


private:
	void drawDefault(PrimitiveRenderer& renderer, sf::Color color);

	void drawIncremental(PrimitiveRenderer& renderer, sf::Color color);
};
