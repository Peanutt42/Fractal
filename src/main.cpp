#include <SFML/Graphics.hpp>

const int WIDTH = 800;
const int HEIGHT = 800;
const int MAX_ITERATIONS = 100;

double minReal = -2.0;
double maxReal = 2.0;
double minImag = -2.0;
double maxImag = 2.0;

int mandelbrot(double real, double imag) {
    int iterations = 0;
    double r = 0.0;
    double i = 0.0;

    while (iterations < MAX_ITERATIONS && r * r + i * i < 4.0) {
        double temp = r * r - i * i + real;
        i = 2.0 * r * i + imag;
        r = temp;
        iterations++;
    }

    return iterations;
}

void zoom(double centerX, double centerY, double factor) {
    double newWidth = (maxReal - minReal) / factor;
    double newHeight = (maxImag - minImag) / factor;

    minReal = centerX - newWidth / 2.0;
    maxReal = centerX + newWidth / 2.0;
    minImag = centerY - newHeight / 2.0;
    maxImag = centerY + newHeight / 2.0;
}

int main() {
    sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGHT }), "Zoomable Mandelbrot Fractal");

    sf::Image image;
    image.create({ WIDTH, HEIGHT }, sf::Color::Black);

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                // Zoom in when left mouse button is pressed
                double mouseX = event.mouseButton.x;
                double mouseY = event.mouseButton.y;

                double real = minReal + mouseX * (maxReal - minReal) / WIDTH;
                double imag = minImag + mouseY * (maxImag - minImag) / HEIGHT;

                double factor = 1.0;
                if (event.mouseButton.button == sf::Mouse::Left)
                    factor = 2.0;
                else if (event.mouseButton.button == sf::Mouse::Right)
                    factor = 0.5;
                zoom(real, imag, factor);
            }
        }

        // Redraw the fractal with the new zoom level
        for (uint32_t x = 0; x < WIDTH; ++x) {
            for (uint32_t y = 0; y < HEIGHT; ++y) {
                double real = minReal + x * (maxReal - minReal) / WIDTH;
                double imag = minImag + y * (maxImag - minImag) / HEIGHT;

                int iterations = mandelbrot(real, imag);

                sf::Color color = sf::Color(255 * iterations / MAX_ITERATIONS, 0, 0);
                image.setPixel({ x, y }, color);
            }
        }

        texture.loadFromImage(image);
        sprite.setTexture(texture);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
