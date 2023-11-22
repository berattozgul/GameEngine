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

public:
    PrimitiveRenderer(sf::RenderWindow& _window);

    void drawRectangle(float x, float y, float width, float height, sf::Color color);
    void drawCircle(float x, float y, float radius, sf::Color color);
    void drawLine(float x1, float y1, float x2, float y2, float thickness, sf::Color color);
    void drawPoint(float x, float y, sf::Color color);
    void drawLineIncremental(int x1, int y1, int x2, int y2, sf::Color color);
    void drawPolyline(const std::vector<Point2D>& points, sf::Color color, bool isClosed);
    void drawPolyline(const std::vector<LineSegment>& segments, sf::Color color, bool isClosed);


private:
    float getDistance(float x1, float y1, float x2, float y2);
    float getAngle(float x1, float y1, float x2, float y2);
    void drawPixel(int x, int y, sf::Color color);

};
