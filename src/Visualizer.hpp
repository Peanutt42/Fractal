#pragma once

#include "Fractals.hpp"

#include <SFML/Graphics.hpp>

#include <functional>

using VisualizerFunc = std::function<sf::Color(int iterations, int max_iterations)>;

sf::Color red_visualizer(int iterations, int max_iterations) {
	return sf::Color(255 * iterations / max_iterations, 0, 0);
}

class Visualizer {
public:
	Visualizer(int width, int height, int max_iterations)
		: m_Width(width), m_Height(height), m_MaxIterations(max_iterations)
	{
		m_Image.create({ (uint32_t)m_Width, (uint32_t)m_Height }, sf::Color::Black);
		m_Texture.loadFromImage(m_Image);
	}

	void Zoom(double x, double y, double factor) {
		double real = m_MinReal + x * (m_MaxReal - m_MinReal) / m_Width;
		double imag = m_MinImag + y * (m_MaxImag - m_MinImag) / m_Height;

		double newWidth = (m_MaxReal - m_MinReal) / factor;
		double newHeight = (m_MaxImag - m_MinImag) / factor;

		m_MinReal = real - newWidth / 2.0;
		m_MaxReal = real + newWidth / 2.0;
		m_MinImag = imag - newHeight / 2.0;
		m_MaxImag = imag + newHeight / 2.0;

		// moves so the camera doesn't center on the zoomed position
		Pan(x - (m_Width / 2), y - (m_Height / 2));
	}

	void Pan(double deltaX, double deltaY) {
		double realShift = deltaX * (m_MaxReal - m_MinReal) / m_Width;
		double imagShift = deltaY * (m_MaxImag - m_MinImag) / m_Height;

		m_MinReal -= realShift;
		m_MaxReal -= realShift;
		m_MinImag -= imagShift;
		m_MaxImag -= imagShift;
	}

	void Update(const FractalFunc& fractalFunc, const VisualizerFunc& visualizeFunc) {
		for (uint32_t x = 0; x < m_Width; ++x) {
			for (uint32_t y = 0; y < m_Height; ++y) {
				double real = m_MinReal + x * (m_MaxReal - m_MinReal) / m_Width;
				double imag = m_MinImag + y * (m_MaxImag - m_MinImag) / m_Height;

				int iterations = fractalFunc(real, imag, m_MaxIterations);

				m_Image.setPixel({ x, y }, visualizeFunc(iterations, m_MaxIterations));
			}
		}

		m_Texture.loadFromImage(m_Image);
	}

	void Draw(sf::RenderWindow& window) {
		sf::Sprite sprite(m_Texture);
		window.draw(sprite);
	}

private:
	sf::Image m_Image;
	sf::Texture m_Texture;

	int m_Width = 0, m_Height = 0;
	int m_MaxIterations = 0;

	double m_MinReal = -2.0, m_MaxReal = 2.0;
	double m_MinImag = -2.0, m_MaxImag = 2.0;
};