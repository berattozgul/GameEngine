//Point2D.cpp
#include "Point2D.h"
#include "PrimitiveRenderer.h"
#include <cmath>

Point2D::Point2D(float _x, float _y) : x(_x), y(_y) {}

float Point2D::getX() const {
    return x;
}
float Point2D::getY() const {
    return y;
}

// Setters for x and y coordinates
void Point2D::setX(float _x) {
    x = _x;
}

void Point2D::setY(float _y) {
    y = _y;
}

// Method to draw the point using the provided PrimitiveRenderer
void Point2D::draw(PrimitiveRenderer& renderer, sf::Color color) {
    renderer.drawPoint(x, y, color);
}