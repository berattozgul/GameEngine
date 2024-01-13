//Engine.cpp
#include "Engine.h"
#include "PrimitiveRenderer.h"
#include "Point2D.h"
#include "LineSegment.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <fstream>
#include <iostream>
#include <vector>

Engine::Engine(int width, int height, std::string title) : window(sf::VideoMode(width, height), title), primitiveRenderer(window),
isRunning(false), logfile("log.txt"),
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

	// Initialize render texture
	renderTexture.create(width, height);

}

// Initialize the game engine
void Engine::initialize() {
	isRunning = true;
	clock.restart();
}

// Set the background color of the window
void Engine::setClearColor(sf::Color color) {
	clearColor = color;
}
// Set the frames per second for the animation
void Engine::setFramesPerSecond(int fps) {
	framesPerSecond = fps;
}

// Enable or disable mouse support
void Engine::setMouseEnabled(bool enabled) {
	isMouseEnabled = enabled;
}

// Enable or disable keyboard support
void Engine::setKeyboardEnabled(bool enabled) {
	isKeyboardEnabled = enabled;
}

// Handle various events such as window close, mouse button press, and text input
void Engine::handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			isRunning = false;
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			}
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::B) { // Press 'C' to clear the screen to cyan color
				setClearColor(sf::Color::Black);
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
void Engine::update() {
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
void Engine::render() {
	// Clear the main window
	window.clear(clearColor);

	// Draw using the PrimitiveRenderer
	primitiveRenderer.drawLine(400.f, 400.f, 500.f, 500.f, 5.f, sf::Color::Blue);

	// Draw the input text
	text.setString("Input: " + inputText);
	text.setPosition(10.f, 10.f);
	window.draw(text);

	// Create a Point2D instance and draw it using PrimitiveRenderer
	Point2D point(300.f, 100.f);
	point.draw(primitiveRenderer, sf::Color::White);

	Point2D startPoint(500.f, 200.f);

	// Update line length based on elapsed time
	float lineLength = 100.f + std::sin(clock.getElapsedTime().asSeconds()) * 100.f;
	Point2D endPoint(startPoint.getX() + lineLength, startPoint.getY() + lineLength);

	LineSegment lineSegment(startPoint, endPoint);

	// Draw the line segment using the incremental algorithm
	lineSegment.draw(primitiveRenderer, sf::Color::Yellow, true);


	// Draw an open polyline using a vector of Point2D

	std::vector<LineSegment> openPolygonSegments = {
	LineSegment({250.f, 200.f}, {250.f, 250.f}),
	LineSegment({250.f, 250.f}, {300.f, 200.f}),
	LineSegment({300.f, 200.f}, {300.f, 300.f})
	};
	primitiveRenderer.drawPolyline(openPolygonSegments, sf::Color::Magenta, false);

	primitiveRenderer.drawEllipse(500.f, 300.f, 50.f, 30.f, sf::Color::Green);

	primitiveRenderer.drawCircleSymmetrical(700.f, 300.f, 50.f, sf::Color::Yellow);

	std::vector<Point2D> closedPolyLinePoints = { {100.f, 200.f}, {150.f, 150.f}, {200.f, 200.f}, {200.f, 300.f}, {200.f, 500.f} };

	// Use the borderFill and floodFill methods to fill areas
	primitiveRenderer.borderFill(75, 75, sf::Color::Yellow, sf::Color::White); // Example of borderFill
	primitiveRenderer.floodFill(250, 250, sf::Color::Cyan, sf::Color::White); // Example of floodFill
	
	primitiveRenderer.drawFilledRectangle(100.0f, 100.0f, 150.0f, 80.0f, sf::Color::Red);

	primitiveRenderer.drawFilledPolygon(closedPolyLinePoints, sf::Color::Blue);

	primitiveRenderer.floodFill(100, 300, sf::Color::Black, sf::Color::Red);
	primitiveRenderer.borderFill(400, 400, sf::Color::Black, sf::Color::Red);
	sf::Time elapsed = clock.getElapsedTime();
	std::string timeString = "Elapsed Time: " + std::to_string(elapsed.asSeconds());
	sf::Text timeText(timeString, font, 24);
	timeText.setFillColor(sf::Color::White);
	timeText.setPosition(10.f, 40.f);
	window.draw(timeText);

	window.display(); // Display the main window

}

// Run the game loop
void Engine::run() {
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
void Engine::logError(const std::string& errorMessage) {
	std::cerr << errorMessage << std::endl;
	if (logfile.is_open()) {
		logfile << "Error: " << errorMessage << std::endl;
	}
}