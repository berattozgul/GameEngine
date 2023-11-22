#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "PrimitiveRenderer.h"

class Engine {
private:
    sf::RenderWindow window;
    sf::Color clearColor;
    sf::Font font;
    sf::Text text;
    std::string inputText;
    sf::Clock clock;
    bool isRunning;
    std::ofstream logfile;
    int framesPerSecond;
    bool isMouseEnabled;
    bool isKeyboardEnabled;
    sf::RenderTexture renderTexture;
    sf::Sprite activeSprite;
    sf::Sprite inactiveSprite;
    PrimitiveRenderer primitiveRenderer;

public:
    Engine(int width, int height, std::string title);

    void initialize();
    void setClearColor(sf::Color color);
    void setFramesPerSecond(int fps);
    void setMouseEnabled(bool enabled);
    void setKeyboardEnabled(bool enabled);
    void handleEvents();
    void update();
    void render();
    void run();
    void logError(const std::string& errorMessage);
};
