#include "phasor.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <iostream>

static double pi = 3.141592653589793238462643383279;

int main() {
    unsigned int N{};
    std::cout << "Insert the initial number of phasors. The series is compute from -N to N: ";
    std::cin >> N;
    std::cout << "\n\n";

    sf::Clock clock;

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1400,1000), "Square", sf::Style::Close | sf::Style::Titlebar);
    window->setPosition({100, 0});
    sf::Event ev;

    std::vector<Phasor> phasors;
    float f = 0.2;
    float r = 100.f;
    float c_n;

    std::vector<sf::Vector2f> points;
    sf::CircleShape point(1.f);
    point.setFillColor(sf::Color::Blue);


    for (int i{0}; i<N; i++) {
        if (i%2 == 0) { 
            c_n = 1.3*r/((i+1));

            phasors.push_back({-c_n, sf::Color::White, -f*(i+1)});
            phasors.push_back({c_n, sf::Color::White, f*(i+1)});
        }

        else { 
            c_n = r/((i*i));

            phasors.push_back({c_n, sf::Color::White, -f*(i)});
            phasors.push_back({c_n, sf::Color::White, f*(i)});
        }
    }

    phasors[0].setPosition({700, 500});

    while (window->isOpen()) {
        while(window->pollEvent(ev)) {
            if (ev.Event::type == sf::Event::Closed) { window->close(); }
            if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape) { window->close(); }
        }


        phasors[0].update();

        for (long unsigned int i{1}; i<phasors.size(); i++) {
            phasors[i].bind(phasors[i-1]);
            phasors[i].update();
        }

        phasors[phasors.size()-1].updateCounter();


        points.push_back(phasors[phasors.size()-1].getPole());
        //points.push_back({ static_cast<float>(window->getSize().x/2), phasors[phasors.size()-1].getPole().y});

        window->clear();

        for (auto& it : phasors) {
            it.render(window);
        }

        for (long unsigned int i{}; i<points.size(); i++) {
            point.setPosition(points[i]);

            window->draw(point);
        }

        /*for (long unsigned int i{}; i<points.size(); i++) {
            if (points[i].x > window->getSize().x) { points.erase(points.begin() + i); }
            points[i] = {static_cast<float>(points[i].x + f), points[i].y};
            point.setPosition(points[i]);

            window->draw(point);
        }*/

        window->display();

        if (clock.getElapsedTime() >= sf::seconds(30)) {
            points.erase(points.begin(), points.begin() + points.size()/2);
            clock.restart();
        }
    }

    delete window;
}