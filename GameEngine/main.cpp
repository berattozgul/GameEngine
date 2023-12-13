#include <SFML/Graphics.hpp>
#include <iostream>

class GameObject {
public:
    virtual ~GameObject() {}
    virtual void update() = 0; // Pure virtual method
};

class UpdatableObject : public virtual GameObject {
public:
    virtual void update() = 0; // Pure virtual method
};

class DrawableObject : public virtual GameObject {
public:
    virtual void draw(sf::RenderWindow& window) = 0; // Pure virtual method
};

class TransformableObject : public virtual GameObject {
public:
    virtual void translate(float x, float y) = 0; // Pure virtual method
    virtual void rotate() = 0; // Pure virtual method
    virtual void scale() = 0; // Pure virtual method
};

class ShapeObject : public DrawableObject, public TransformableObject {
public:
    virtual void draw(sf::RenderWindow& window) = 0; // Pure virtual method
    virtual void translate(float x, float y) = 0; // Pure virtual method
    virtual void rotate() = 0; // Pure virtual method
    virtual void scale() = 0; // Pure virtual method
};

class Point2D : public ShapeObject{
private:
    float x, y;

public:
    Point2D(float x, float y) : x(x), y(y) {}

    // Getter methods for x and y

    virtual void translate(float dx, float dy) override {
        x += dx;
        y += dy;
    }

    virtual void rotate() override {
        // Rotation logic for a point (not implemented for a single point)
    }
    virtual void update() override {

    }
    virtual void scale() override {
        // Scaling logic for a point (not implemented for a single point)
    }

    virtual void draw(sf::RenderWindow& window) override {
        // Draw logic for a point
    }
};

class LineSegment : public ShapeObject{
private:
    Point2D start, end;

public:
    LineSegment(float startX, float startY, float endX, float endY)
        : start(startX, startY), end(endX, endY) {}

    // Getter methods for start and end points

    virtual void translate(float dx, float dy) override {
        start.translate(dx, dy);
        end.translate(dx, dy);
    }

    virtual void rotate() override {
        // Rotation logic for a line segment (not implemented for a line segment)
    }

    virtual void scale() override {
        // Scaling logic for a line segment (not implemented for a line segment)
    }

    virtual void draw(sf::RenderWindow& window) override {
        // Draw logic for a line segment
    }
};


// Implement classes for specific shapes inheriting from ShapeObject
class Circle : public ShapeObject {
private:
    sf::CircleShape shape;
    float x, y;
    float speed;

public:
    Circle(float radius, float x, float y, float speed) : x(x), y(y), speed(speed) {
        shape.setRadius(radius);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Green);
    }

    virtual void draw(sf::RenderWindow& window) override {
        window.draw(shape);
    }

    virtual void translate(float dx, float dy) override {
        x += dx;
        y += dy;
        shape.setPosition(x, y);
    }

    virtual void update() override {
        // Move the circle within boundaries
        if (x < 0 || x + shape.getRadius() * 2 > 800) {
            speed = -speed; // Reverse direction
        }
        translate(speed, 0);
    }

    virtual void rotate() override {
        // Not implemented for a circle
    }

    virtual void scale() override {
        // Not implemented for a circle
    }
};
class Rectangle : public ShapeObject {
private:
    sf::RectangleShape shape;
    float x, y;
    float speed;
    float rotationSpeed;

public:
    Rectangle(float width, float height, float x, float y, float speed, float rotationSpeed)
        : x(x), y(y), speed(speed), rotationSpeed(rotationSpeed) {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Red);
    }

    virtual void draw(sf::RenderWindow& window) override {
        window.draw(shape);
    }

    virtual void translate(float dx, float dy) override {
        x += dx;
        y += dy;
        shape.setPosition(x, y);
    }

    virtual void update() override {
        // Move the rectangle within boundaries
        if (x < 0 || x + shape.getSize().x > 800) {
            speed = -speed; // Reverse direction
        }
        translate(speed, 0);
    }

    virtual void rotate() override {
        shape.rotate(rotationSpeed);
    }

    virtual void scale() override {
        // Not implemented for a rectangle
    }
};
class Player : public UpdatableObject, public DrawableObject {
private:
    sf::RectangleShape shape;
    float x, y;
    float speed;

public:
    Player(float x, float y, float speed) : x(x), y(y), speed(speed) {
        shape.setSize(sf::Vector2f(100, 100));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Blue);
    }

    virtual void draw(sf::RenderWindow& window) override {
        window.draw(shape);
    }

    virtual void update() override {
        // Move the player with keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            x -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            x += speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            y -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            y += speed;
        }
        shape.setPosition(x, y);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game");

    Circle circle(50, 100, 300, 0.5f);
    Player player(300, 400, 1);
    Rectangle rotatingRectangle(80, 40, 200, 200, 1.0f, 1.5f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        circle.update();
        circle.draw(window);

        player.update();
        player.draw(window);

        rotatingRectangle.update();
        rotatingRectangle.rotate();  // Rotate the rectangle
        rotatingRectangle.draw(window);

        window.display();
    }

    return 0;
}
