#include "phasor.hpp"

static double pi = 3.141592653589793238462643383279;

// Private functions
void Phasor::initShape() {
    circle.setRadius(radius_);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(2.f);
    circle.setOutlineColor(thikness_color);
    circle.setOrigin({radius_, radius_});
}

void Phasor::initArrow() {
    line.setSize({radius_, 1});
    line.setFillColor(sf::Color::White);
    line.setPosition(circle.getPosition());
}

// Constructor & destructor
Phasor::Phasor() {
    evolution_counter = 0;

    initShape();
    initArrow();
}

Phasor::Phasor(float radius, sf::Color color, float frequency) {
    evolution_counter = 0;
    radius_ = radius;
    thikness_color = color;
    frequency_ = frequency;

    initShape();
    initArrow();
}

Phasor::~Phasor() {

}

// Accessors
unsigned int Phasor::getCounter() {
    return evolution_counter;
}

sf::Vector2f Phasor::getPole() {
    float angle = evolution_counter * frequency_*pi/180;
    float x = line.getSize().x * cos(angle) + line.getSize().y * sin(angle);
    float y = -line.getSize().y * cos(angle) + line.getSize().x * sin(angle);
    sf::Vector2f size = {x,y};
    
    return line.getPosition() + size;
}

void Phasor::updateCounter() {
    ++evolution_counter;
}

void Phasor::bind(Phasor& phi) {
    this->setPosition(phi.getPole());
    phi.updateCounter();
}

// Functions
void Phasor::setRadius(float radius) {
    radius_ = radius;
}

void Phasor::setColor(sf::Color color) {
    thikness_color = color;
}

void Phasor::setFrequency(float frequency) {
    frequency_ = frequency;
}

void Phasor::setPosition(sf::Vector2f pos) {
    circle.setPosition(pos);
    line.setPosition(pos);
}

void Phasor::rotate() {
    line.rotate(frequency_);
}

sf::Vector2f Phasor::getCentre() {
    return line.getPosition();
}

void Phasor::update() {
    rotate();
}

void Phasor::render(sf::RenderTarget* target) {
    target->draw(circle);
    target->draw(line);
}