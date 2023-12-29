#include <SFML/Graphics.hpp>
#include "Fractals.hpp"
#include "Visualizer.hpp"

int main() {
    const int width = 800, height = 800;

    sf::RenderWindow window(sf::VideoMode({ width, height }), "Fractal", sf::Style::Titlebar | sf::Style::Close);

    Visualizer visualizer(width, height, 300);

    sf::Vector2i lastMousePosition = sf::Mouse::getPosition(window);

    int fractalChoice = 1;

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
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1)
                    fractalChoice = 1;
                else if (event.key.code == sf::Keyboard::Num2)
                    fractalChoice = 2;
                else if (event.key.code == sf::Keyboard::Num3)
                    fractalChoice = 3;
                else if (event.key.code == sf::Keyboard::Num4)
                    fractalChoice = 4;
            }
        }

        sf::Vector2i currentMosuePosition = sf::Mouse::getPosition(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            visualizer.Pan(currentMosuePosition.x - lastMousePosition.x, currentMosuePosition.y - lastMousePosition.y);
        lastMousePosition = currentMosuePosition;

        switch (fractalChoice) {
        default:
        case 1:
            visualizer.Update(mandelbrot); break;
        case 2:
            visualizer.Update(julia); break;
        case 3:
            visualizer.Update(burningShip); break;
        case 4:
            visualizer.Update(tricorn); break;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            std::printf("save");
        }

        window.clear();
        visualizer.Draw(window);
        window.display();
    }

    return 0;
}
