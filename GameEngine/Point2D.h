
#pragma once

#include <SFML/Graphics.hpp> 

class PrimitiveRenderer;

class Point2D {
private:
    float x;
    float y;

public:
    Point2D(float _x, float _y);

    float getX() const;
    float getY() const;
    void setX(float _x);
    void setY(float _y);
    void draw(PrimitiveRenderer& renderer, sf::Color color);
};