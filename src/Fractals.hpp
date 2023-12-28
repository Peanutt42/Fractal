#pragma once

#include <functional>

using FractalFunc = std::function<int(double real, double imag, int max_iterations)>;


int mandelbrot(double real, double imag, int max_iterations) {
    int iterations = 0;
    double r = 0.0;
    double i = 0.0;

    while (iterations < max_iterations && r * r + i * i < 4.0) {
        double temp = r * r - i * i + real;
        i = 2.0 * r * i + imag;
        r = temp;
        iterations++;
    }

    return iterations;
}