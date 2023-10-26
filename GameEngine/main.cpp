#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

class Engine {
private:
    sf::RenderWindow window; // The main window for the application
    sf::Color clearColor; // The background color of the window
    sf::Font font; // Font for text rendering
    sf::Text text; // Text object for displaying input text and time
    std::string inputText; // String to store the user input text
    sf::Clock clock; // Clock object to measure elapsed time
    sf::RectangleShape button; // Button for clearing the input text
    bool isRunning; // Flag to control the game loop
    std::ofstream logfile; // File stream for logging errors
    int framesPerSecond; // Number of animation frames per second
    bool isMouseEnabled; // Flag to enable mouse support
    bool isKeyboardEnabled; // Flag to enable keyboard support


public:
    // Constructor to initialize the window and other variables
    Engine(int width, int height, std::string title) : window(sf::VideoMode(width, height), title), isRunning(false), logfile("log.txt"),
        framesPerSecond(60), isMouseEnabled(true), isKeyboardEnabled(true) {
        // Check if the log file is opened successfully
        if (!logfile.is_open()) {
            std::cerr << "Failed to open log file." << std::endl;
        }
        // Default values
        clearColor = sf::Color::Black;
        // Load font from file
        if (!font.loadFromFile("arial.ttf")) {
            logError("Error loading font");
        }
        // Set up text properties
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        inputText = "";
        // Button initialization
        button.setSize(sf::Vector2f(100.f, 50.f));
        button.setFillColor(sf::Color::Red);
        button.setPosition(200.f, 200.f);
    }

    // Initialize the game engine
    void initialize() {
        isRunning = true;
        clock.restart();
    }

    // Set the background color of the window
    void setClearColor(sf::Color color) {
        clearColor = color;
    }
    // Set the frames per second for the animation
    void setFramesPerSecond(int fps) {
        framesPerSecond = fps;
    }

    // Enable or disable mouse support
    void setMouseEnabled(bool enabled) {
        isMouseEnabled = enabled;
    }

    // Enable or disable keyboard support
    void setKeyboardEnabled(bool enabled) {
        isKeyboardEnabled = enabled;
    }

    // Clear the screen to the specified color
    void clearScreen() {
        window.clear(clearColor);
    }

    // Handle various events such as window close, mouse button press, and text input
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isRunning = false;
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (button.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        inputText = "";
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::C) { // Press 'C' to clear the screen to cyan color
                    setClearColor(sf::Color::Cyan);
                }
                else if (event.key.code == sf::Keyboard::M) { // Press 'M' to clear the screen to magenta color
                    setClearColor(sf::Color::Magenta);
                }
                else if (event.key.code == sf::Keyboard::Y) { // Press 'Y' to clear the screen to yellow color
                    setClearColor(sf::Color::Yellow);
                }
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == '\b') {
                        if (!inputText.empty()) {
                            inputText.pop_back();
                        }
                    }
                    else {
                        inputText += event.text.unicode;
                    }
                }
            }
        }
    }

    // Update the game logic
    void update() {
        // Set frame rate limit
        window.setFramerateLimit(framesPerSecond);

        // Check if mouse and keyboard are enabled
        if (isMouseEnabled) {
            // Handle mouse input
        }

        if (isKeyboardEnabled) {
            // Handle keyboard input
        }

        // Update game logic here
    }

    // Render the game, including the button, input text, and elapsed time
    void render() {
        clearScreen();

        // Draw the button
        window.draw(button);

        // Draw the input text
        text.setString("Input: " + inputText);
        text.setPosition(10.f, 10.f);
        window.draw(text);

        // Draw the elapsed time
        sf::Time elapsed = clock.getElapsedTime();
        std::string timeString = "Elapsed Time: " + std::to_string(elapsed.asSeconds());
        sf::Text timeText(timeString, font, 24);
        timeText.setFillColor(sf::Color::White);
        timeText.setPosition(10.f, 40.f);
        window.draw(timeText);

        window.display();
    }

    // Run the game loop
    void run() {
        while (isRunning) {
            handleEvents();
            update();
            render();
        }
        // Clean up resources and close the log file
        logfile.close();
        window.close();
    }

    // Log errors to the console and the log file
    void logError(const std::string& errorMessage) {
        std::cerr << errorMessage << std::endl;
        if (logfile.is_open()) {
            logfile << "Error: " << errorMessage << std::endl;
        }
    }
};

int main() {
    // Create an instance of the Engine and run the game
    Engine engine(800, 600, "SFML Game");
    engine.initialize();
    engine.run();
    return 0;
}
