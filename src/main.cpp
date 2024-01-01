#include <SFML/Graphics.hpp>
#include "Fractals.hpp"
#include "Visualizer.hpp"

int main() {
    uint32_t width = 1200, height = 1200;
    
    sf::RenderWindow window(sf::VideoMode({ width, height }), "Fractal", sf::Style::Titlebar | sf::Style::Close);

    Visualizer visualizer(width, height, 500); // for high quality, use 40000

    sf::Vector2i lastMousePosition = sf::Mouse::getPosition(window);

    int fractalChoice = 1;

    while (window.isOpen()) {
        bool windowFocused = window.hasFocus();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (windowFocused && event.type == sf::Event::MouseWheelScrolled) {
                double factor = 1.0 + (event.mouseWheelScroll.delta * 0.1);
                visualizer.Zoom(event.mouseWheelScroll.x, event.mouseWheelScroll.y, factor);
            }
        }

        sf::Vector2i currentMosuePosition = sf::Mouse::getPosition(window);

        if (windowFocused) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                fractalChoice = 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
                fractalChoice = 2;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
                fractalChoice = 3;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
                fractalChoice = 4;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                visualizer.SetMaxIterations(visualizer.GetMaxIterations() + 50);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                visualizer.SetMaxIterations(visualizer.GetMaxIterations() - 50);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                visualizer.SetMultithreading(true);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                visualizer.SetMultithreading(false);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                visualizer.Pan(currentMosuePosition.x - lastMousePosition.x, currentMosuePosition.y - lastMousePosition.y);
        }
        lastMousePosition = currentMosuePosition;

        switch (fractalChoice) {
        default:
        case 1:
            visualizer.Update(mandelbrot, colorful); break;
        case 2:
            visualizer.Update(julia, colorful); break;
        case 3:
            visualizer.Update(burningShip, colorful); break;
        case 4:
            visualizer.Update(tricorn, colorful); break;
        }

        if (windowFocused && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            std::printf("saving to output.jpg - ");
            visualizer.SaveToFile("output.jpg");
            std::printf("finished.\n");
        }

        window.clear();
        visualizer.Draw(window);
        window.display();
    }

    return 0;
}
