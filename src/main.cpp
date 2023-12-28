#include <SFML/Graphics.hpp>
#include "Fractals.hpp"
#include "Visualizer.hpp"

int main() {
    const int width = 800, height = 800;

    sf::RenderWindow window(sf::VideoMode({ width, height }), "Zoomable Mandelbrot Fractal");

    Visualizer visualizer(width, height, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                double mouseX = event.mouseButton.x;
                double mouseY = event.mouseButton.y;

                double factor = 1.0;
                if (event.mouseButton.button == sf::Mouse::Left)
                    factor = 2.0;
                else if (event.mouseButton.button == sf::Mouse::Right)
                    factor = 0.5;

                visualizer.Zoom(mouseX, mouseY, factor);
            }
        }

        visualizer.Update(mandelbrot, red_visualizer);

        window.clear();
        visualizer.Draw(window);
        window.display();
    }

    return 0;
}
