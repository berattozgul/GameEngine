/**
 * @file main.cpp
 * @brief A simple game implemented in C++ using SFML.
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

 // =====================================
 //             GameObject Hierarchy
 // =====================================

 /**
  * @brief The base class for all game objects.
  */
class GameObject {
public:
    virtual ~GameObject() {}
    /**
    * @brief Pure virtual method to update the game object.
    */
    virtual void update() = 0;
};
/**
 * @brief Virtual base class for objects that can be updated.
 */
class UpdatableObject : public virtual GameObject {
public:
    /**
     * @brief Pure virtual method to update the object.
     */
    virtual void update() = 0; // Pure virtual method
};
/**
 * @brief Virtual base class for objects that can be drawn on the screen.
 */
class DrawableObject : public virtual GameObject {
public:
    /**
     * @brief Pure virtual method to draw the object on the screen.
     * @param window The SFML render window.
     */
    virtual void draw(sf::RenderWindow& window) = 0; // Pure virtual method
};
/**
 * @brief Virtual base class for objects that can be transformed.
 */
class TransformableObject : public virtual GameObject {
public:
    /**
     * @brief Pure virtual method to translate the object's position.
     * @param x The translation in the x-axis.
     * @param y The translation in the y-axis.
     */
    virtual void translate(float x, float y) = 0;
    /**
     * @brief Pure virtual method to rotate the object.
     */
    virtual void rotate() = 0;
    /**
     * @brief Pure virtual method to scale the object.
     */
    virtual void scale() = 0;
};
/**
 * @brief Virtual base class for objects with a specific shape.
 */
class ShapeObject : public DrawableObject, public TransformableObject {
public:
    /**
     * @brief Pure virtual method to draw the object on the screen.
     * @param window The SFML render window.
     */
    virtual void draw(sf::RenderWindow& window) = 0;
    /**
     * @brief Pure virtual method to translate the object's position.
     * @param x The translation in the x-axis.
     * @param y The translation in the y-axis.
     */
    virtual void translate(float x, float y) = 0;
    /**
     * @brief Pure virtual method to rotate the object.
     */
    virtual void rotate() = 0; 
    /**
     * @brief Pure virtual method to scale the object.
     */
    virtual void scale() = 0; 
};
// =====================================
//           Concrete Shape Classes
// =====================================

/**
 * @brief Represents a point in 2D space.
 */
class Point2D : public ShapeObject {
private:
    float x, y;

public:
    /**
     * @brief Constructor for Point2D.
     * @param x The x-coordinate of the point.
     * @param y The y-coordinate of the point.
     */
    Point2D(float x, float y) : x(x), y(y) {}
    /**
     * @brief Translates the point by a given amount.
     * @param dx The translation in the x-axis.
     * @param dy The translation in the y-axis.
     */
    virtual void translate(float dx, float dy) override {
        x += dx;
        y += dy;
    }
    /**
     * @brief Not implemented for a single point.
     */
    virtual void rotate() override {
        // Rotation logic for a point (not implemented for a single point)
    }
    /**
     * @brief Not implemented for a single point.
     */
    virtual void update() override {

    }
    /**
     * @brief Not implemented for a single point.
     */
    virtual void scale() override {
        // Scaling logic for a point (not implemented for a single point)
    }

    /**
     * @brief Represents a line segment in 2D space.
     */
    virtual void draw(sf::RenderWindow& window) override {
        // Draw logic for a point
    }
};

class LineSegment : public ShapeObject {
private:
    Point2D start, end;

public:
    /**
     * @brief Constructor for LineSegment.
     * @param startX The x-coordinate of the starting point.
     * @param startY The y-coordinate of the starting point.
     * @param endX The x-coordinate of the ending point.
     * @param endY The y-coordinate of the ending point.
     */
    LineSegment(float startX, float startY, float endX, float endY)
        : start(startX, startY), end(endX, endY) {}

    /**
     * @brief Translates the line segment by a given amount.
     * @param dx The translation in the x-axis.
     * @param dy The translation in the y-axis.
     */
    virtual void translate(float dx, float dy) override {
        start.translate(dx, dy);
        end.translate(dx, dy);
    }
    /**
     * @brief Not implemented for a line segment.
     */
    virtual void rotate() override {
        // Rotation logic for a line segment (not implemented for a line segment)
    }
    /**
     * @brief Not implemented for a line segment.
     */

    virtual void scale() override {
        // Scaling logic for a line segment (not implemented for a line segment)
    }
    /**
     * @brief Draws the line segment on the screen.
     * @param window The SFML render window.
     */
    virtual void draw(sf::RenderWindow& window) override {
        // Draw logic for a line segment
    }
};
// ... (Other shape classes, Circle, Rectangle, etc.)

// =====================================
//          Additional Object Classes
// =====================================

/**
 * @brief Represents an animated object in the game.
 */
class AnimatedObject : public virtual GameObject {
public:
    /**
     * @brief Pure virtual method to perform animation.
     */
    virtual void animate() = 0; // Pure virtual method
};
/**
 * @brief Represents a bitmap object that can be drawn and transformed.
 */
class BitmapObject : public virtual DrawableObject, public virtual TransformableObject {
public:
    /**
     * @brief Pure virtual method to draw the object on the screen.
     * @param window The SFML render window.
     */
    virtual void draw(sf::RenderWindow& window) override = 0; // Pure virtual method

    // Additional methods for bitmap manipulation can be added here
};
/**
 * @brief Represents a sprite object that can be animated.
 */
class SpriteObject : public BitmapObject, public AnimatedObject {
public:
    /**
     * @brief Pure virtual method to perform animation.
     */
    virtual void animate() override = 0; // Pure virtual method

    // Additional methods for sprite animation can be added here
};
/**
 * @brief Represents the ground object in the game.
 */
class GroundObject : public DrawableObject {
private:
    sf::RectangleShape ground;

public:
    /**
     * @brief Constructor for GroundObject.
     * @param width The width of the ground.
     * @param height The height of the ground.
     */
    GroundObject(float width, float height) {
        ground.setSize(sf::Vector2f(width, height));
        ground.setPosition(0, 600 - height); // Adjust the position as needed
        ground.setFillColor(sf::Color::Color(105, 151, 61));
    }
    /**
     * @brief Draws the ground on the screen.
     * @param window The SFML render window.
     */
    virtual void draw(sf::RenderWindow& window) override {
        window.draw(ground);
    }
    /**
     * @brief Updates the ground object.
     */
    virtual void update() override {
        // Add any update logic specific to the ground if needed
    }
};


// =====================================
//           Game-Specific Classes
// =====================================

/**
 * @brief Represents a circle in the game with movement logic.
 */
class Circle : public ShapeObject {
private:
    sf::CircleShape shape;
    float speed;
    sf::Clock clock;

public:
    /**
     * @brief Constructor for Circle.
     * @param radius The radius of the circle.
     * @param x The x-coordinate of the circle's position.
     * @param y The y-coordinate of the circle's position.
     * @param speed The speed of the circle's movement.
     */

    Circle(float radius, float x, float y, float speed) : speed(speed) {
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Black);
        shape.setPosition(x, y);
    }
    /**
     * @brief Getter method for the x-coordinate of the circle's position.
     * @return The x-coordinate of the circle's position.
     */
    float getX() const {
        return shape.getPosition().x;
    }
    /**
     * @brief Getter method for the radius of the circle.
     * @return The radius of the circle.
     */
    float getRadius() const {
        return shape.getRadius();
    }
    /**
     * @brief Resets the circle's position to the specified coordinates.
     * @param x The x-coordinate to reset to.
     * @param y The y-coordinate to reset to.
     */
    void reset(float x, float y) {
        shape.setPosition(x, y);
        clock.restart(); // Yeniden baþlatýldýðýnda süreyi sýfýrla
    }

    /**
     * @brief Draws the circle on the screen.
     * @param window The SFML render window.
     */
    virtual void draw(sf::RenderWindow& window) override {
        window.draw(shape);
    }

    /**
     * @brief Translates the circle by a given amount.
     * @param dx The translation in the x-axis.
     * @param dy The translation in the y-axis.
     */
    virtual void translate(float dx, float dy) override {
        shape.move(dx, dy);
    }
    /**
     * @brief Not implemented for a circle.
     */
    virtual void rotate() override {
        // Not implemented for a circle
    }
    /**
     * @brief Not implemented for a circle.
     */
    virtual void scale() override {
        // Not implemented for a circle
    }
    /**
     * @brief Updates the circle's position and checks for reset condition.
     */
    virtual void update() override {
        // Move the circle towards left
        translate(-speed, 0);

        // If the circle goes off the left side, reset its position
        if (shape.getPosition().x + getRadius() * 2 < 0 && clock.getElapsedTime().asSeconds() > 3.0f) {
            float randomY = static_cast<float>(std::rand() % 301 + 100); // Random y between 100 and 400
            reset(800, randomY);
        }
    }
    /**
     * @brief Sets a new speed for the circle.
     * @param newSpeed The new speed of the circle.
     */
    void setSpeed(float newSpeed) {
        speed = newSpeed;
    }
    /**
     * @brief Gets the underlying SFML CircleShape object.
     * @return A reference to the SFML CircleShape object.
     */
    sf::CircleShape& getShape() {
        return shape;
    }
};

/**
 * @brief Represents a rectangle in the game with movement and rotation logic.
 */
class Rectangle : public ShapeObject {
private:
    sf::RectangleShape shape;
    float x, y;
    float speed;
    float rotationSpeed;

public:
    /**
     * @brief Constructor for Rectangle.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     * @param x The x-coordinate of the rectangle's position.
     * @param y The y-coordinate of the rectangle's position.
     * @param speed The speed of the rectangle's movement.
     * @param rotationSpeed The speed of the rectangle's rotation.
     */
    Rectangle(float width, float height, float x, float y, float speed, float rotationSpeed)
        : x(x), y(y), speed(speed), rotationSpeed(rotationSpeed) {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Red);
    }
    /**
     * @brief Draws the rectangle on the screen.
     * @param window The SFML render window.
     */
    virtual void draw(sf::RenderWindow& window) override {
        window.draw(shape);
    }
    /**
     * @brief Translates the rectangle by a given amount.
     * @param dx The translation in the x-axis.
     * @param dy The translation in the y-axis.
     */
    virtual void translate(float dx, float dy) override {
        x += dx;
        y += dy;
        shape.setPosition(x, y);
    }
    /**
     * @brief Updates the rectangle's position within boundaries.
     */
    virtual void update() override {
        // Move the rectangle within boundaries
        if (x < 0 || x + shape.getSize().x > 800) {
            speed = -speed; // Reverse direction
        }
        translate(speed, 0);
    }
    /**
     * @brief Rotates the rectangle.
     */
    virtual void rotate() override {
        shape.rotate(rotationSpeed);
    }
    /**
     * @brief Not implemented for a rectangle.
     */
    virtual void scale() override {
        // Not implemented for a rectangle
    }
};
/**
 * @brief Represents the player character in the game.
 */
class Player : public UpdatableObject, public DrawableObject {
private:
    sf::Sprite sprite;
    sf::Texture textureIdle;
    sf::Texture textureWalking1;
    sf::Texture textureWalking2;
    sf::Texture textureJumping; // Texture for the jump animation
    float x, y;
    float speed;
    int currentFrame;
    int frameCount;
    float frameDuration;
    float elapsedTime;
    bool isJumping;
    float jumpSpeed;
    float initialJumpHeight;
    float maxJumpHeight;
    float jumpHeight;
    bool isOnGround;

public:
    /**
     * @brief Constructor for Player.
     * @param x The x-coordinate of the player's position.
     * @param y The y-coordinate of the player's position.
     * @param speed The speed of the player's movement.
     */
    Player(float x, float y, float speed)
        : x(x), y(y), speed(speed), currentFrame(0), frameCount(4),
        frameDuration(0.2f), elapsedTime(0.0f), isJumping(false),
        jumpSpeed(0.5f), initialJumpHeight(80), maxJumpHeight(200),
        jumpHeight(0.0f), isOnGround(true) {

        if (!textureIdle.loadFromFile("Cowboy4_walk without gun_0.png") ||
            !textureWalking1.loadFromFile("Cowboy4_walk without gun_2.png") ||
            !textureWalking2.loadFromFile("Cowboy4_walk without gun_2.png") ||
            !textureJumping.loadFromFile("Cowboy4_jump without gun_0.png")) {
            std::cerr << "Failed to load player sprites!" << std::endl;
            // Handle failure
        }
        else {
            sprite.setTexture(textureIdle);
            sprite.setPosition(x, y);
            sprite.setScale(2.5f, 2.5f); // Adjust scale as needed
        }
    }
    /**
     * @brief Draws the player on the screen.
     * @param window The SFML render window.
     */
    virtual void draw(sf::RenderWindow& window) override {
        window.draw(sprite);
    }
    /**
     * @brief Updates the player's position based on keyboard input.
     */
    virtual void update() override {
        // Update player's position based on keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            x -= speed;
            updateAnimation();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            x += speed;
            updateAnimation();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping && isOnGround) {
            isJumping = true;
            isOnGround = false;
            jumpHeight = 0.0f;
            sprite.setTexture(textureJumping); // Set jump texture when jumping
        }

        // Jumping logic with maximum height check
        if (isJumping) {
            if (jumpHeight < maxJumpHeight) {
                y -= jumpSpeed;
                jumpHeight += jumpSpeed;
            }
            else {
                isJumping = false;
                jumpHeight = 0.0f;
                sprite.setTexture(textureIdle); // Set back to idle texture when jump is complete
            }
        }
        else {
            // Apply gravity when not jumping
            if (y < 270) {
                y += jumpSpeed; // Adjust gravity as needed
            }
            else {
                y = 270;
                isOnGround = true;
            }
        }

        // Ensure the player stays within the bounds of the window
        if (x < 0) {
            x = 0;
        }
        if (x + sprite.getGlobalBounds().width > 800) {
            x = 800 - sprite.getGlobalBounds().width;
        }

        elapsedTime += frameDuration;
        if (elapsedTime >= frameDuration) {
            currentFrame = (currentFrame + 1) % frameCount;
            elapsedTime = 0.0f;
        }

        sprite.setPosition(x, y);
    }
    sf::Sprite& getSprite() {
        return sprite;
    }
private:
    /**
     * @brief Helper function to update walking or jumping animation.
     */
    void updateAnimation() {
        // Switch between walking frames
        if (currentFrame % 2 == 0 && !isJumping) {
            sprite.setTexture(textureWalking1);
        }
        else if (!isJumping) {
            sprite.setTexture(textureWalking2);
        }
    }
};
/**
 * @brief Handles collisions between game objects.
 */
class CollisionHandler {
public:
    /**
     * @brief Checks if two rectangles intersect.
     * @param rect1 The first rectangle.
     * @param rect2 The second rectangle.
     * @return True if the rectangles intersect, false otherwise.
     */
    static bool checkCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
        return rect1.intersects(rect2);
    }
    /**
     * @brief Handles a collision event between two game objects.
     * @param window The SFML render window.
     * @param obj1 The first game object involved in the collision.
     * @param obj2 The second game object involved in the collision.
     */
    static void handleCollision(sf::RenderWindow& window, GameObject& obj1, GameObject& obj2) {
        window.clear();
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            // Handle font loading error
        }

        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("Game Over");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(200, 300);

        window.draw(gameOverText);
        window.display();

        // Wait for a moment to show the "Game Over" message
        sf::sleep(sf::seconds(2));

        // Close the window
        window.close();
    }
};

/**
 * @brief The main function that initializes the game and runs the game loop.
 * @return The exit status of the program.
 */
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game");
    sf::Color backgroundColor(0, 192, 255);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("asd.jpg")) {
        std::cerr << "Failed to load background image!" << std::endl;
        return EXIT_FAILURE;
    }
    sf::Sprite backgroundSprite1(backgroundTexture);
    sf::Sprite backgroundSprite2(backgroundTexture);

    backgroundSprite1.setPosition(0, 0);
    backgroundSprite2.setPosition(backgroundSprite1.getGlobalBounds().width, 0);

    Player player(0, 270, 1);
    GroundObject ground(1000, 200);

    const int circleCount = 1;
    std::vector<Circle> circles;

    for (int i = 0; i < circleCount; ++i) {
        float randomY = static_cast<float>(std::rand() % 301 + 100);
        circles.emplace_back(20, 800, randomY, 0.9f);
    }

    sf::Clock speedUpClock, clock;
    const float initialCircleSpeed = 0.8f;
    float currentCircleSpeed = initialCircleSpeed;
    const float speedUpInterval = 20.0f; // seconds

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {  // Adjust the font file path as needed
        std::cerr << "Failed to load font!" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(20);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(700, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        backgroundSprite1.move(-0.5f, 0);
        backgroundSprite2.move(-0.5f, 0);

        if (backgroundSprite1.getPosition().x + backgroundSprite1.getGlobalBounds().width <= 0) {
            backgroundSprite1.setPosition(backgroundSprite2.getPosition().x + backgroundSprite2.getGlobalBounds().width, 0);
        }

        if (backgroundSprite2.getPosition().x + backgroundSprite2.getGlobalBounds().width <= 0) {
            backgroundSprite2.setPosition(backgroundSprite1.getPosition().x + backgroundSprite1.getGlobalBounds().width, 0);
        }

        window.clear();

        window.draw(backgroundSprite1);
        window.draw(backgroundSprite2);

        ground.update();
        ground.draw(window);

        // Check if 15 seconds have passed to speed up the circles
        if (speedUpClock.getElapsedTime().asSeconds() >= speedUpInterval) {
            // Speed up the circles
            currentCircleSpeed += 0.1f; // You can adjust the speed increment as needed
            speedUpClock.restart(); // Restart the clock
        }

        for (auto& circle : circles) {
            circle.setSpeed(currentCircleSpeed);
            circle.update();
            circle.draw(window);
            // Check for collision between player and circle
            sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();
            sf::FloatRect circleBounds = circle.getShape().getGlobalBounds();

            // Scale the playerBounds for collision detection (make it smaller)
            float collisionScale = 0.3f; // Adjust the scale factor as needed
            playerBounds.width *= collisionScale;
            playerBounds.height *= collisionScale;
            // Use the scaled playerBounds for the intersection check
            if (playerBounds.intersects(circleBounds)) {
                CollisionHandler::handleCollision(window, player, circle);
            }
            if (circle.getX() < -circle.getRadius()) {
                float randomY = static_cast<float>(std::rand() % 301 + 100);
                circle.reset(800, randomY);
            }
        }

        player.update();
        player.draw(window);

        // Display the elapsed time in the top-right corner
        timerText.setString("Time:" + std::to_string(clock.getElapsedTime().asSeconds()));
        window.draw(timerText);

        window.display();
    }

    return 0;
}
