#include <SFML/Graphics.hpp>
#include "Engine.h"
#include <iostream>
#include <fstream>

int main() {
    // Create an instance of the Engine and run the game
    Engine engine(800, 600, "SFML Game");
    engine.initialize();
    // Set FPS
    engine.setFramesPerSecond(60);
    engine.run();
    return 0;
}