#include <SFML/Graphics.hpp>
#include "Fractals.hpp"
#include "Visualizer.hpp"

int main() {
    uint32_t width = 1200, height = 1200;
    
    sf::RenderWindow window(sf::VideoMode({ width, height }), "Fractal");

    Visualizer visualizer(width, height, 500); // for high quality, use 40000

    sf::Vector2i lastMousePosition = sf::Mouse::getPosition(window);

    int fractalChoice = 1;

    while (window.isOpen()) {
        bool windowFocused = window.hasFocus();

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            default: break;
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                if (event.size.width != 0 && event.size.height != 0) {
					width = event.size.width;
					height = event.size.height;
					visualizer.Resize(width, height);
	                window.setView(sf::View(sf::FloatRect({0.f,0.f }, {(float)width, (float)height })));
                }
				break;
            case sf::Event::MouseWheelScrolled:
                if (windowFocused)
                    visualizer.Zoom(event.mouseWheelScroll.x, event.mouseWheelScroll.y, event.mouseWheelScroll.delta);
                break;
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

        window.clear(sf::Color::White);
        visualizer.Draw(window);
        window.display();
    }

    return 0;
}