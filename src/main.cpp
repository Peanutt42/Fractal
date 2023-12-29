#include <SFML/Graphics.hpp>
#include "Fractals.hpp"
#include "Visualizer.hpp"

int main() {
    const int width = 800, height = 800;
    const double quality = 50.0;

    sf::RenderWindow window(sf::VideoMode({ width, height }), "Fractal", sf::Style::Titlebar | sf::Style::Close);

    Visualizer visualizer(width, height, 100);

    sf::Vector2i lastMousePosition = sf::Mouse::getPosition(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseWheelScrolled) {
                double factor = 1.0 + (event.mouseWheelScroll.delta * 0.1);
                visualizer.Zoom(event.mouseWheelScroll.x, event.mouseWheelScroll.y, factor);
            }
        }

        sf::Vector2i currentMosuePosition = sf::Mouse::getPosition(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            visualizer.Pan(currentMosuePosition.x - lastMousePosition.x, currentMosuePosition.y - lastMousePosition.y);
        lastMousePosition = currentMosuePosition;


        visualizer.Update(mandelbrot);

        window.clear();
        visualizer.Draw(window);
        window.display();
    }

    return 0;
}
