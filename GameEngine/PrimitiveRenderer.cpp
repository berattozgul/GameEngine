//PrimitiveRenderer.cpp
#include "PrimitiveRenderer.h"
#include "Point2D.h"
#include "LineSegment.h"
#include <math.h>
#include <SFML/Graphics.hpp>
#include <vector>


PrimitiveRenderer::PrimitiveRenderer(sf::RenderWindow& _window) : window(_window) {}

void PrimitiveRenderer::drawRectangle(float x, float y, float width, float height, sf::Color color) {
	sf::RectangleShape rectangle(sf::Vector2f(width, height));
	rectangle.setPosition(x, y);
	rectangle.setFillColor(color);
	window.draw(rectangle);
}

void PrimitiveRenderer::drawCircle(float x, float y, float radius, sf::Color color) {
	sf::CircleShape circle(radius);
	circle.setPosition(x - radius, y - radius);
	circle.setFillColor(color);
	window.draw(circle);
}

void PrimitiveRenderer::drawLine(float x1, float y1, float x2, float y2, float thickness, sf::Color color) {
	sf::RectangleShape line(sf::Vector2f(getDistance(x1, y1, x2, y2), thickness));
	line.setPosition(x1, y1);
	line.setFillColor(color);
	line.setRotation(getAngle(x1, y1, x2, y2));
	window.draw(line);
}

void PrimitiveRenderer::drawPoint(float x, float y, sf::Color color) {
	sf::CircleShape point(2.f);
	point.setPosition(x, y);
	point.setFillColor(color);
	window.draw(point);
}

void PrimitiveRenderer::drawLineIncremental(int x1, int y1, int x2, int y2, sf::Color color) {
	int dx = x2 - x1;
	int dy = y2 - y1;

	int steps = std::max(std::abs(dx), std::abs(dy));

	float xIncrement = static_cast<float>(dx) / static_cast<float>(steps);
	float yIncrement = static_cast<float>(dy) / static_cast<float>(steps);

	float x = static_cast<float>(x1);
	float y = static_cast<float>(y1);

	for (int i = 0; i <= steps; ++i) {
		drawPixel(static_cast<int>(x + 0.5f), static_cast<int>(y + 0.5f), color);
		x += xIncrement;
		y += yIncrement;
	}
}
float PrimitiveRenderer::getDistance(float x1, float y1, float x2, float y2) {
	return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float PrimitiveRenderer::getAngle(float x1, float y1, float x2, float y2) {
	const float pi = 3.14159265358979323846f;
	return std::atan2(y2 - y1, x2 - x1) * (180.f / pi);
}
void PrimitiveRenderer::drawPixel(int x, int y, sf::Color color) {
	sf::RectangleShape pixel(sf::Vector2f(1.f, 1.f));
	pixel.setPosition(static_cast<float>(x), static_cast<float>(y));
	pixel.setFillColor(color);
	window.draw(pixel);
}
void PrimitiveRenderer::drawPolyline(const std::vector<Point2D>& points, sf::Color color, bool isClosed) {
	if (points.size() < 2) {
		// Polyline must have at least two points
		return;
	}

	for (size_t i = 0; i < points.size() - 1; ++i) {
		const Point2D& startPoint = points[i];
		const Point2D& endPoint = points[i + 1];
		drawLine(startPoint.getX(), startPoint.getY(), endPoint.getX(), endPoint.getY(), 2.f, color);
	}

	// Connect the last point to the first point to close the polyline
	if (isClosed && points.size() > 2) {
		const Point2D& firstPoint = points.front();
		const Point2D& lastPoint = points.back();
		drawLine(lastPoint.getX(), lastPoint.getY(), firstPoint.getX(), firstPoint.getY(), 2.f, color);
	}
}

void PrimitiveRenderer::drawPolyline(const std::vector<LineSegment>& segments, sf::Color color, bool isClosed) {
	for (const auto& segment : segments) {
		const Point2D& startPoint = segment.getStartPoint();
		const Point2D& endPoint = segment.getEndPoint();
		drawLine(startPoint.getX(), startPoint.getY(), endPoint.getX(), endPoint.getY(), 2.f, color);
	}

	// Connect the last segment to the first segment to close the polyline
	if (isClosed && !segments.empty()) {
		const Point2D& firstPoint = segments.front().getStartPoint();
		const Point2D& lastPoint = segments.back().getEndPoint();
		drawLine(lastPoint.getX(), lastPoint.getY(), firstPoint.getX(), firstPoint.getY(), 2.f, color);
	}
}