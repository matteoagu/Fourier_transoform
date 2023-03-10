#include "phasor.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <iostream>

static double pi = 3.141592653589793238462643383279;

int main() {
    int N;
    std::cout << "Insert the initial number of phasors. The biggest is the number, the better is the approximation of the function!\n";
    std::cin >> N;
    if (N<1) { throw std::runtime_error{"You can't start with zero phasors!"}; }

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1400,600), "Square wave", sf::Style::Close | sf::Style::Titlebar);
    window->setPosition({300, 100});
    sf::Event ev;
    float f = 0.05;
    float r = 150.f;
    std::vector<float> trace;
    bool show = false;

    sf::Clock clock;

    std::vector<Phasor> phasors;
    Phasor phasor(r, sf::Color::White, 0);
    phasor.setPosition({500, 300});

    sf::RectangleShape axis_x({static_cast<float>(window->getSize().x), 1});
    axis_x.setPosition({0, static_cast<float>(window->getSize().y/2)});
    axis_x.setFillColor(sf::Color::White);

    sf::RectangleShape axis_y({1, static_cast<float>(window->getSize().y)});
    axis_y.setPosition(50, 0);
    axis_y.setFillColor(sf::Color::White);

    for (int i{1}; i<N+1; i++) {
        float c_n;

        if (i%2==0) { c_n = 0; }
        else { c_n = -4*r/(pi*i); }

        phasors.push_back({c_n, sf::Color::White, f*i});
    }

    while (window->isOpen()) {
        while(window->pollEvent(ev)) {
            if (ev.Event::type == sf::Event::Closed) { window->close(); }
            if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape) { window->close(); }
            if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::D) { show = true; }
            if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::P && clock.restart() >= sf::seconds(0.3f)) { 
                trace.clear();
                N++ ;
                float c_n;
                if (N%2==0) { c_n = 0; }
                else { c_n = -4*r/(pi*N); }

                phasors.push_back({c_n, sf::Color::White, f*N});
            }
        }

        phasor.update();
        phasors[0].bind(phasor);
        phasors[0].update();

        for (int i{1}; i<N+1; i++) {
            phasors[i].bind(phasors[i-1]);
            phasors[i].update();
        }

        trace.push_back(phasors[N].getPole().y);

        window->clear();

        phasor.render(window);
        for (auto& it : phasors) {
            it.render(window);
        }

        window->display();

        while (show) {
            sf::CircleShape point(1.f);
            point.setFillColor(sf::Color::Red);

            window->clear();

            float i = 50.f;
            for (auto it : trace) {
                point.setPosition({i, it});
                window->draw(point);
                i = i+0.04;
            }
            window->draw(axis_x);
            window->draw(axis_y);

            window->display();

            while(window->pollEvent(ev)) {
                if (ev.Event::type == sf::Event::Closed) { show = false; window->close(); }
                if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape) { show = false; window->close(); }
            }
        }
    }
    
    delete window;
}
