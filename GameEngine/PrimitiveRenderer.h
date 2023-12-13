//PrimitiveRenderer.h
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Point2D.h"
#include "LineSegment.h"


class LineSegment;

class PrimitiveRenderer {
private:
    sf::RenderWindow& window;

    sf::RenderTexture renderTexture;

public:
    PrimitiveRenderer(sf::RenderWindow& _window);
    void drawRectangle(float x, float y, float width, float height, sf::Color color);
    void drawCircle(float x, float y, float radius, sf::Color color);
    void drawLine(float x1, float y1, float x2, float y2, float thickness, sf::Color color);
    void drawPoint(float x, float y, sf::Color color);
    void drawLineIncremental(int x1, int y1, int x2, int y2, sf::Color color);
    void drawEllipse(float centerX, float centerY, float rx, float ry, sf::Color color);
    void drawCircleSymmetrical(float centerX, float centerY, float radius, sf::Color color);
    void drawPolyline(const std::vector<Point2D>& points, sf::Color color, bool isClosed);
    void drawPolyline(const std::vector<LineSegment>& segments, sf::Color color, bool isClosed);
    void drawPolygon(const std::vector<Point2D>& points, sf::Color color);
    void drawPolygon(const std::vector<LineSegment>& segments, sf::Color color);
    void drawFilledPolygon(const std::vector<Point2D>& points, sf::Color fillColor);
    // New methods for filling an area with color



    void consistencyFill(int x, int y, sf::Color fillColor, sf::Color targetColor);
    void parityCheckFill(const std::vector<Point2D>& points, sf::Color fillColor);


    void borderFill(int x, int y, sf::Color fillColor, sf::Color borderColor);
    void floodFill(int x, int y, sf::Color fillColor, sf::Color targetColor);


private:

    float getDistance(float x1, float y1, float x2, float y2);
    float getAngle(float x1, float y1, float x2, float y2);
    void drawPixel(int x, int y, sf::Color color);
    void drawEllipsePoints(int cx, int cy, int x, int y, sf::Color color);
    void drawCirclePointsSymmetrical(int cx, int cy, int x, int y, sf::Color color);
    bool isPolygonValid(const std::vector<Point2D>& points);
    bool doSegmentsIntersect(const LineSegment& segment1, const LineSegment& segment2);
    int orientation(const Point2D& p, const Point2D& q, const Point2D& r);
    bool onSegment(const Point2D& p, const Point2D& q, const Point2D& r);



    // Helper function to check if a point is inside the window boundaries
    bool isInsideWindow(int x, int y);

    // Helper function to get the color of a pixel from the render texture
    sf::Color getPixelColor(int x, int y);

    // Helper function to fill a horizontal section of pixels
    void fillHorizontalSection(int startX, int endX, int y, sf::Color fillColor);

};
