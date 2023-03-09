#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <cmath>

class Phasor {
private:
    sf::CircleShape circle;
    sf::Color thikness_color;
    float radius_;

    sf::RectangleShape line;
    float frequency_;

    unsigned int evolution_counter;

    // Private functions
    void initShape();
    void initArrow();

public:
    Phasor();
    Phasor(float, sf::Color, float);
    virtual ~Phasor();

    // Accessors
    unsigned int getCounter();
    sf::Vector2f getPole();
    void updateCounter();
    void bind(Phasor&);

    // Functions
    void setRadius(float);
    void setColor(sf::Color);
    void setInitialAngle(float);
    void setFrequency(float);
    void setPosition(sf::Vector2f);
    void rotate();
    sf::Vector2f getCentre();

    void update();
    void render(sf::RenderTarget*);
};