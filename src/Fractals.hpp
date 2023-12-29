#pragma once

#include <SFML/Graphics.hpp>

#include <functional>

using FractalFunc = std::function<sf::Color(double x, double y, int max_iterations)>;


sf::Color mandelbrot(double x, double y, int max_iterations) {
    double real = -2.0 + x * 4.0;
    double imag = -2.0 + y * 4.0;

    int iterations = 0;
    double r = 0.0;
    double i = 0.0;

    while (iterations < max_iterations && r * r + i * i < 4.0) {
        double temp = r * r - i * i + real;
        i = 2.0 * r * i + imag;
        r = temp;
        iterations++;
    }

    int value = 255 * iterations / max_iterations;
    return sf::Color(value, value, value, value);
}