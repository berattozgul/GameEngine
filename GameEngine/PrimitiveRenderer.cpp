//PrimitiveRenderer.cpp
#include "PrimitiveRenderer.h"
#include "Point2D.h"
#include "LineSegment.h"
#include <math.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stack>


PrimitiveRenderer::PrimitiveRenderer(sf::RenderWindow& _window) : window(_window) {
	renderTexture.create(window.getSize().x, window.getSize().y);
}

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

void PrimitiveRenderer::drawEllipse(float centerX, float centerY, float rx, float ry, sf::Color color) {
	int cx = static_cast<int>(centerX + 0.5f); // Merkez x koordinatý
	int cy = static_cast<int>(centerY + 0.5f); // Merkez y koordinatý

	int rxRound = static_cast<int>(rx + 0.5f);
	int ryRound = static_cast<int>(ry + 0.5f);

	int rxSquared = rxRound * rxRound;
	int rySquared = ryRound * ryRound;

	int x = 0, y = ryRound;
	int px = 0, py = 2 * rxSquared * y;

	// Ýlk bölgenin karar parametresi
	int p1 = rySquared - rxSquared * ryRound + 0.25 * rxSquared;

	// Ýlk set simetrik olarak çizilmiþ noktalar
	drawEllipsePoints(cx, cy, x, y, color);

	// Bölge 1
	while (px < py) {
		x++;
		px += 2 * rySquared;
		if (p1 < 0) {
			p1 += rySquared + px;
		}
		else {
			y--;
			py -= 2 * rxSquared;
			p1 += rySquared + px - py;
		}
		// Bölge 1'deki noktalarý çiz
		drawEllipsePoints(cx, cy, x, y, color);
	}

	// Bölge 2
	p1 = rySquared * (x + 0.5) * (x + 0.5) + rxSquared * (y - 1) * (y - 1) - rxSquared * rySquared;
	while (y > 0) {
		y--;
		py -= 2 * rxSquared;
		if (p1 > 0) {
			p1 += rxSquared - py;
		}
		else {
			x++;
			px += 2 * rySquared;
			p1 += rxSquared - py + px;
		}
		// Bölge 2'deki noktalarý çiz
		drawEllipsePoints(cx, cy, x, y, color);
	}
}

void PrimitiveRenderer::drawCircleSymmetrical(float centerX, float centerY, float radius, sf::Color color) {
	int cx = static_cast<int>(centerX + 0.5f); // Center x-coordinate
	int cy = static_cast<int>(centerY + 0.5f); // Center y-coordinate

	int r = static_cast<int>(radius + 0.5f);
	int currentX = r, currentY = 0;
	int err = 0;

	// Initial point at the top-right of the circle
	drawCirclePointsSymmetrical(cx, cy, currentX, currentY, color);

	while (currentX >= currentY) {
		// Move to the next point on the circle
		currentY++;

		// Mid-point is inside or on the perimeter
		if (err <= 0) {
			err += 2 * currentY + 1;
		}
		// Mid-point is outside the perimeter
		else {
			currentX--;
			err += 2 * (currentY - currentX) + 1;
		}

		// All the perimeter points have already been printed
		if (currentX < currentY) {
			break;
		}

		// Printing the generated point and its 7 other symmetrical points
		drawCirclePointsSymmetrical(cx, cy, currentX, currentY, color);
	}
}

void PrimitiveRenderer::drawCirclePointsSymmetrical(int cx, int cy, int x, int y, sf::Color color) {
	drawPixel(cx + x, cy - y, color);
	drawPixel(cx + y, cy - x, color);
	drawPixel(cx + x, cy + y, color);
	drawPixel(cx + y, cy + x, color);
	drawPixel(cx - x, cy - y, color);
	drawPixel(cx - y, cy - x, color);
	drawPixel(cx - x, cy + y, color);
	drawPixel(cx - y, cy + x, color);
}

void PrimitiveRenderer::drawEllipsePoints(int cx, int cy, int x, int y, sf::Color color) {
	drawPixel(cx + x, cy + y, color);
	drawPixel(cx - x, cy + y, color);
	drawPixel(cx + x, cy - y, color);
	drawPixel(cx - x, cy - y, color);
}

void PrimitiveRenderer::drawPolygon(const std::vector<Point2D>& points, sf::Color color) {
	if (isPolygonValid(points)) {
		for (size_t i = 0; i < points.size() - 1; ++i) {
			const Point2D& startPoint = points[i];
			const Point2D& endPoint = points[i + 1];
			drawLine(startPoint.getX(), startPoint.getY(), endPoint.getX(), endPoint.getY(), 2.f, color);
		}
		// Connect the last point to the first point to close the polygon
		const Point2D& firstPoint = points.front();
		const Point2D& lastPoint = points.back();
		drawLine(lastPoint.getX(), lastPoint.getY(), firstPoint.getX(), firstPoint.getY(), 2.f, color);
	}
}

void PrimitiveRenderer::drawPolygon(const std::vector<LineSegment>& segments, sf::Color color) {
	// Check for intersections between line segments
	for (size_t i = 0; i < segments.size() - 1; ++i) {
		for (size_t j = i + 1; j < segments.size(); ++j) {
			if (doSegmentsIntersect(segments[i], segments[j])) {
				// If segments intersect, stop drawing
				return;
			}
		}
	}

	// If no intersections found, draw the polygon
	for (const auto& segment : segments) {
		const Point2D& startPoint = segment.getStartPoint();
		const Point2D& endPoint = segment.getEndPoint();
		drawLine(startPoint.getX(), startPoint.getY(), endPoint.getX(), endPoint.getY(), 2.f, color);
	}
	// Connect the last segment to the first segment to close the polygon
	if (!segments.empty()) {
		const Point2D& firstPoint = segments.front().getStartPoint();
		const Point2D& lastPoint = segments.back().getEndPoint();
		drawLine(lastPoint.getX(), lastPoint.getY(), firstPoint.getX(), firstPoint.getY(), 2.f, color);
	}
}

bool PrimitiveRenderer::isPolygonValid(const std::vector<Point2D>& points) {
	// A polygon must have at least three points
	if (points.size() < 3) {
		return false;
	}

	// Check for self-intersection (overlapping edges)
	for (size_t i = 0; i < points.size() - 1; ++i) {
		LineSegment currentSegment(points[i], points[i + 1]);
		for (size_t j = i + 2; j < points.size() - 1; ++j) {
			LineSegment otherSegment(points[j], points[j + 1]);
			if (doSegmentsIntersect(currentSegment, otherSegment)) {
				return false; // Self-intersection found
			}
		}
	}

	return true;
}

bool PrimitiveRenderer::doSegmentsIntersect(const LineSegment& segment1, const LineSegment& segment2) {
	const Point2D& A = segment1.getStartPoint();
	const Point2D& B = segment1.getEndPoint();
	const Point2D& C = segment2.getStartPoint();
	const Point2D& D = segment2.getEndPoint();

	// Compute orientations of the four points
	int orientation1 = orientation(A, B, C);
	int orientation2 = orientation(A, B, D);
	int orientation3 = orientation(C, D, A);
	int orientation4 = orientation(C, D, B);

	// General case: segments intersect if orientations are different
	if (orientation1 != orientation2 && orientation3 != orientation4) {
		return true;
	}

	// Special cases:

	// Segments AB and CD are collinear and overlap
	if (orientation1 == 0 && onSegment(A, C, B)) return true;
	if (orientation2 == 0 && onSegment(A, D, B)) return true;
	if (orientation3 == 0 && onSegment(C, A, D)) return true;
	if (orientation4 == 0 && onSegment(C, B, D)) return true;

	return false; // No intersection
}

void PrimitiveRenderer::drawFilledPolygon(const std::vector<Point2D>& points, sf::Color fillColor) {
	if (!isPolygonValid(points)) {
		// If the polygon is not valid, do not draw it
		return;
	}

	// Draw the filled polygon
	sf::ConvexShape convex;
	convex.setPointCount(points.size());
	for (size_t i = 0; i < points.size(); ++i) {
		convex.setPoint(i, sf::Vector2f(points[i].getX(), points[i].getY()));
	}
	convex.setFillColor(fillColor);
	window.draw(convex);
}
// Helper method to calculate orientation of triplet (p, q, r)
// 0: Collinear points, 1: Clockwise, 2: Counterclockwise
int PrimitiveRenderer::orientation(const Point2D& p, const Point2D& q, const Point2D& r) {
	float val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
		(q.getX() - p.getX()) * (r.getY() - q.getY());

	if (val == 0) return 0;  // Collinear
	return (val > 0) ? 1 : 2; // Clockwise or counterclockwise
}

// Helper method to check if point q lies on the line segment 'pr'
bool PrimitiveRenderer::onSegment(const Point2D& p, const Point2D& q, const Point2D& r) {
	return (q.getX() <= std::max(p.getX(), r.getX()) && q.getX() >= std::min(p.getX(), r.getX()) &&
		q.getY() <= std::max(p.getY(), r.getY()) && q.getY() >= std::min(p.getY(), r.getY()));
}








void PrimitiveRenderer::consistencyFill(int x, int y, sf::Color fillColor, sf::Color targetColor) {
	std::stack<std::pair<int, int>> stack;
	stack.push(std::make_pair(x, y));

	while (!stack.empty()) {
		std::pair<int, int> current = stack.top();
		stack.pop();

		int currentX = current.first;
		int currentY = current.second;

		if (!isInsideWindow(currentX, currentY) || getPixelColor(currentX, currentY) != targetColor) {
			continue;
		}

		// Fill the current pixel
		drawPixel(currentX, currentY, fillColor);

		// Push adjacent pixels to the stack
		stack.push(std::make_pair(currentX + 1, currentY));
		stack.push(std::make_pair(currentX - 1, currentY));
		stack.push(std::make_pair(currentX, currentY + 1));
		stack.push(std::make_pair(currentX, currentY - 1));
	}
}

void PrimitiveRenderer::parityCheckFill(const std::vector<Point2D>& points, sf::Color fillColor) {
	// Check if the polygon has enough points
	if (points.size() < 3) {
		return;
	}

	// Sort the points based on their y-coordinates
	std::vector<Point2D> sortedPoints = points;
	std::sort(sortedPoints.begin(), sortedPoints.end(), [](const Point2D& a, const Point2D& b) {
		return a.getY() < b.getY();
		});

	// Iterate through each horizontal line
	for (int y = static_cast<int>(sortedPoints[0].getY()); y <= static_cast<int>(sortedPoints.back().getY()); ++y) {
		std::vector<float> intersections;

		// Calculate intersections with each polygon edge
		for (size_t i = 0; i < sortedPoints.size() - 1; ++i) {
			const Point2D& startPoint = sortedPoints[i];
			const Point2D& endPoint = sortedPoints[i + 1];

			// Check if the current horizontal line intersects the edge
			if ((startPoint.getY() <= y && endPoint.getY() > y) || (endPoint.getY() <= y && startPoint.getY() > y)) {
				float xIntersection = startPoint.getX() + (static_cast<float>(y) - startPoint.getY()) / (endPoint.getY() - startPoint.getY()) * (endPoint.getX() - startPoint.getX());
				intersections.push_back(xIntersection);
			}
		}

		// Sort the intersections in ascending order
		std::sort(intersections.begin(), intersections.end());

		// Fill the horizontal sections between pairs of intersections
		for (size_t i = 0; i < intersections.size(); i += 2) {
			int startX = static_cast<int>(intersections[i]);
			int endX = static_cast<int>(intersections[i + 1]);

			// Draw a horizontal line between startX and endX at y-coordinate
			fillHorizontalSection(startX, endX, y, fillColor);
		}
	}
}

bool PrimitiveRenderer::isInsideWindow(int x, int y) {
	return x >= 0 && x < renderTexture.getSize().x && y >= 0 && y < renderTexture.getSize().y;
}

sf::Color PrimitiveRenderer::getPixelColor(int x, int y) {
	sf::Image image = renderTexture.getTexture().copyToImage();
	return image.getPixel(x, y);
}

void PrimitiveRenderer::fillHorizontalSection(int startX, int endX, int y, sf::Color fillColor) {
	for (int x = startX; x <= endX; ++x) {
		drawPixel(x, y, fillColor);
	}
}

void PrimitiveRenderer::borderFill(int x, int y, sf::Color fillColor, sf::Color borderColor) {
	if (!isInsideWindow(x, y) || getPixelColor(x, y) == borderColor) {
		return;
	}

	consistencyFill(x, y, fillColor, borderColor);
}

void PrimitiveRenderer::floodFill(int x, int y, sf::Color fillColor, sf::Color targetColor) {
	if (!isInsideWindow(x, y) || getPixelColor(x, y) == fillColor || getPixelColor(x, y) == targetColor) {
		return;
	}

	std::stack<std::pair<int, int>> stack;
	stack.push(std::make_pair(x, y));

	while (!stack.empty()) {
		std::pair<int, int> current = stack.top();
		stack.pop();

		int currentX = current.first;
		int currentY = current.second;

		if (!isInsideWindow(currentX, currentY) || getPixelColor(currentX, currentY) != targetColor) {
			continue;
		}

		// Fill the current pixel
		drawPixel(currentX, currentY, fillColor);

		// Push adjacent pixels to the stack
		stack.push(std::make_pair(currentX + 1, currentY));
		stack.push(std::make_pair(currentX - 1, currentY));
		stack.push(std::make_pair(currentX, currentY + 1));
		stack.push(std::make_pair(currentX, currentY - 1));
	}
}