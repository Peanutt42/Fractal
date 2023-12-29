#pragma once

#include <SFML/Graphics.hpp>

#include <functional>

using FractalFunc = std::function<double(double x, double y, int max_iterations)>;

using Vec2 = sf::Vector2<double>;


double julia(double x, double y, int max_iterations) {
    constexpr double real = -0.8;
    constexpr double imag = 0.156;

    int iterations = 0;
    double zr{ x };
    double zi{ y };
    double mod = zr * zr + zi * zi;
    while (mod < 4.0 && iterations < max_iterations) {
        double tmp = zr;
        zr = zr * zr - zi * zi + real;
        zi = 2.0 * zi * tmp + imag;
        mod = zr * zr + zi * zi;
        iterations++;
    }
    return (double)iterations - std::log2(std::max(1.0, std::log2(mod)));
}

double mandelbrot(double x, double y, int max_iterations) {
    double real = -2.0 + x * 4.0;
    double imag = -2.0 + y * 4.0;

    int iterations = 0;
    double r = 0.0;
    double i = 0.0;
    double mod = r * r + i * i;
    while (iterations < max_iterations && mod < 4.0) {
        double temp = r * r - i * i + real;
        i = 2.0 * r * i + imag;
        r = temp;
        mod = r * r + i * i;
        iterations++;
    }

    return (double)iterations - std::log2(std::max(1.0, std::log2(mod)));
}

double burningShip(double x, double y, int max_iterations) {
    double real = x;
    double imag = y;

    int iterations = 0;
    double r = 0.0;
    double i = 0.0;
    double mod = r * r + i * i;

    while (iterations < max_iterations && mod < 4.0) {
        double temp = std::abs(r * r - i * i) + real;
        i = 2.0 * std::abs(r * i) + imag;
        r = temp;
        mod = r * r + i * i;
        iterations++;
    }

    return (double)iterations - std::log2(std::max(1.0, std::log2(mod)));
}

double tricorn(double x, double y, int max_iterations) {
    double real = x;
    double imag = y;

    int iterations = 0;
    double r = 0.0;
    double i = 0.0;
    double mod = r * r + i * i;

    while (iterations < max_iterations && mod < 4.0) {
        double temp = r * r - i * i + real;
        i = -2.0 * r * i + imag;
        r = temp;
        mod = r * r + i * i;
        iterations++;
    }

    return (double)iterations - std::log2(std::max(1.0, std::log2(mod)));
}